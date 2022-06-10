#!/bin/bash
# Tests if file is correctly cleared from any tuples that input got and preceeds unwanted growth of file size. 
# Results:
#   Elapsed Time: 2 seconds - Correct
#   <Else>                  - Uncorrect
./reset_workers_space.sh
cd ../../build

./outputer aaa 
before="$(cat ../tests/workers/data.csv)"
./inputer aaa 2
after="$(cat ../tests/workers/data.csv)"
printf "Inside of space before:$before after:$after"

