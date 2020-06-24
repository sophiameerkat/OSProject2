#!/bin/bash

cd ../user_program

echo "Demo mmap sample_input_2"
cd ../output/sample_output_2
sudo ../../user_program/slave 1 mmap_received_file mmap 127.0.0.1
diff -a mmap_received_file_1 ../../input/sample_input_2/target_file_1 > /dev/null 2>&1
if [ $? -eq 0 ]
then
  echo "target_file_1 and mmap_received_file_1 are similar."
fi
