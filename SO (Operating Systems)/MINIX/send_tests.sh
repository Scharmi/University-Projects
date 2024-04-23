#!/bin/bash

# Define the path to the patch file
patch_file="ms440004.patch"

# Define SSH connection details
username="root"
hostname="localhost"
port="2222"

# Copy the patch file to the Minix virtual machine
scp -P "$port" "./tests/test.c" "$username@$hostname:/"
scp -P "$port" "./tests/test1.c" "$username@$hostname:/"
scp -P "$port" "./tests/test2.c" "$username@$hostname:/"
scp -P "$port" "./tests/test3.c" "$username@$hostname:/"
scp -P "$port" "./tests/test4.c" "$username@$hostname:/"
scp -P "$port" "./tests/test5.c" "$username@$hostname:/"
scp -P "$port" "./tests/test6.c" "$username@$hostname:/"
scp -P "$port" "./tests/test7.c" "$username@$hostname:/"
scp -P "$port" "./tests/test.sh" "$username@$hostname:/"

