# Contributing

## Learning

Decompilation is a fairly advanced skill and can potentially take a long time to
learn. Having prior programming experience is highly recommended, but we are
more than willing to help you get up to speed.

If you want an overview of how the process works, take a peek at [MattKC's
video](https://youtu.be/MToTEqoVv3I?feature=shared) he made for the Lego Island
decompilation project. While not all of the information here applies to Rock
Band 3, the overall process still applies.

## Ghidra

We use [Ghidra](https://ghidra-sre.org/) for doing most of our reverse
engineering work. While we currently do not have a dedicated Ghidra server for
the project, There is a script for script for quickly reimporting symbols from
symbols.txt into your local ghidra project in `tools`.

## Text Ediors

[VSCode](https://code.visualstudio.com/)/[VSCodium](https://vscodium.com/) with
Microsoft's C++ plugin is the text editor we recommend newcomers use for this
project. However, you are more than welcome to use any text editor you'd like as
long as you have a good way of running `clang-format`.

## Guidelines

### Code formatting

Any code that is not from a third party library should be formatted with
`clang-format` before being submitted to the project. This avoids all questions
about code style and lets us focus on what's actually important: Decompiling the
game.

### Continious Integration

We make use of GitHub Actions to ensure all code merged to the repository
produces a matching binary. If your code fails CI, you will be asked to fix it
before it can be merged.

### Naming conventions.

We currently lack a formal set of naming conventions. The current advice is to
just try and follow what surrounding code does.
