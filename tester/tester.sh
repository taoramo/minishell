#!/bin/bash

cd ..
make
cd tester

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

LEAKS_LOG=tmp/leaks.log
TRASH_LOG=tmp/trash.log

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
	rm -f ${BASH_OUTPUT}
	rm -f ${MINISHELL_OUTPUT}
}

check_exit_code()
{
	if [ ${BASH_EXIT_CODE} -eq ${MINISHELL_EXIT_CODE} ]
	then
		echo -e ${GREEN}"Exit code: [OK]"${NC}
	else
		echo -e ${YELLOW}"Exit code: [KO]"
		echo -e "bash: ${BASH_EXIT_CODE}"
		echo -e "minishell: ${MINISHELL_EXIT_CODE}"${NC}
	fi
}

check_leaks()
{
	a=a
	# leaks --atExit -q -- $MINISHELL"\"$line_commented\"" 1>$LEAKS_LOG 2>$TRASH_LOG
	# LEAKS=$( grep "total leaked bytes" $LEAKS_LOG | awk '{print $3}' )
	# if [ $LEAKS -eq 0 ]; then
	# 	echo -e ${GREEN}"leaks: [OK]"${NC}
	# else
	# 	echo -e ${RED}"leaks: [KO]"${NC}
	# 	cat $LEAKS_LOG
	# fi
}

#------ BASIC ------#

printf $HEADER_COLOR"\n#------ BASIC ------#\n\n"$NC

while read -r line; do
	eval $line > $BASH_OUTPUT
	eval $MINISHELL"\"$line\"" > $MINISHELL_OUTPUT
	check_output
	check_leaks
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
	check_leaks
done < $TEST_DIR/built_in_tests.txt

line="exit"
echo $line
../minishell -c "exit" > $MINISHELL_OUTPUT 2>$TRASH_LOG
MINISHELL_EXIT_CODE=$(echo $?)
BASH_EXIT_CODE=0
check_exit_code

line="exit 42"
echo $line
../minishell -c "exit 42" > $MINISHELL_OUTPUT 2>$TRASH_LOG
MINISHELL_EXIT_CODE=$(echo $?)
BASH_EXIT_CODE=42
check_exit_code

line="exit asd"
echo $line
../minishell -c "exit asd" > $MINISHELL_OUTPUT 2>$TRASH_LOG
MINISHELL_EXIT_CODE=$(echo $?)
BASH_EXIT_CODE=255
check_exit_code

line="exit 100 200"
echo $line
../minishell -c "exit 100 200" > $MINISHELL_OUTPUT 2>$TRASH_LOG
MINISHELL_EXIT_CODE=$(echo $?)
BASH_EXIT_CODE=1
check_exit_code

#------ REDIRECT ------#

printf $HEADER_COLOR"\n#------ REDIRECT ------#\n\n"$NC

while read -r line; do
	eval $line > $BASH_OUTPUT
	rm -f tmp/outfile
	rm -f tmp/outfile2
	rm -f out1
	rm -f out2
	rm -f out3
	rm -f out4
	rm -f out5
	rm -f out6
	rm -f out7
	rm -f out8
	rm -f out9
	rm -f out10
	# comment out $ and " for -c input
	line_commented=${line//\$/\\\$}
	line_commented=${line_commented//\"/\\\"}
	eval $MINISHELL"\"$line_commented\"" > $MINISHELL_OUTPUT
	rm -f tmp/outfile
	rm -f tmp/outfile2
	rm -f out1
	rm -f out2
	rm -f out3
	rm -f out4
	rm -f out5
	rm -f out6
	rm -f out7
	rm -f out8
	rm -f out9
	rm -f out10
	check_output
	check_leaks
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
	check_leaks
done < $TEST_DIR/pipe_tests.txt

#------ INPUT ------#

printf $HEADER_COLOR"\n#------ INPUT ------#\n\n"$NC

while read -r line; do
	eval $line > $BASH_OUTPUT
	# comment out $ and " for -c input
	line_commented=${line//\$/\\\$}
	line_commented=${line_commented//\"/\\\"}
	eval $MINISHELL"\"$line_commented\"" > $MINISHELL_OUTPUT
	check_output
	check_leaks
done < $TEST_DIR/input_tests.txt

rm -f infile1
rm -f infile2

#------ RETURN VALUE ------#

printf $HEADER_COLOR"\n#------ RETURN VALUE ------#\n\n"$NC

while read -r line; do
	eval $line > $BASH_OUTPUT 2> $TRASH_LOG
	# comment out $ and " for -c input
	line_commented=${line//\$/\\\$}
	line_commented=${line_commented//\"/\\\"}
	eval $MINISHELL"\"$line_commented\"" > $MINISHELL_OUTPUT 2> $TRASH_LOG
	check_output
	check_leaks
done < $TEST_DIR/return_value_tests.txt

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
	check_leaks
done < $TEST_DIR/and_or_tests.txt

#------ ERRORS ------#

printf $HEADER_COLOR"\n#------ ERRORS ------#\n\n"$NC

echo "echo hello" > tmp/noaccess
chmod -rwx tmp/noaccess
echo "echo hello" > tmp/noread
chmod -r tmp/noread
echo "echo hello" >  tmp/nowrite
chmod -w tmp/nowrite
echo "echo hello" >  tmp/noexec
chmod -x tmp/noexec

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
	check_leaks
done < $TEST_DIR/errors.txt

line="echo hello >\$HOME/out"
line_commented=${line//\$/\\\$}
line_commented=${line_commented//\"/\\\"}
eval $MINISHELL"\"$line_commented\"" > $MINISHELL_OUTPUT
eval echo >$NOTEXIST > $BASH_OUTPUT
touch $BASH_OUTPUT
check_output
check_leaks

rm -f ls

#------ WILDCARDS ------#

printf $HEADER_COLOR"\n#------ WILDCARDS ------#\n\n"$NC

while read -r line; do
	eval $line > $BASH_OUTPUT
	# comment out $ and " for -c input
	line_commented=${line//\$/\\\$}
	line_commented=${line_commented//\"/\\\"}
	eval $MINISHELL"\"$line_commented\"" > $MINISHELL_OUTPUT
	check_output
	check_leaks
done < $TEST_DIR/wildcard_tests.txt

# cases differ from actual bash because of limitations
line="echo \$HOME*"
line_commented=${line//\$/\\\$}
line_commented=${line_commented//\"/\\\"}
eval $MINISHELL"\"$line_commented\"" > $MINISHELL_OUTPUT
echo $HOME'*' > $BASH_OUTPUT
check_output
check_leaks

line="echo \"\$HOME*\""
line_commented=${line//\$/\\\$}
line_commented=${line_commented//\"/\\\"}
eval $MINISHELL"\"$line_commented\"" > $MINISHELL_OUTPUT
eval echo $NOTEXIST > $BASH_OUTPUT
check_output
check_leaks


rm -f tmp/noaccess
rm -f tmp/noread
rm -f tmp/nowrite
rm -f tmp/noexec

rm -f a
rm -f b
rm -f c

rm -f asd*

rm -f out

echo ""