#!/bin/bash

cd ../user_program

echo "Demo fcntl sample_input_1"
cd ../output/sample_output_1
sudo ../../user_program/slave 10 fcntl_received_file fcntl 127.0.0.1
for i in {1..10}
do
  diff -a fcntl_received_file_$i ../../input/sample_input_1/target_file_$i > /dev/null 2>&1
  if [ $? -eq 0 ]
  then
    echo "target_file_${i} and fcntl_received_file_${i} are similar."
  fi
done
