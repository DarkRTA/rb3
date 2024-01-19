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
        let parts = line.split(" ").collect::<Vec<_>>();
        let sym = parts[0];

        let addr_idx = parts[2].find("0x").unwrap();
        let addr = &parts[2][addr_idx..addr_idx + 10];

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
