#
##Makefile for the FREAX-kernel
#
# Note! Dependencise are done automagically by 'make dep',which alsp
# removes any old dependencies . DON'T put your own dependencise here
# unless it's something sepecial (ie not a.c file )
#

AR    = har  
AS    = gas
LD    = gld
LDFLAGS = -s -x
CC      = gcc
CFLAGS  = -Wall -O -fstrength-reduce -fomit-frame-pointer -fcombine-regs \
	  -finline-functions -mstring-insns -nostdinc -I../include
CPP     = gcc -E -nostdinc -I../include

.c.s:
	$(CC) $(CFLAGS)  \
		-S -o $*.o $<
.s.o:   
	$(AS) -c -o $.*.o $<
.c.o:
	$(CC) $(CFLAGS) \
		-c -o $*.o $<

OBJS = sched.o system_call.o traps.o asm.o fork.o \
       panic.o printk.o vsprintf.o sys.o exit.o \
       signal.o mktime.o

kernel.o:$(OBJS)
	$(LD) -r -o kernel.o $(OBJS)
	sync

clean:
	rm -f core *.o *.a tmp_make keyboard.s
	for i in *.c; do rm -f `basename $$i.c`.s; done
	(cd chr_drv; make clean)
	(cd blk_drv; make clean)
	(cd math;make clean)

dep:
	sed '/\#\#\# Dependencies/q' < Makefile > tmp_make
	(for i in *.c; do echo -n `echo $$i | sed 's,\.c,\.s,'`" "; \
		$(CPP) -M $$i; done) >> tmp_make
	cp tmp_make Makefile
	(cd chr_drv; make dep)
	(cd blk_drv;make dep)

### Dependencies:
exit.s exit.o:exit.c ../include/errno.h ../include/signal.h \
../include/sys/types.h ../include/sys/wait.h ../include/linux/scged.h \
../include/linux/head.h ../include/linux/fs.h ../include/linux/mm,h
../include/linux/kernel.h ../include/linux/tty.h ../include/termios.h \
../include/asm/segment.h
fork.s fork.o: fork.c ../include/errno.h ../include/linux/sched.h \
../include/linux/head.h ../include/linux/fs.h ../include/sys/types.h \
../include/linux/mm.h ../include/signal.h ../include/linux/kernel.h \
../include/asm/segment.h ../include/asm/system.h
mktime.s mktime.o: mktime.c ../include/time.h
panic.s panic.o: panic.c ../include/linux/kernel.h ../include/linux/sched.h  \
../include/linux/head.h ../include/linux/fs.h ../include/sys/types.h \
../include/linux/mm.h ../include/signal.h
printk.s printk.o: printk.c ../include/stdarg.h ../include/stddef.h \
	../include/linux/kernel.h
sched.s sched.o: sched.c ../include/linux/seched.h ../include/linux/head.h \
../include/linux/fs.h ../include/sys/types.h ../include/linux/mm.h \
../include/signal.h ../include/linux/kernel.h ../include/linux/sys.h \
../include/linux.fdreg.h ../include/asm/sysytem.h ../include/asm/io.h \
../include/asm/segment.h
signal.s signal.o:signal.c ../include/linux/sched.h ../include/linux/head.h \
../include/linux/fs.h ../include/sys/types.h ../include/linux/mm.h \
../include/signal.h ../include/linux/kernel.h ../include/asm/segment.h 
sys.s sys.o: sys.c ../include/errno.h ../include/linux/sched.h \
../include/linux/head.h ../include/linux/fs.h ../include/sys/types.h \
../include/linux/mm.h ../include/signal.h ../include/linux/tty.h \
../include/termios.h ../include/linux/kernel.h ../include/asm/segment.h \
../include/sys/times.h ../include/sys/utsname.h
traps.s traps.o: traps.c ../include/string.h ../include/linux/head.h \
../include/linux/sched.h ../include/linux/fs.h ../include/sys/types.h \
../include/linux/mm.h ../include/signal.h ../include/linux/kernel.h \
../include/asm/system.h ../include/asm/segment.h ../include/asm/io.h
vsprintf.s vsprintf.o: vsprintf.c ../include/stdarg.h ../include/string.h

