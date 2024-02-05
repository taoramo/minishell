#!/bin/bash

MINISHELL="../minishell -c "

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
OUTPUT_DIR=./tmp

BASH_OUTPUT=$OUTPUT_DIR/bash.out
MINISHELL_OUTPUT=$OUTPUT_DIR/mini.out

BASH_EXIT_CODE=0
MINISHELL_EXIT_CODE=0

check_output()
{
	cmp ${BASH_OUTPUT} ${MINISHELL_OUTPUT} && 
		echo -e ${GREEN}"$line: [OK]"${NC} || 
		(echo -e ${RED}"$line: [KO]"${NC}
		echo -e ${YELLOW}"bash:"${NC}
		cat $BASH_OUTPUT
		echo -e ${YELLOW}"minishell:"${NC}
		cat $MINISHELL_OUTPUT)
	rm ${BASH_OUTPUT}
	rm ${MINISHELL_OUTPUT}
}

check_exit_code()
{
	if [ ${BASH_EXIT_CODE} -eq ${MINISHELL_EXIT_CODE} ]
	then
		echo -e ${GREEN}"Exit code: [OK]"${NC}
	else
		echo -e ${YELLOW}"Exit code: [KO]"
		echo -e "bash: ${BASH_EXIT_CODE}"
		echo -e "minishell: ${EXMINISHELL_EXIT_CODEIT_CODE}"${NC}
	fi
}

#------ BASIC ------#

printf $HEADER_COLOR"\n#------ BASIC ------#\n\n"$NC

while read -r line; do
	eval $line > $BASH_OUTPUT
	eval $MINISHELL"\"$line\"" > $MINISHELL_OUTPUT
	check_output
done < $TEST_DIR/basic_tests.txt

#------ BUILT-IN ------#

printf $HEADER_COLOR"\n#------ BUILT-IN ------#\n\n"$NC

while read -r line; do
	eval $line > $BASH_OUTPUT
	# comment out $ and " for -c input
	line_commented=${line//\$/\\\$}
	line_commented=${line_commented//\"/\\\"}
	eval $MINISHELL"\"$line_commented\"" > $MINISHELL_OUTPUT
	check_output
done < $TEST_DIR/built_in_tests.txt

#------ INPUT ------#

printf $HEADER_COLOR"\n#------ INPUT ------#\n\n"$NC

while read -r line; do
	eval $line > $BASH_OUTPUT
	# comment out $ and " for -c input
	line_commented=${line//\$/\\\$}
	line_commented=${line_commented//\"/\\\"}
	eval $MINISHELL"\"$line_commented\"" > $MINISHELL_OUTPUT
	check_output
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
	eval $line > $BASH_OUTPUT
	# comment out $ and " for -c input
	line_commented=${line//\$/\\\$}
	line_commented=${line_commented//\"/\\\"}
	eval $MINISHELL"\"$line_commented\"" > $MINISHELL_OUTPUT
	check_output
done < $TEST_DIR/pipe_tests.txt

#------ && AND || ------#

printf $HEADER_COLOR"\n#------ && AND || ------#\n\n"$NC

cc $SRCS_DIR/true.c -o true
cc $SRCS_DIR/false.c -o false

while read -r line; do
	eval $line > $BASH_OUTPUT
	eval $MINISHELL"\"$line\"" > $MINISHELL_OUTPUT
	check_output
done < $TEST_DIR/and_or_tests.txt

#------ ERRORS ------#

printf $HEADER_COLOR"\n#------ ERRORS ------#\n\n"$NC

while read -r line; do
	eval $line > $BASH_OUTPUT
	BASH_EXIT_CODE=$(echo $?)
	eval $MINISHELL"\"$line\""  > $MINISHELL_OUTPUT
	MINISHELL_EXIT_CODE=$(echo $?)
	check_output
	check_exit_code
done < $TEST_DIR/errors.txt

echo ""