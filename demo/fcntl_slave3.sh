#!/bin/bash

cd ../user_program

echo "Demo fcntl my_input"
cd ../output/my_output
sudo ../../user_program/slave 5 fcntl_out fcntl 127.0.0.1
for i in {1..5}
do
  diff -a fcntl_out_$i ../../input/my_input/in_$i > /dev/null 2>&1
  if [ $? -eq 0 ]
  then
    echo "in_${i} and fcntl_out_${i} are similar."
  fi
done
