#!/bin/bash
# Reset Linda Space for workers
rm ../workers/data.csv
rm ../workers/processes.csv

touch ../workers/data.csv
touch ../workers/processes.csv

printf "Space reset"