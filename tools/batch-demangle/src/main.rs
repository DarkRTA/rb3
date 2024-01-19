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
        // let flags = remaining.split(' ').collect::<Vec<_>>();

        match demangle(sym, &DemangleOptions {
            omit_empty_parameters: false
        }) {
            Some(demangled) => {
                println!("{addr}|||{sym}|||{demangled}");
            },
            None => {
                println!("{addr}|||{sym}");
            }
        };
    }
}
