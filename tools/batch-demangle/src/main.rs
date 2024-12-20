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

static FUNCTION_ENDS: [&'static str; 5] = [
    ")",
    ") const",
    ") volatile",
    ") const volatile",
    ") volatile const",
];

fn demangle_line(line: &str) -> String {
    // Symbol info: symbol = section:0x<address>; // type:<type> [flags...]
    let (sym, remaining) = line.split_once(" = ").unwrap();
    let (_section, remaining) = remaining.split_once(':').unwrap();
    let (addr, _remaining) = remaining.split_once("; // ").unwrap();

    // Skip demangling compiler-generated symbols,
    // as well as symbols for function-static variables/data
    if sym.starts_with('@') {
        return format!("{addr}|||{sym}");
    }

    match demangle(sym, &DemangleOptions {
        omit_empty_parameters: false
    }) {
        Some(demangled) => {
            if !FUNCTION_ENDS.iter().any(|end| demangled.ends_with(end)) {
                // Variable: [namespace::]name
                let (Name { namespace, name }, remaining) = parse_name(demangled.as_str());
                assert!(remaining.is_empty());
                return format!("{addr}|||{sym}|||{demangled}|||{namespace}|||{name}");
            } else {
                // Function: [return-type] [namespace::]name([parameter_types]) [cv-qualifier]
                let (prolog, _parameters, _epilog) = split_function(demangled.as_str());

                let (return_type, remaining) = parse_name(prolog);
                let Name { namespace, name } = if !remaining.is_empty() {
                    let (qualified_name, remaining) = parse_name(remaining);
                    assert!(remaining.is_empty());
                    qualified_name
                } else {
                    return_type
                };

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
        panic!("Tried to split non-function symbol {demangled_fn}");
    } else {
        unreachable!("This branch indicates mismatched parentheses, which would be a demangler bug");
    }
}

struct Name {
    namespace: String,
    name: String,
}

// Operators which are ambiguous in the context of templates or function types
static AMBIGUOUS_OPERATORS: [&'static str; 11] = [
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
    "()",
    ">",
    "<",
];

fn parse_name(text: &str) -> (Name, &str) {
    let mut components = Vec::<String>::new();

    let mut current_name = String::new();
    // let mut name_start = 0;
    let mut final_pos = text.len();

    let mut template_depth = 0;
    let mut parentheses_depth = 0;
    let mut end_of_name = false;

    let mut iter = text.char_indices();
    'next_char: while let Some((pos, char)) = iter.next() {
        'push_char: {
            match char {
                ':' => {
                    // Skip while inside a template
                    if template_depth > 0 {
                        break 'push_char;
                    }

                    // Verify that this is not a separator directly following another separator
                    if current_name.is_empty() {
                        panic!("malformed namespace separator at {pos}: {text}");
                    }

                    // Get second character of namespace separator
                    let Some((_, ':')) = iter.next() else {
                        panic!("malformed namespace separator at {pos}: {text}");
                    };

                    components.push(current_name);

                    current_name = String::new();
                    end_of_name = false;
                    continue 'next_char;
                },
                ' ' => {
                    // Skip while inside a template or function type
                    if template_depth > 0 || parentheses_depth > 0 {
                        break 'push_char;
                    }

                    // Check if we're approaching a function pointer type
                    if pos + 1 < text.len() && text[pos + 1..].starts_with('(') {
                        // DataNode (*)(DataArray*)
                        //  we are ^-- here
                        break 'push_char;
                    }

                    final_pos = pos + 1;
                    break 'next_char;
                },

                // Handle reference/pointer modifiers at the end of a name
                char if end_of_name => match char {
                    '&' => break 'push_char,
                    '*' => break 'push_char,
                    _ => panic!("expected namespace separator at {pos}: {text}"),
                },

                '<' => {
                    // Skip while inside a function type
                    if parentheses_depth > 0 {
                        break 'push_char;
                    }

                    template_depth += 1
                },
                '>' => {
                    // Skip while inside a function type
                    if parentheses_depth > 0 {
                        break 'push_char;
                    }

                    template_depth -= 1;
                    if template_depth == 0 {
                        // End of template, expect a name separator next
                        end_of_name = true;
                    }
                },

                '(' => {
                    // Skip while inside a template
                    if template_depth > 0 {
                        break 'push_char;
                    }

                    // Function pointer type
                    // DataNode (*)(DataArray*)
                    //   we are ^-- here

                    if parentheses_depth == 0 {
                        let remaining = &text[pos..];
                        if remaining.starts_with("(*)(") {
                            // Function pointer type
                            iter.nth("(*)(".len() - 1).unwrap();
                            // not stable yet
                            // iter.advance_by("(*)(".len()).unwrap();
                        } else {
                            // Function signature part of function-static variable
                            // This is excluded from the namespace for better display in Ghidra
                            //
                            // this is technically never gonna be hit due to the compiler-generated
                            // symbol exclusion, but i can't be bothered to remove it lol
                            // leaving for posterity
                            let mut parentheses_depth = 0;
                            let mut parentheses_end = 0;
                            for (pos, char) in remaining.match_indices(['(', ')']) {
                                match char {
                                    "(" => parentheses_depth += 1,
                                    ")" => parentheses_depth -= 1,
                                    _ => ()
                                };

                                if parentheses_depth == 0 {
                                    parentheses_end = pos;
                                    break;
                                }
                            }

                            assert_eq!(parentheses_depth, 0, "unbalanced parentheses: {text}");

                            iter.nth(parentheses_end - 1).unwrap();
                            // not stable yet
                            // iter.advance_by(pos).unwrap();

                            continue 'next_char;
                        }
                    }

                    parentheses_depth += 1;
                }

                ')' => {
                    // Skip while inside a template
                    if template_depth > 0 {
                        break 'push_char;
                    }

                    parentheses_depth -= 1;
                    if parentheses_depth == 0 {
                        // End of function type, expect a name separator next
                        end_of_name = true;
                    }
                },

                _ => {
                    // Skip while inside a template or function type
                    if template_depth > 0 || parentheses_depth > 0 {
                        break 'push_char;
                    }

                    let remaining = &text[pos..];

                    fn consume_text(
                        iter: &mut std::str::CharIndices,
                        current_name: &mut String,
                        remaining: &str,
                        text: &str
                    ) {
                        current_name.push_str(&remaining[..text.len()]);
                        iter.nth(text.len() - 2).unwrap();
                        // not stable yet
                        // iter.advance_by(text.len() - 1).unwrap();
                    }

                    // Type qualifiers
                    if remaining.starts_with("const ") {
                        consume_text(&mut iter, &mut current_name, remaining, "const ");
                        continue 'next_char;
                    } else if remaining.starts_with("volatile ") {
                        consume_text(&mut iter, &mut current_name, remaining, "volatile ");
                        continue 'next_char;
                    } else if remaining.starts_with("unsigned ") {
                        consume_text(&mut iter, &mut current_name, remaining, "unsigned ");
                        continue 'next_char;
                    }
                    // long long
                    else if remaining.starts_with("long long") {
                        consume_text(&mut iter, &mut current_name, remaining, "long long");
                        continue 'next_char;
                    }
                    // Check for ambiguous operator names and handle them specially
                    else if remaining.starts_with("operator") {
                        if remaining.starts_with("operator ") {
                            // type conversion operator, such as
                            // operator unsigned long long
                            consume_text(&mut iter, &mut current_name, remaining, "operator ");
                            continue 'next_char;
                        }

                        consume_text(&mut iter, &mut current_name, remaining, "operator");

                        let operator_check = &remaining["operator".len()..];
                        for operator in AMBIGUOUS_OPERATORS {
                            if !operator_check.starts_with(operator) {
                                continue;
                            }

                            // Check for templated operators such as operator<<<int>
                            if operator_check.len() > operator.len() {
                                let template_start = &operator_check[operator.len()..];
                                // This is not the right operator if there is no template open at the end,
                                // or if there's more than one (the extras are part of the operator).
                                // This prevents operator<<int> from being detected as operator<<,
                                // other operator ambiguities are handled via the ordering in AMBIGUOUS_OPERATORS.
                                let lt_count = template_start.chars().take_while(|c| *c == '<').count();
                                if lt_count != 1 {
                                    continue;
                                }
                            }

                            iter.nth(operator.len() - 1).unwrap();
                            // iter.advance_by(operator.len()).unwrap();
                            current_name.push_str(&operator_check[..operator.len()]);
                            continue 'next_char;
                        }

                        continue 'next_char;
                    }

                    break 'push_char;
                },
            }
        }

        current_name.push(char);
    }

    assert_eq!(template_depth, 0, "unbalanced templates: {text}");
    assert_eq!(parentheses_depth, 0, "unbalanced parentheses: {text}");

    let name = Name {
        namespace: components.join(" :: "),
        name: current_name,
    };

    (name, &text[final_pos..])
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
    fn too_complex() {
        assert_eq!(
            &demangle_line("@LOCAL@__ct__3AppFiPPc@kESRBMs = .rodata:0x80B34BA8; // type:object size:0x4 scope:local align:4"),
            "0x80B34BA8|||@LOCAL@__ct__3AppFiPPc@kESRBMs"
        );
        assert_eq!(
            &demangle_line("@STRING@StaticClassName__12BudgetScreenFv = .data:0x80B4A358; // type:object size:0xD scope:weak align:4 data:string"),
            "0x80B4A358|||@STRING@StaticClassName__12BudgetScreenFv"
        );
        assert_eq!(
            &demangle_line("@GUARD@DrawRegular__3AppFv@_t = .sbss:0x80C79AC4; // type:object size:0x1 scope:local align:1 data:byte"),
            "0x80C79AC4|||@GUARD@DrawRegular__3AppFv@_t"
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

    #[test]
    fn shift_operator() {
        assert_eq!(
            &demangle_line("__rs__FR9BinStreamR6SfxMap = .text:0x8068FC80; // type:function size:0x38"),
            "0x8068FC80|||__rs__FR9BinStreamR6SfxMap|||operator>>(BinStream&, SfxMap&)||||||operator>>"
        );
    }

    #[test]
    fn call_operator() {
        assert_eq!(
            &demangle_line("__cl__11GoalAlpaCmpCF6Symbol6Symbol = .text:0x80188854; // type:function size:0x30"),
            "0x80188854|||__cl__11GoalAlpaCmpCF6Symbol6Symbol|||GoalAlpaCmp::operator()(Symbol, Symbol) const|||GoalAlpaCmp|||operator()"
        );
    }

    #[test]
    fn conversion_operator() {
        assert_eq!(
            &demangle_line("__opUx__Q26Quazal8DateTimeCFv = .text:0x8001281C; // type:function size:0x10"),
            "0x8001281C|||__opUx__Q26Quazal8DateTimeCFv|||Quazal::DateTime::operator unsigned long long(void) const|||Quazal :: DateTime|||operator unsigned long long"
        );
        assert_eq!(
            &demangle_line("__opP10RndMatAnim__31ObjPtr<10RndMatAnim,9ObjectDir>CFv = .text:0x80505E70; // type:function size:0x8 scope:global align:16"),
            "0x80505E70|||__opP10RndMatAnim__31ObjPtr<10RndMatAnim,9ObjectDir>CFv|||ObjPtr<RndMatAnim, ObjectDir>::operator RndMatAnim*(void) const|||ObjPtr<RndMatAnim, ObjectDir>|||operator RndMatAnim*"
        );
    }

    #[test]
    fn function_pointer() {
        assert_eq!(
            &demangle_line("DataRegisterFunc__F6SymbolPFP9DataArray_8DataNode = .text:0x8031B2B8; // type:function size:0x40"),
            "0x8031B2B8|||DataRegisterFunc__F6SymbolPFP9DataArray_8DataNode|||DataRegisterFunc(Symbol, DataNode (*)(DataArray*))||||||DataRegisterFunc"
        );
        assert_eq!(
            &demangle_line("__vc__Q211stlpmtx_std154map<6Symbol,PFP9DataArray_8DataNode,Q211stlpmtx_std13less<6Symbol>,Q211stlpmtx_std69StlNodeAlloc<Q211stlpmtx_std38pair<C6Symbol,PFP9DataArray_8DataNode>>>FRC6Symbol = .text:0x8031B2F8; // type:function size:0xFC"),
            "0x8031B2F8|||__vc__Q211stlpmtx_std154map<6Symbol,PFP9DataArray_8DataNode,Q211stlpmtx_std13less<6Symbol>,Q211stlpmtx_std69StlNodeAlloc<Q211stlpmtx_std38pair<C6Symbol,PFP9DataArray_8DataNode>>>FRC6Symbol|||stlpmtx_std::map<Symbol, DataNode (*)(DataArray*), stlpmtx_std::less<Symbol>, stlpmtx_std::StlNodeAlloc<stlpmtx_std::pair<const Symbol, DataNode (*)(DataArray*)>>>::operator[](const Symbol&)|||stlpmtx_std :: map<Symbol, DataNode (*)(DataArray*), stlpmtx_std::less<Symbol>, stlpmtx_std::StlNodeAlloc<stlpmtx_std::pair<const Symbol, DataNode (*)(DataArray*)>>>|||operator[]"
        );
    }
}
