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

#------ BASIC ------#

printf $HEADER_COLOR"\n#------ BASIC ------#\n\n"$NC

echo -e $COMMAND_COLOR"echo hello"$NC
echo hello

#------ && AND || ------#

printf $HEADER_COLOR"\n#------ && AND || ------#\n\n"$NC

while read -r line; do
	echo -e $COMMAND_COLOR $line $NC
	eval $line
done < "and_or_tests.txt"