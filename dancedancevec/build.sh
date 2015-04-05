#!/bin/bash
##
##  Created by Martin White 2014
##  Copyright (c) 2014 Martin White. All rights reserved.
##
##	Permission is hereby granted, free of charge, to any person obtaining a
##	copy of this software and associated documentation files (the
##	"Software"), to deal in the Software without restriction, including
##	without limitation the rights to use, copy, modify, merge, publish,
##	distribute, sublicense, and/or sell copies of the Software, and to
##	permit persons to whom the Software is furnished to do so, subject to
##	the following conditions:
##
##	The above copyright notice and this permission notice shall be included
##	in all copies or substantial portions of the Software.
##
##	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
##	OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
##	MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
##	IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
##	CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
##	TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
##	SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
##
##
#########  MAKE SURE ASSEMBLER FILES ARE .S    #########
#########     OR THEY'LL BE LOST ON CLEAN      #########

SRC=src
INC=include
OBJ=intermediate

echo "ACTION: $ACTION"

function errorTrap()
{
	rc=$?
	exit $rc
}

trap errorTrap ERR;

# IF Clean
case "$1" in
    clean)
        rm -f $OBJ/*
		rm -f *.bin
		rm -f dancedancevec.lst
        ;;
    *)
        # Assemble CRT0
		echo "Assembling CRT stub..."
		/usr/local/bin/as6809 -logpcb $OBJ/crt0 src/crt0.s

        # Compile main program to assembler
		echo "Compiling C to ASM..."
        /usr/local/bin/m6809-cc1 -I$INC \
			$SRC/main.c \
			-dumpbase $SRC/main.c  \
			-mno-direct -mint8 -msoft-reg-count=0 -auxbase main \
			-O3 -o $OBJ/main.s

		# Assemble main code
		echo "Assembling main code..."
		/usr/local/bin/as6809 -logpcb $OBJ/main.s

		# Link it all up
		echo "Linking..."
        /usr/local/bin/aslink -m -nwsu -b .text=0x0 $OBJ/main.s19 $OBJ/crt0.rel $OBJ/main.rel

		# Make Vectrex binary
		echo "Converting output to Vectrex binary..."
		/usr/local/bin/srec_cat $OBJ/main.s19 -o dancedancevec.bin -binary

		# Create a version of the LST file for use with ParaJVD
        # mono /usr/local/bin/lstcat $OBJ/crt0.lst $OBJ/main.lst gorfian.lst
        open -a ParaJVE dancedancevec.bin
esac
