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
        let output = demangle_line(line);
        println!("{}", output);
    }
}

fn demangle_line(line: &str) -> String {
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
                return format!("{addr}|||{sym}|||{demangled}|||{namespace}|||{name}");
            } else {
                // Function: [return-type] [namespace::]name([parameter_types]) [cv-qualifier]
                let (prolog, _parameters, _epilog) = split_function(demangled.as_str());

                let (_return_type, qualified_name) = split_return(prolog);
                let (namespace, name) = split_namespace(qualified_name);

                return format!("{addr}|||{sym}|||{demangled}|||{namespace}|||{name}");
            }
        },
        None => {
            return format!("{addr}|||{sym}");
        }
    };
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

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn c_symbol() {
        assert_eq!(
            &demangle_line("main = .text:0x8000F96C; // type:function size:0x44 scope:global"),
            "0x8000F96C|||main"
        );
    }

    #[test]
    fn namespace_function() {
        assert_eq!(
            &demangle_line("Lefty__8GemTrackCFv = .text:0x801411A0; // type:function size:0x8 scope:global align:16"),
            "0x801411A0|||Lefty__8GemTrackCFv|||GemTrack::Lefty(void) const|||GemTrack|||Lefty"
        );
    }

    #[test]
    fn namespace_variable() {
        assert_eq!(
            &demangle_line("gRev__10BandButton = .sbss:0x808E45B4; // type:object size:0x2 data:2byte"),
            "0x808E45B4|||gRev__10BandButton|||BandButton::gRev|||BandButton|||gRev"
        );
    }

    #[test]
    fn operator() {
        assert_eq!(
            &demangle_line("__rs__FR9BinStreamR6SfxMap = .text:0x8068FC80; // type:function size:0x38"),
            "0x8068FC80|||__rs__FR9BinStreamR6SfxMap|||operator>>(BinStream&, SfxMap&)||||||operator>>"
        );
    }

    #[test]
    fn namespace_operator() {
        assert_eq!(
            &demangle_line("__vc__7MessageFi = .text:0x8000DF44; // type:function size:0xC"),
            "0x8000DF44|||__vc__7MessageFi|||Message::operator[](int)|||Message|||operator[]"
        );
    }

    #[test]
    fn template_function() {
        assert_eq!(
            &demangle_line("__find<PP10RndEnviron,P10RndEnviron>__11stlpmtx_stdFPP10RndEnvironPP10RndEnvironRCP10RndEnvironRCQ211stlpmtx_std26random_access_iterator_tag_PP10RndEnviron = .text:0x800B1334; // type:function size:0xD4"),
            "0x800B1334|||__find<PP10RndEnviron,P10RndEnviron>__11stlpmtx_stdFPP10RndEnvironPP10RndEnvironRCP10RndEnvironRCQ211stlpmtx_std26random_access_iterator_tag_PP10RndEnviron|||RndEnviron** stlpmtx_std::__find<RndEnviron**, RndEnviron*>(RndEnviron**, RndEnviron**, RndEnviron* const&, const stlpmtx_std::random_access_iterator_tag&)|||stlpmtx_std|||__find<RndEnviron**, RndEnviron*>"
        );
    }

    #[test]
    fn template_namespace_function() {
        assert_eq!(
            &demangle_line("__ct__Q26Quazal66DOClassTemplate<Q26Quazal15_DO_DefaultCell,Q26Quazal11_DOC_RootDO>Fv = .text:0x8007D9D8; // type:function size:0x3C"),
            "0x8007D9D8|||__ct__Q26Quazal66DOClassTemplate<Q26Quazal15_DO_DefaultCell,Q26Quazal11_DOC_RootDO>Fv|||Quazal::DOClassTemplate<Quazal::_DO_DefaultCell, Quazal::_DOC_RootDO>::DOClassTemplate(void)|||Quazal :: DOClassTemplate<Quazal::_DO_DefaultCell, Quazal::_DOC_RootDO>|||DOClassTemplate"
        );
    }

    #[test]
    fn template_operator() {
        assert_eq!(
            &demangle_line("__rs<i,Us>__FR9BinStreamRQ211stlpmtx_std45vector<i,Us,Q211stlpmtx_std15StlNodeAlloc<i>>_R9BinStream = .text:0x80134F94; // type:function size:0x7C"),
            "0x80134F94|||__rs<i,Us>__FR9BinStreamRQ211stlpmtx_std45vector<i,Us,Q211stlpmtx_std15StlNodeAlloc<i>>_R9BinStream|||BinStream& operator>><int, unsigned short>(BinStream&, stlpmtx_std::vector<int, unsigned short, stlpmtx_std::StlNodeAlloc<int>>&)||||||operator>><int, unsigned short>"
        );
        assert_eq!(
            &demangle_line("__ls<Q25Stats10StreakInfo,Us>__FR9BinStreamRCQ211stlpmtx_std83vector<Q25Stats10StreakInfo,Us,Q211stlpmtx_std34StlNodeAlloc<Q25Stats10StreakInfo>>_R9BinStream = .text:0x80160424; // type:function size:0x74"),
            "0x80160424|||__ls<Q25Stats10StreakInfo,Us>__FR9BinStreamRCQ211stlpmtx_std83vector<Q25Stats10StreakInfo,Us,Q211stlpmtx_std34StlNodeAlloc<Q25Stats10StreakInfo>>_R9BinStream|||BinStream& operator<<<Stats::StreakInfo, unsigned short>(BinStream&, const stlpmtx_std::vector<Stats::StreakInfo, unsigned short, stlpmtx_std::StlNodeAlloc<Stats::StreakInfo>>&)||||||operator<<<Stats::StreakInfo, unsigned short>"
        );
    }

    #[test]
    fn template_namespace_operator() {
        assert_eq!(
            &demangle_line("__as__Q211stlpmtx_std45vector<f,Us,Q211stlpmtx_std15StlNodeAlloc<f>>FRCQ211stlpmtx_std45vector<f,Us,Q211stlpmtx_std15StlNodeAlloc<f>> = .text:0x801349B8; // type:function size:0x30"),
            "0x801349B8|||__as__Q211stlpmtx_std45vector<f,Us,Q211stlpmtx_std15StlNodeAlloc<f>>FRCQ211stlpmtx_std45vector<f,Us,Q211stlpmtx_std15StlNodeAlloc<f>>|||stlpmtx_std::vector<float, unsigned short, stlpmtx_std::StlNodeAlloc<float>>::operator=(const stlpmtx_std::vector<float, unsigned short, stlpmtx_std::StlNodeAlloc<float>>&)|||stlpmtx_std :: vector<float, unsigned short, stlpmtx_std::StlNodeAlloc<float>>|||operator="
        );
    }

    #[test]
    fn template_namespace_template_operator() {
        assert_eq!(
            &demangle_line("__vc<6Symbol>__Q211stlpmtx_std286map<6Symbol,Q211stlpmtx_std71vector<P11LightPreset,Us,Q211stlpmtx_std28StlNodeAlloc<P11LightPreset>>,Q211stlpmtx_std13less<6Symbol>,Q211stlpmtx_std135StlNodeAlloc<Q211stlpmtx_std103pair<C6Symbol,Q211stlpmtx_std71vector<P11LightPreset,Us,Q211stlpmtx_std28StlNodeAlloc<P11LightPreset>>>>>FRC6Symbol_RQ211stlpmtx_std71vector<P11LightPreset,Us,Q211stlpmtx_std28StlNodeAlloc<P11LightPreset>> = .text:0x805B0A68; // type:function size:0x120"),
            "0x805B0A68|||__vc<6Symbol>__Q211stlpmtx_std286map<6Symbol,Q211stlpmtx_std71vector<P11LightPreset,Us,Q211stlpmtx_std28StlNodeAlloc<P11LightPreset>>,Q211stlpmtx_std13less<6Symbol>,Q211stlpmtx_std135StlNodeAlloc<Q211stlpmtx_std103pair<C6Symbol,Q211stlpmtx_std71vector<P11LightPreset,Us,Q211stlpmtx_std28StlNodeAlloc<P11LightPreset>>>>>FRC6Symbol_RQ211stlpmtx_std71vector<P11LightPreset,Us,Q211stlpmtx_std28StlNodeAlloc<P11LightPreset>>|||stlpmtx_std::vector<LightPreset*, unsigned short, stlpmtx_std::StlNodeAlloc<LightPreset*>>& stlpmtx_std::map<Symbol, stlpmtx_std::vector<LightPreset*, unsigned short, stlpmtx_std::StlNodeAlloc<LightPreset*>>, stlpmtx_std::less<Symbol>, stlpmtx_std::StlNodeAlloc<stlpmtx_std::pair<const Symbol, stlpmtx_std::vector<LightPreset*, unsigned short, stlpmtx_std::StlNodeAlloc<LightPreset*>>>>>::operator[]<Symbol>(const Symbol&)|||stlpmtx_std :: map<Symbol, stlpmtx_std::vector<LightPreset*, unsigned short, stlpmtx_std::StlNodeAlloc<LightPreset*>>, stlpmtx_std::less<Symbol>, stlpmtx_std::StlNodeAlloc<stlpmtx_std::pair<const Symbol, stlpmtx_std::vector<LightPreset*, unsigned short, stlpmtx_std::StlNodeAlloc<LightPreset*>>>>>|||operator[]<Symbol>"
        );
    }
}
