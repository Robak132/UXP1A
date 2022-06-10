#!/bin/bash
# Tests if read and input can't delete from empty file, and if the timeouts are working correctly
# Results:
#   Elapsed Time: 2 seconds - Correct
#   <Else>                  - Uncorrect

./reset_workers_space.sh
cd ../../build
printf "Setting Timeout for 2 seconds"
start=$(date +%s)
./reader aaa 2 &
./inputer aaa 2
end=$(date +%s)
printf "\nElapsed Time: $(($end-$start)) seconds\n"
