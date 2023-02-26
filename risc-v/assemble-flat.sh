riscv64-unknown-elf-as $1.s -o $1.out
riscv64-unknown-elf-objcopy -O binary $1.out $1.obj
rm $1.out