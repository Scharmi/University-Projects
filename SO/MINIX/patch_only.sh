#!/bin/bash

# Define the path to the patch file
patch_file="ms440004.patch"

# Define SSH connection details
username="root"
hostname="localhost"
port="2222"

# Copy the patch file to the Minix virtual machine
scp -P "$port" "$patch_file" "$username@$hostname:/"

# Connect to the Minix virtual machine and apply the patch
ssh -p "$port" "$username@$hostname" << EOF
    cd /
    patch -p1 < ms440004.patch
    reboot
EOF

