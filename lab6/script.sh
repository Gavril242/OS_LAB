#!/bin/bash

# check if an argument was provided
if [ -z "$1" ]
then
  echo "Please provide the name of a .c file as an argument."
  exit 1
fi

# extract the filename without extension
filename=$(basename -- "$1")
extension="${filename##*.}"
filename="${filename%.*}"

# compile the .c file and capture the output
output=$(gcc -Wall -Wextra "$1" 2>&1)

# check if the compilation was successful
if [ $? -eq 0 ]
then
  echo "Compilation successful."
else
  echo "Compilation failed with errors:"
  echo "$output"
fi

# check for warnings in the output
if echo "$output" | grep -iq 'warning'
then
  echo "Warnings:"
  echo "$output" | grep -i 'warning'
fi
errors=$(echo "$output" | grep -c 'error')
warnings=$(echo "$output" | grep -c 'warning')

# print the total number of errors and warnings
echo "Total errors: $errors"
echo "Total warnings: $warnings"
