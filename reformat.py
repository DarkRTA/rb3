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
    ignore_directories = list(
        map(lambda p: os.path.normpath(p.strip()), ignore_file.readlines())
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
