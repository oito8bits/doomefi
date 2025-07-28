IMG = doomefi.img
PROG = BOOTX64.EFI
CC = x86_64-w64-mingw32-gcc
OBJS = efi_main.o console.o file.o str.o env.o video.o gettime.o kb.o mem.o ascii.o str.o

$(IMG): $(PROG)
	dd if=/dev/zero of=$@ bs=1024 count=46875

	sudo mkfs.fat -v -F32 $@

	mkdir dir/
	sudo mount $@ dir
	sudo mkdir dir/efi/boot -p
	sudo cp BOOTX64.EFI dir/efi/boot/
	sudo mkdir dir/doom1.wad
	sudo cp PureDOOM/doom1.wad dir/doom1.wad
	sudo umount $@
	rmdir dir

$(PROG): $(OBJS)
	$(CC) -nostdlib -Wl,-dll -shared -Wl,--subsystem,10 -e efi_main -o $(PROG) $^ -Iinclude/

%.o: %.c
	$(CC) -O2 -ffreestanding -I libefi/include/ -I include/ -I include/amd64 -c -o $@ $<

.PHONY: clean run

clean:
	rm -rf *.o $(PROG) $(IMG)

	make clean -C libefi/

run:
	qemu-system-x86_64 -L /usr/share/edk2-ovmf/x64/ -bios OVMF.fd -drive file=$(IMG),format=raw -serial stdio
