rm minix.img
qemu-img create -f qcow2 -F raw -o backing_file=~/SO/minix.img minix.img
qemu-system-x86_64 -curses -drive file=minix.img -rtc base=localtime -net user,hostfwd=tcp::2222-:22 -net nic,model=virtio -m 1024M -enable-kvm -machine kernel_irqchip=off
