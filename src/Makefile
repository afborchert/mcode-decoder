#
#	Makefile for	mcd
#
OBJS=	mcd_error.o mcd_in.o mcd_load.o mcd_loadcode.o mcd_loaddata.o mcd_main.o mcd_mnem.o
BINDIR=	/usr/soft/borchert/bin

all:	mcd

mcd:	${OBJS}
	${CC} -o mcd ${OBJS}

cp:	mcd
	cp mcd ${BINDIR}/mcd
	rm mcd

cmp:	mcd
	cmp mcd ${BINDIR}/mcd
	rm mcd

clean:
	rm -f ${OBJS}
