#!/bin/bash

max_id=$1
id=1

while [ $id -le $max_id ]; do
    echo "string${id}" >> lines.txt
    id=$((id+1))
done
