#!/bin/bash

cd ..
make
cd ./tester

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

# cases differ from actual bash because of limitations
line="echo \$HOME*"
line_commented=${line//\$/\\\$}
line_commented=${line_commented//\"/\\\"}
eval $MINISHELL"\"$line_commented\"" > $MINISHELL_OUTPUT
echo $HOME'*' > $BASH_OUTPUT
check_output

line="echo \"\$HOME*\""
line_commented=${line//\$/\\\$}
line_commented=${line_commented//\"/\\\"}
eval $MINISHELL"\"$line_commented\"" > $MINISHELL_OUTPUT
echo $NOTEXIST > $BASH_OUTPUT
check_output

rm -f infile1
rm -f infile2

#------ REDIRECT ------#

printf $HEADER_COLOR"\n#------ REDIRECT ------#\n\n"$NC

while read -r line; do
	eval $line > $BASH_OUTPUT
	rm -f tmp/outfile
	rm -f tmp/outfile2
	# comment out $ and " for -c input
	line_commented=${line//\$/\\\$}
	line_commented=${line_commented//\"/\\\"}
	eval $MINISHELL"\"$line_commented\"" > $MINISHELL_OUTPUT
	rm -f tmp/outfile
	rm -f tmp/outfile2
	check_output
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
	# comment out $ and " for -c input
	line_commented=${line//\$/\\\$}
	line_commented=${line_commented//\"/\\\"}
	eval $MINISHELL"\"$line_commented\"" > $MINISHELL_OUTPUT
	check_output
done < $TEST_DIR/and_or_tests.txt

#------ ERRORS ------#

printf $HEADER_COLOR"\n#------ ERRORS ------#\n\n"$NC

touch tmp/noaccess
chmod -rwx tmp/noaccess
touch tmp/noread
chmod -r tmp/noread
touch tmp/nowrite
chmod -w tmp/nowrite

while read -r line; do
	eval $line > $BASH_OUTPUT
	BASH_EXIT_CODE=$(echo $?)
	# comment out $ and " for -c input
	line_commented=${line//\$/\\\$}
	line_commented=${line_commented//\"/\\\"}
	eval $MINISHELL"\"$line_commented\""  > $MINISHELL_OUTPUT
	MINISHELL_EXIT_CODE=$(echo $?)
	check_output
	check_exit_code
done < $TEST_DIR/errors.txt

rm -f tmp/noaccess
rm -f tmp/noread
rm -f tmp/nowrite

rm -f a
rm -f b
rm -f c
rm -f "outfile && echo hello > outfile && cat outfile"

rm -f asd*

echo ""