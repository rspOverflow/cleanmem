CFLAGS = -O3 -Wall -Wextra -pedantic -D_FORTIFY_SOURCE=2 -ftree-vectorize

all:
	$(CC) $(CFLAGS) -c cleanmem_heap_region.c -o cleanmem_heap_region.o
	$(CC) $(CFLAGS) -c cleanmem_heap_management.c -o cleanmem_heap_management.o
	ar rcs libcleanmem.a cleanmem_heap_management.o cleanmem_heap_region.o
	
	$(CC) $(CFLAGS) -fPIC -c cleanmem_heap_region.c -o cleanmem_heap_region.o
	$(CC) $(CFLAGS) -fPIC -c cleanmem_heap_management.c -o cleanmem_heap_management.o
	$(CC) $(CFLAGS) -shared cleanmem_heap_region.o cleanmem_heap_management.o -o libcleanmem.so

	mkdir -p build
	cp libcleanmem.a build
	cp libcleanmem.so build

	make clean

clean:
	rm -rfv *.o
	rm -rfv *.so
	rm -rfv *.a

distclean: clean
	rm -rfv build