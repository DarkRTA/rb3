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

## Using AI
Let's get this out of the way right now: I am not completely against the usage of AI. In fact, I'd argue one of its better uses is as a permuter for close-to-100% functions. But with that all being said, if you are going to use an LLM to decomp, there are some things to keep in mind:

- First and foremost, **AI is NOT a substitute for familiarizing yourself with the workflow**. In our experience, while AI does have the potential to get things right, it also frequently generates code that a human would be unlikely to write (i.e. pointer offsets), and we spend more time having to review the poor quality AI code than we would an entirely human PR submission. If you intend to throw this decomp at a series of agents and let them run wild instead of learning the general decomp process, or at least trying a function or two manually by yourself first, this is not the project for you. In other words, **purely "agentic" PRs with no human involvement will be rejected, and the submitter banned from the repo.**
- You must also keep in mind: the AI can NOT reference leaked material. We are trying to keep this decomp as clean room as possible. For this reason, it would be best to use an offline or local LLM.
- You must use a local, open weights LLM. All usage of cloud models is strictly forbidden.
- You must disclose your usage of AI in your contribution. Specifically, you must disclose the model you used, and how much of your PR the AI was involved in (did it clean up a few minor mismatches, or did you have it completely do several functions from zero?)
- The PR body **must** be human-written. Reviewers don't want to read an AI-generated description.
  - Furthermore, you must be able to understand and explain the code contained in your PR. And I don't mean "ask your LLM to explain the code", I mean you, the human.
- You must NOT submit any AI-tailored markdowns (CLAUDE.md, AGENTS.md, etc). If any are spotted in your PR, it will be rejected.

We can, and have, accepted AI code in the past, but the code still needs to be up to the quality that we expect from human contributions. Overall, **AI should *augment* your ability to decomp, not *replace* it entirely**. Thus, any obvious signs of AI slop or lack of meaningful review of AI generated code will result in a ban from future contributions.

## Conclusion

That's the general gist! We’re happy you have an interest in contributing and can’t wait to see what you uncover! If you have any further questions, reach out to us on the [MiloHax discord](https://discord.gg/milohax) (for general milo engine knowledge/interest) or the [GC/Wii Decompilation Discord](https://discord.gg/hKx3FJJgrV).
