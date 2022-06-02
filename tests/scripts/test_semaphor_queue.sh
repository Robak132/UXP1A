#!/bin/bash
# Tests if processes that were born after each other are awaken in correct order
# Results:
#   Semaphor Time: 3 seconds    - Correct - Second process in queue waited till timeout
#   Semaphor Time: 5 seconds    - Uncorrect - First process in queue waited till timeout
#   <Else>                      - Uncorrect
./reset_workers_space.sh
cd ../../build

nstart=$(date +%s)
./inputer aaa 5 &
sleep 0.1 
./reader aaa 3 &
sleep 1 
./outputer aaa
wait
nend=$(date +%s)

printf "\nSemaphor Time: $(($nend-$nstart)) seconds"


