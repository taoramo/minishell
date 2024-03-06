#!/bin/bash

make
make clean

MINISHELL="./minishell -c "

LEAKS_OUT=leaks.out
TRASH_OUT=trash.out

run_command()
{
	echo "$line"
	line_commented=${line//\$/\\\$}
	line_commented=${line_commented//\"/\\\"}
	eval leaks --atExit -q -- $MINISHELL\"$line_commented\" 1> $LEAKS_OUT
	LEAKS=$( grep "total leaked bytes" $LEAKS_OUT | awk '{print $3}' )
	echo $LEAKS
}

line="echo hello<leaks.sh"
run_command

line="echo \$USER < leaks.sh"
run_command

line="echo *"
run_command

line="echo *.sh"
run_command

line="echo *aadifjaosdijf"
run_command

line="echo hello | wc -l | echo hello"
run_command

line="cat < leaks.sh | echo hello | wc -l | echo hello"
run_command

line="echo hello && echo wow || (echo fail && echo fail2) && echo ok"
run_command

line="export x=wow && echo \$x && unset x && echo \$x"
run_command

line="export x=wow && echo \$x && export x=123 && echo \$x && export x+=mom && echo \$x"
run_command

line="/bin/ls"
run_command

line="pwd && cd .. && pwd && cd && pwd"
run_command
