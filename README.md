This is the source code of operating system project2.
```
./master_device : the device moudule for master server
./slave_device  : the device moudule for slave client
./ksocket: the device moudule including the funtions used for kernel socket
./user_program : the user program "master" and "slave"
```

To use it, please:
<ol>
  <li>Change to super user</li>
  <li>Execute "./compile.sh" to compile codes and install modules</li>
  <li>Follow the input instrutions in the spec, i.e.</li>
</ol>

```
./master file_num input_filename method
./slave file_num output_filename method ip
```

<b>Note</b> <br>
We changed the input parameters such that it is simpler and easier for multiple files I/O. <br>
The rule is that the filenames (both input and output) must be <b>exactly the same</b>. <br>
They can be differentiate by the index "_i" appended (which starts from 1).<br>
i.e. If you wish to use "target_file", the filenames must be target_file_1, target_file_2, ... <br>
Then the input parameter is <b>./master 2 target_file mmap</b> <br>
<i>Even if there is only one input file, the file must be saved as target_file_1</i>

Make sure that you are under the path "./user_program" when you execute user programs. <br>
Though the execution order of user program "master" and "slave" does not matter, <br>
it is suggested to execute "master" first to get more precise transmission time.

To run demo, go to "demo" folder and execute `sudo ./{method}_{master/slave}_{i}`
