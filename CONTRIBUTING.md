# Contributing

## Learning

Decompilation is a fairly advanced skill and can potentially take a long time to
learn. Having prior programming experience (especially with C++) is highly recommended, but we are
more than willing to help you get up to speed.

If you want an overview of how the process works, take a peek at [MattKC's
video](https://youtu.be/MToTEqoVv3I?feature=shared) he made for the Lego Island
decompilation project. While obviously not everything covered in this video will apply to Rock
Band 3, it still provides a good summary of how decompilation projects usually work.

## Ghidra

We use [Ghidra](https://ghidra-sre.org/) with the [GameCube loader extension](https://github.com/Cuyler36/Ghidra-GameCube-Loader) for doing most of our reverse
engineering work. While we currently do not have a dedicated Ghidra server for
the project, there is a script for quickly reimporting symbols from
symbols.txt into your local Ghidra project in `tools`.

## Text Editors

For newcomers to these types of projects, we recommend [VSCode](https://code.visualstudio.com/)/[VSCodium](https://vscodium.com/) with
Microsoft's C++ plugin. However, you may use any text editor you prefer as
long as you have a good way of running `clang-format`.

## Guidelines

### Code formatting

Any code that is not from a third party library should be formatted with
`clang-format` before being submitted to the project. This avoids all questions
about code style and allows us to focus on what's actually important: decompiling the
game.

### Continuous Integration

We make use of GitHub Actions to ensure all code merged to the repository
produces a matching binary. If your code fails CI, you must fix it
before it can be merged.

### Naming conventions

We currently lack a formal set of naming conventions. The current advice is to
just try and follow what surrounding code does.

## Further questions

If you have any further questions, feel free to join the [GC/Wii Decompilation Discord](https://discord.gg/hKx3FJJgrV).
