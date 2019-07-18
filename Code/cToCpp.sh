#!/bin/bash

# Rename all file of extension argument 2 to argument 3 from folder argument 1

count=0
for f in $1/*.$2; do 

    mv -- "$f" "${f%.$2}.$3"
    count=$[count + 1]

done

echo Changed extension of $count files from folder $1, $2 to $3
