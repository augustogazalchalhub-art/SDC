obj-m := modulo_propio.o

KDIR := /home/augusto-gazal-chlahub/SDC/TP4/raspberry/linux

all:
	make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean
