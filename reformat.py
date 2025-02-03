import glob
import os
import subprocess

directories = [
    os.path.join("src", "band3", "**"),
    os.path.join("src", "system", "**"),
    os.path.join("src", "network", "**"),
    "src",
]

with open(".clang-format-ignore") as ignore_file:
    def read_ignore_line(line: str) -> str:
        if line.startswith("#"):
            return ""
        return os.path.normpath(line.strip())

    ignore_directories = list(
        filter(
            lambda p: p != "",
            map(read_ignore_line, ignore_file.readlines()),
        )
    )


def format_file(file: str):
    for ignored in ignore_directories:
        prefix = os.path.commonpath((ignored, file))
        if prefix == ignored:
            print(f"Skipping {file}")
            return

    print(f"Reformatting {file}")
    subprocess.check_call(["clang-format", "-i", file])


for directory in directories:
    for file in glob.iglob(os.path.join(directory, "*.c")):
        format_file(file)
    for file in glob.iglob(os.path.join(directory, "*.cpp")):
        format_file(file)
    for file in glob.iglob(os.path.join(directory, "*.h")):
        format_file(file)
    for file in glob.iglob(os.path.join(directory, "*.hpp")):
        format_file(file)
    pass
