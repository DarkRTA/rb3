#!/usr/bin/env python3

# A quick-and-dirty script to split the output of `dtk dwarf dump` into individual files.
# Currently only works with dumps that have a multi-line comment block delimiting each file:
# /*
#     Compile unit: ...
#     Producer: ...
#     Language: ...
#     Code range: ... -> ...
# */

import os
import argparse

from pathlib import Path
from typing import Optional

parser = argparse.ArgumentParser()
parser.add_argument(
    "input",
    type=Path,
    help="input dump file to split",
)
parser.add_argument(
    "output",
    type=Path,
    help="directory to output splits to",
)

args = parser.parse_args()
input_file: Path = args.input
output_dir: Path = args.output

if not input_file.exists():
    print(f"Input path {input_file.resolve()} does not exist")
    exit()

if not input_file.is_file():
    print(f"Input path {input_file.resolve()} is not a file")
    exit()

if not output_dir.exists():
    output_dir.mkdir(parents=True)
elif not output_dir.is_dir():
    print(f"Output path {output_dir.resolve()} is not a directory")
    exit()

dump_text = input_file.read_text()

BLOCK_START = "/*"
BLOCK_END   = "*/"

FILE_PATH_PROLOG = "Compile unit: "
CODE_RANGE_PROLOG = "Code range: "
CODE_RANGE_SPLIT = " -> "

class CompileUnitInfo:
    def __init__(self):
        self.unit_path = ""
        self.text_start = -1
        self.text_end = -1
        self.split_start = -1
        self.split_end = -1

def print_file_error(file_text: str, index: int, msg: str):
    line_number = file_text.count('\n', 0, index) + 1
    print(f"{line_number}: {msg}")

print("Splitting input file...")
compile_units: list[CompileUnitInfo] = []
current_unit: Optional[CompileUnitInfo] = None
search_start_index = 0
while True:
    start_index = dump_text.find(BLOCK_START, search_start_index)
    if start_index < 0:
        break

    end_index = dump_text.find(BLOCK_END, start_index + len(BLOCK_START))
    if end_index < 0:
        print_file_error(dump_text, start_index, "Unterminated block comment")
        exit()
    end_index = end_index + len(BLOCK_END)

    comment_block = dump_text[start_index:end_index]
    search_start_index = end_index

    path_index = comment_block.find(FILE_PATH_PROLOG)
    if (path_index < 0):
        continue
    path_index = path_index + len(FILE_PATH_PROLOG)
    newline_index = comment_block.find('\n', path_index)
    compile_unit_path = comment_block[path_index:newline_index].strip()

    code_range_index = comment_block.find(CODE_RANGE_PROLOG)
    if (code_range_index < 0):
        print_file_error(dump_text, start_index, "Missing code range info")
        exit()
    code_range_index = code_range_index + len(CODE_RANGE_PROLOG)
    newline_index = comment_block.find('\n', code_range_index)
    code_range = comment_block[code_range_index:newline_index].split(CODE_RANGE_SPLIT)

    if current_unit is not None:
        current_unit.text_end = start_index
        compile_units.append(current_unit)
        current_unit = None

    current_unit = CompileUnitInfo()
    current_unit.unit_path = compile_unit_path
    current_unit.text_start = start_index
    current_unit.split_start = int(code_range[0], 16)
    current_unit.split_end = int(code_range[1], 16)

if current_unit is not None:
    current_unit.text_end = len(dump_text)
    compile_units.append(current_unit)
    current_unit = None

if len(compile_units) < 1:
    print("No splits parsed")
    exit()

print("Finding common prefix...")
splits: list[tuple] = []
prefix = compile_units[0].unit_path
for unit in compile_units:
    prefix = os.path.commonprefix([unit.unit_path, prefix])
print(f"Common prefix: {prefix}")

splits_file = output_dir.joinpath("splits.txt").open("w")
splits_file.write("""
Sections:
	.text       type:code

""")

print("Writing split files...")
for unit in compile_units:
    output_path = unit.unit_path.removeprefix(prefix)
    splits_file.write(f"""
{output_path}:
	.text       start:0x{unit.split_start:8X} end:0x{unit.split_end:8X}

""")

    output_joined = output_dir.joinpath(output_path)
    output_joined.parent.mkdir(parents=True, exist_ok=True)
    output_joined.write_text(dump_text[unit.text_start:unit.text_end])
    # print(output_joined.as_posix())

print("Done!")
