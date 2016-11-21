all: run

run: libfoo.a
	gcc main.c -lfoo -L. -lpthread

libfoo.a: device.o rule.o
	ar r libfoo.a device.o rule.o

device.o: device.c
	gcc -c device.c
rule.o: rule.c
	gcc -c rule.c
