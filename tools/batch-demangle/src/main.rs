use clap::Parser;
use cwdemangle::*;
use std::fs::read_to_string;

#[derive(Parser)]
struct Args {
    input: String,
}

fn main() {
    let args = Args::parse();
    let f = read_to_string(args.input).unwrap();

    for line in f.lines() {
        // Symbol info: symbol = section:0x<address>; // type:<type> [flags...]
        let (sym, remaining) = line.split_once(" = ").unwrap();
        let (_section, remaining) = remaining.split_once(':').unwrap();
        let (addr, _remaining) = remaining.split_once("; // ").unwrap();

        match demangle(sym, &DemangleOptions {
            omit_empty_parameters: false
        }) {
            Some(demangled) => {
                if !demangled.contains('(') {
                    // Variable: [namespace::]name
                    let (namespace, name) = split_namespace(demangled.as_str());
                    println!("{addr}|||{sym}|||{demangled}|||{namespace}|||{name}");
                } else {
                    // Function: [return-type] [namespace::]name([parameter_types]) [cv-qualifier]
                    let (prolog, _parameters, _epilog) = split_function(demangled.as_str());

                    let (_return_type, qualified_name) = split_return(prolog);
                    let (namespace, name) = split_namespace(qualified_name);

                    println!("{addr}|||{sym}|||{demangled}|||{namespace}|||{name}");
                }
            },
            None => {
                println!("{addr}|||{sym}");
            }
        };
    }
}

fn split_function<'a>(demangled_fn: &'a str) -> (&'a str, &'a str, &'a str) {
    // Search from the end by depth, to handle function pointer types correctly
    let mut parentheses_depth = 0;
    for (index, value) in demangled_fn.rmatch_indices(&['(', ')']) {
        parentheses_depth += match value {
            // We're searching in reverse, so closing parentheses increase our depth
            "(" => -1,
            ")" => 1,
            _ => 0
        };

        if parentheses_depth == 0 {
            let parameter_start = index;
            let parameter_end = demangled_fn.rfind(')').unwrap();
            let (prolog, remaining) = demangled_fn.split_at(parameter_start);
            let (parameters, epilog) = remaining.split_at(parameter_end - parameter_start + 1);
            return (prolog, parameters, epilog);
        }
    }

    if !demangled_fn.contains('(') {
        panic!("Non-function symbol {demangled_fn} passed to split_function!");
    } else {
        unreachable!("This branch indicates mismatched parentheses, which would be a demangler bug");
    }
}

fn split_return<'a>(prolog: &'a str) -> (&'a str, &'a str) {
    const PATTERN: &str = " ";
    match prolog.find(PATTERN) {
        Some(space_index) => match prolog.find('<') {
            // Template args, make sure space doesn't come from there
            Some(template_index) => match space_index < template_index {
                true => {
                    let (ret, _) = prolog.split_at(space_index);
                    let (_, qualified) = prolog.split_at(space_index + PATTERN.len());
                    (ret, qualified)
                },
                false => ("", prolog)
            },
            None => {
                let (ret, _) = prolog.split_at(space_index);
                let (_, qualified) = prolog.split_at(space_index + PATTERN.len());
                (ret, qualified)
            }
        },
        None => ("", prolog)
    }
}

static AMBIGUOUS_OPERATORS: [&'static str; 10] = [
    // Note: sorted by length, then from least ambiguous to most ambiguous.
    // This order avoids immense complexity, as we can just do a simple loop
    // to find the right operator.
    "->*",
    ">>=",
    "<<=",
    ">=",
    "<=",
    ">>",
    "<<",
    "->",
    ">",
    "<",
];

fn split_namespace(prolog: &str) -> (String, String) {
    const PATTERN: &str = "::";

    let mut namespaces = Vec::<String>::new();

    // Ensure template arguments aren't split up
    let mut template_depth = 0;
    let mut template_buffer = String::new();
    for split in prolog.split(PATTERN) {
        let mut template_count_text = split;

        // Specially handle operator names that contain <>
        if split.starts_with("operator") {
            let operator_remaining = &split["operator".len()..];
            for operator in AMBIGUOUS_OPERATORS {
                if !operator_remaining.starts_with(operator) {
                    continue;
                }

                // Check for templated operators such as operator<<<int>
                if operator_remaining.len() > operator.len() {
                    let template_start = &operator_remaining[operator.len()..];
                    // This is not the right operator if there is no template open at the end,
                    // or if there's more than one (the extras are part of the operator).
                    // This prevents operator<<int> from being detected as operator<<,
                    // other operator ambiguities are handled via the ordering in AMBIGUOUS_OPERATORS.
                    let lt_count = template_start.chars().take_while(|c| *c == '<').count();
                    if lt_count != 1 {
                        continue;
                    }
                }

                template_count_text = &operator_remaining[operator.len()..];
                break;
            }
        }

        // // Ensure special names that contain <> but aren't templates are added as-is
        // if NON_TEMPLATE_NAMES.contains(split) {
        //     namespaces.push(split.to_string());
        //     continue;
        // }

        template_depth += template_count_text.matches('<').count();

        if template_depth > 0 {
            template_buffer += split;

            template_depth -= template_count_text.matches('>').count();
            if template_depth < 1 {
                namespaces.push(template_buffer);
                template_buffer = String::new();
            } else {
                // Keep namespace delimiter in the final namespace
                template_buffer += PATTERN;
            }
        } else {
            namespaces.push(split.to_string());
        }
    }

    assert_eq!(template_depth, 0);
    assert!(template_buffer.is_empty());

    // Split off name, and re-join namespaces with a padded separator to make later splitting easier
    let name = namespaces.pop().unwrap();
    let namespaces = namespaces.join(" :: ");
    return (namespaces, name);
}
