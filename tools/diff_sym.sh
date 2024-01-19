#!/bin/sh
git --no-pager diff --no-index \
	<(build/binutils/powerpc-eabi-objdump -D --disassemble-symbols=$1 build/SZBE69/main.elf) \
	<(build/binutils/powerpc-eabi-objdump -D --disassemble-symbols=$1 ignore/orig.elf)
