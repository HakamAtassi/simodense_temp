CC = $(TOOL_DIR)/bin/riscv32-unknown-elf-gcc -DSTREAM_ARRAY_SIZE=1024 -DNTIMES=20 -g -march=rv32im -std=gnu99 -ffreestanding -Wl,-Bstatic -o firmware.elf   -Wextra -Wshadow -Wundef -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings -Wredundant-decls -g -pedantic  -ffreestanding -fpermissive -DSTREAM_TYPE=uint32_t
#gcc-4.9
CFLAGS = -O2 #-fopenmp

FC = gfortran-4.9
FFLAGS = -O2 -fopenmp

all: stream_c.exe 
#stream_f.exe

stream_f.exe: stream.f mysecond.o
	$(CC) $(CFLAGS) -c mysecond.c
	$(FC) $(FFLAGS) -c stream.f
	$(FC) $(FFLAGS) stream.o mysecond.o -o stream_f.exe

stream_c.exe: stream.c
	$(CC) $(CFLAGS) syscalls.c stream.c -o stream_c.exe 

clean:
	rm -f stream_f.exe stream_c.exe *.o

# an example of a more complex build line for the Intel icc compiler
stream.icc: stream.c
	icc -O3 -xCORE-AVX2 -ffreestanding -qopenmp -DSTREAM_ARRAY_SIZE=80000000 -DNTIMES=20 stream.c -o stream.omp.AVX2.80M.20x.icc
