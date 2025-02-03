import glob
import os
import subprocess

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


for file in glob.iglob("src/**/*.c", recursive=True):
    format_file(file)
for file in glob.iglob("src/**/*.cpp", recursive=True):
    format_file(file)
for file in glob.iglob("src/**/*.h", recursive=True):
    format_file(file)
for file in glob.iglob("src/**/*.hpp", recursive=True):
    format_file(file)
