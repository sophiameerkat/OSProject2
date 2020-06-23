#!/bin/bash

cd ../user_program

echo "Demo mmap sample_input_2"
cd ../output/sample_output_2
sudo ../../user_program/slave 1 mmap_received_file mmap 127.0.0.1
diff -a mmap_received_file ../../input/sample_input_2/target_file > /dev/null 2>&1
if [ $? -eq 0 ]
then
  echo "target_file and mmap_received_file are similar."
fi
