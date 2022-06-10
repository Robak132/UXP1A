#!/bin/bash
# Tests if after adding new tuple to Space, reading process is awaken and not timed-out.
# Results:
#   Waiting Time: 1 seconds, and space states: 1: 2:"aaa" - Correct
#   Waiting Time: 3 seconds, and space states: 1: 2:"aaa" - Reader process were not awaken
#   <Else>                                                - Uncorrect
./reset_workers_space.sh
cd ../../build

printf "\n"
wstart=$(date +%s)
sstart="$(cat ../tests/workers/data.csv)"
./reader aaa 3 &
sleep 1 
./outputer aaa
wend=$(date +%s)
send="$(cat ../tests/workers/data.csv)"
wait

printf "\nWaiting Time: $(($wend-$wstart)) seconds, and space states: 1:$sstart 2:$send\n"

