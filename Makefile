XINCLUDEDIR = /usr/X11R6/include
INCLUDEDIR = .
XLIBDIR = /usr/X11R6/lib

VERSION = Wonx-a05
PKGNAME = wonx-a05

OBJS = WWCharacter.o WWColorMap.o WWDisplay.o WWLCDPanel.o WWPalette.o WWScreen.o WWSprite.o WonxDisplay.o XDisplay.o bank.o comm.o disp.o text.o key.o sound.o system.o timer.o etc.o wonx.o

.SUFFIXES: .c .o

all :		libwonx.a

libwonx.a :	$(OBJS)
		ar ruc libwonx.a $(OBJS)
#		ranlib libwonx.a

.c.o :		$*.c
		gcc -c $*.c -O -I$(INCLUDEDIR) -I$(XINCLUDEDIR)

clean :
		rm -f libwonx.a *.o

package :
		mkdir -p $(PKGNAME)
		rm -fR $(PKGNAME)/*
		cp COPYING COPYRIGHT HISTORY README OMAKE.jpn Makefile \
			*.h *.c $(PKGNAME)
		tar cvzf $(PKGNAME).tar.gz $(PKGNAME)

# End of Makefile.
