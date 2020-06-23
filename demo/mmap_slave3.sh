#!/bin/bash

cd ../user_program

echo "Demo mmap my_input"
cd ../output/my_output
sudo ../../user_program/slave 5 mmap_out mmap 127.0.0.1
for i in {1..5}
do
  diff -a out_$i ../../input/my_input/in_$i > /dev/null 2>&1
  if [ $? -eq 0 ]
  then
    echo "in_${i} and mmap_out_${i} are similar."
  fi
done
