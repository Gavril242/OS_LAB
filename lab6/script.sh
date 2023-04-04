#!/bin/bash

# create 5 random text files
for i in {1..5}; do
    filename="file$i.txt"
    size=$((RANDOM % 1000 + 1)) # random size between 1 and 1000 bytes
    dd if=/dev/urandom of=$filename bs=$size count=1 > /dev/null 2>&1 # generate random text
done

# create 2 symbolic links to random files
ln -s $(ls | shuf -n 1) link1.txt
ln -s $(ls | shuf -n 1) link2.txt

echo "Files and symbolic links created successfully!"
