#!/bin/bash

# Colors
NC='\033[0m'
GREEN='\033[0;32m'
LGREEN='\033[1;32m'
RED='\033[0;31m'
CYAN='\033[0;36m'
LCYAN='\033[1;36m'
YELLOW='\033[0;33m'

HEADER_COLOR=$LCYAN
COMMAND_COLOR=$CYAN

TEST_DIR=./tests
SRCS_DIR=./srcs

#------ BUILT-IN ------#

printf $HEADER_COLOR"\n#------ BUILT-IN ------#\n\n"$NC

while read -r line; do
	echo -e $COMMAND_COLOR $line $NC
	eval $line
done < $TEST_DIR/built_in_tests.txt

#------ BASIC ------#

printf $HEADER_COLOR"\n#------ BASIC ------#\n\n"$NC

while read -r line; do
	echo -e $COMMAND_COLOR $line $NC
	eval $line
done < $TEST_DIR/basic_tests.txt

#------ INPUT ------#

printf $HEADER_COLOR"\n#------ INPUT ------#\n\n"$NC

while read -r line; do
	echo -e $COMMAND_COLOR $line $NC
	eval $line
done < $TEST_DIR/input_tests.txt

#------ REDIRECT ------#

printf $HEADER_COLOR"\n#------ REDIRECT ------#\n\n"$NC

echo "aaaaa" > ./tmp/outfile
echo "bbbbb" > ./tmp/outfile2
cat ./tmp/outfile
cat ./tmp/outfile2
echo ""

while read -r line; do
	echo "aaaaa" > ./tmp/outfile
	echo "bbbbb" > ./tmp/outfile2
	echo -e $COMMAND_COLOR $line $NC
	eval $line
	echo -e cat ./tmp/outfile
	cat ./tmp/outfile
	echo -e cat ./tmp/outfile2
	cat ./tmp/outfile2
	echo ""
done < $TEST_DIR/redirect_tests.txt

#------ PIPES ------#

printf $HEADER_COLOR"\n#------ PIPES ------#\n\n"$NC

while read -r line; do
	echo -e $COMMAND_COLOR $line $NC
	eval $line
done < $TEST_DIR/pipe_tests.txt

#------ && AND || ------#

printf $HEADER_COLOR"\n#------ && AND || ------#\n\n"$NC

cc $SRCS_DIR/true.c -o true
cc $SRCS_DIR/false.c -o false

while read -r line; do
	echo -e $COMMAND_COLOR $line $NC
	eval $line
done < $TEST_DIR/and_or_tests.txt

rm true
rm false