#!/bin/bash
# Scripts that runs all the tests. Go to script with single test for it's description.

printf "START TESTS... \n"

green=$(tput setaf 2)
red=$(tput setaf 1)
normal=$(tput sgr0)

END_TEST_NUMBER=3
declare -A test_output
declare -A expected_output

printf "  0: Testing timeout\n"
expected_output[0]="Elapsed Time: 2 seconds"
test_output[0]=$(./test_timeout.sh | grep "Elapsed Time")

printf "  1: Testing correct removal from space\n"
expected_output[1]="Inside of space before:\"aaa\" after:"
test_output[1]=$(./test_empty_after_input.sh | grep "Inside of space")

printf "  2: Testing parrel waiting for data\n"
expected_output[2]="Waiting Time: 1 seconds, and space states: 1: 2:\"aaa\""
test_output[2]=$(./test_waiting_for_data.sh | grep "Waiting Time")

printf "  3: Testing semaphor awaking by queue \n"
expected_output[3]="Semaphor Time: 3 seconds"
test_output[3]=$(./test_semaphor_queue.sh | grep "Semaphor Time")

printf "\nRESULTS:\n"
for i in $(seq 0 $END_TEST_NUMBER); do
if [ "${test_output[$i]}" = "${expected_output[$i]}" ]; then
    printf "%10s\n" "${green}  $i: positive${normal}"
else 
    printf "%10s\n" "${red}  $i: negative:  ${test_output[$i]} != ${expected_output[$i]} ${normal}"
fi 
    
done

