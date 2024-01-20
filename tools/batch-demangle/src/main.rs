use clap::Parser;
use cwdemangle::*;
use std::fs::read_to_string;
use std::collections::hash_set::HashSet;

#[macro_use]
extern crate lazy_static;

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
                    let (prolog, _remaining) = demangled.split_once('(').unwrap();

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

lazy_static! {
    static ref NON_TEMPLATE_NAMES: HashSet<&'static str> = HashSet::from_iter([
        "operator<",
        "operator>",
        "operator<<",
        "operator>>",
        "operator>>=",
        "operator<<=",
        "operator<=",
        "operator>=",
        "operator->*",
        "operator->",
    ]);
}

fn split_namespace(prolog: &str) -> (String, String) {
    const PATTERN: &str = "::";

    let mut namespaces = Vec::<String>::new();

    // Ensure template arguments aren't split up
    let mut template_depth = 0;
    let mut template_buffer = String::new();
    for split in prolog.split(PATTERN) {
        // Ensure special names that contain <> but aren't templates are added as-is
        if NON_TEMPLATE_NAMES.contains(split) {
            namespaces.push(split.to_string());
            continue;
        }

        template_depth += split.matches('<').count();

        if template_depth > 0 {
            template_buffer += split;

            template_depth -= split.matches('>').count();
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

    assert!(template_buffer.is_empty());

    // Split off name, and re-join namespaces with a padded separator to make later splitting easier
    let name = namespaces.pop().unwrap();
    let namespaces = namespaces.join(" :: ");
    return (namespaces, name);
}
