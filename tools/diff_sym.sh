#!/bin/sh
git --no-pager diff --no-index \
	<(llvm-objdump -D --disassemble-symbols=$1 build/SZBE69/main.elf) \
	<(llvm-objdump -D --disassemble-symbols=$1 ignore/orig.elf)
