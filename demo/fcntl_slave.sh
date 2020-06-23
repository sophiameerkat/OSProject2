#!/bin/bash

cd ../user_program

echo "Demo fcntl sample_input_1"
cd ../output/sample_output_1
sudo ../../user_program/slave 10 fcntl_received_file_1 fcntl_received_file_2 fcntl_received_file_3 fcntl_received_file_4 fcntl_received_file_5 fcntl_received_file_6 fcntl_received_file_7 fcntl_received_file_8 fcntl_received_file_9 fcntl_received_file_10 fcntl 127.0.0.1
for i in {1..10}
do
  diff -a fcntl_received_file_$i ../../input/sample_input_1/target_file_$i > /dev/null 2>&1
  if [ $? -eq 0 ]
  then
    echo "target_file_${i} and fcntl_received_file_${i} are similar."
  fi
done

echo "Demo fcntl sample_input_2"
cd ../sample_output_2
sudo ../../user_program/slave 1 fcntl_received_file fcntl 127.0.0.1
diff -a fcntl_received_file ../../input/sample_input_2/target_file > /dev/null 2>&1
if [ $? -eq 0 ]
then
  echo "target_file and fcntl_received_file are similar."
fi

echo "Demo fcntl my_input"
cd ../my_output
sudo ../../user_program/slave 5 out_1 out_2 out_3 out_4 out_5 fcntl 127.0.0.1
for i in {1..5}
do
  diff -a out_$i ../../input/my_input/in_$i > /dev/null 2>&1
  if [ $? -eq 0 ]
  then
    echo "in_${i} and out_${i} are similar."
  fi
done
