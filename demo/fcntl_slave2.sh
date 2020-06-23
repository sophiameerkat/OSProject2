#!/bin/bash

cd ../user_program

echo "Demo fcntl sample_input_2"
cd ../output/sample_output_2
sudo ../../user_program/slave 1 fcntl_received_file fcntl 127.0.0.1
diff -a fcntl_received_file ../../input/sample_input_2/target_file > /dev/null 2>&1
if [ $? -eq 0 ]
then
  echo "target_file and fcntl_received_file are similar."
fi
