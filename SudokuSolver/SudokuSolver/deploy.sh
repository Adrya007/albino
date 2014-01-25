#!/bin/sh
scons -c
scons
if [ -d ~/web2py/applications/sudoku/ ]; then
	rm -r ~/web2py/applications/sudoku/
fi
cp -r app/ ~/web2py/applications/sudoku/
