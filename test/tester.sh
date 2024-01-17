#!/bin/bash

# Colors
NC='\033[0m'
GREEN='\033[0;32m'
LGREEN='\033[1;32m'
RED='\033[0;31m'
CYAN='\033[0;36m'
LCYAN='\033[1;36m'
YELLOW='\033[0;33m'

# while read -r line; do
# 	echo $line
# 	$line
# done < "and_or_tests.txt"

echo "./true 1 && ./true 2"
./true 1 && ./true 2
echo "./true 1 || ./true 2"
./true 1 || ./true 2
echo "./false 1 && ./true 2"
./false 1 && ./true 2
echo "./false 1 || ./true 2"
./false 1 || ./true 2

echo "./true 1 && ./true 2 || ./true 3"
./true 1 && ./true 2 || ./true 3
echo "./true 1 && ./false 2 || ./true 3"
./true 1 && ./false 2 || ./true 3
echo "./false 1 && ./true 2 || ./true 3"
./false 1 && ./true 2 || ./true 3
echo "./false 1 && ./false 2 || ./true 3"
./false 1 && ./false 2 || ./true 3

echo "./true 1 && ./true 2 || (./true 3 && ./false 4) || ./false 5 && ./true 6"
./true 1 && ./true 2 || (./true 3 && ./false 4) || ./false 5 && ./true 6
echo "./true 1 && ./true 2 || (./true 3 && ./false 4) || ./false 5 && ./true 6"
./true 1 && ./false 2 || (./true 3 && ./false 4) || ./false 5 && ./true 6
echo "./false 1 && ./true 2 || (./true 3 && ./false 4) || ./false 5 && ./true 6"
./false 1 && ./true 2 || (./true 3 && ./false 4) || ./false 5 && ./true 6