#!/bin/zsh

FILE = $1;

xxd -a -g 1 $1 > moitest
xxd -a -g 1 corewar-unit-tests/tests/asm/valid2/${FILE} > testbin

diff -q moitest testbin