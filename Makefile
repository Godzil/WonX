XINCLUDEDIR = /usr/X11R6/include
INCLUDEDIR = .
XLIBDIR = /usr/X11R6/lib

VERSION = Wonx-b03
PKGNAME = wonx-b03

SMAC = smac-b02

OBJS = WWCharacter.o WWColorMap.o WWDisplay.o WWLCDPanel.o WWPalette.o WWScreen.o WWSprite.o WWText.o WWInterrupt.o WWTimer.o Wonx.o WonxDisplay.o WonxText.o WonxSystem.o XDisplay.o UNIXTimer.o bank.o comm.o disp.o text.o key.o sound.o system.o timer.o etc.o

CC = gcc

.SUFFIXES: .c .o

all :		libwonx.a

libwonx.a :	$(OBJS)
		ar ruc libwonx.a $(OBJS)
#		ranlib libwonx.a

.c.o :		$*.c
		$(CC) -c $*.c -O -Wall -I$(INCLUDEDIR) -I$(XINCLUDEDIR)

clean :
		rm -f libwonx.a sample1 sample2 *.o

sample1 :	libwonx.a sample1.o
		$(CC) sample1.o -o sample1 \
			-L. -L/usr/X11R6/lib -lwonx -lX11 -lXt

sample2 :	libwonx.a sample2.o
		$(CC) sample2.o -o sample2 \
			-L. -L/usr/X11R6/lib -lwonx -lX11 -lXt

smac :		libwonx.a
		unzip $(SMAC).zip
		cp -R wonx_include $(SMAC)
		cp libwonx.a $(SMAC)
		mv $(SMAC)/makefile $(SMAC)/makefile.orig
		cp makefile_for_smac $(SMAC)/makefile
		cp sys2wonx.pl $(SMAC)
		echo "ここで止まったときは，sys2wonx.pl の１行目に適切なperlを指定してください"
		cd $(SMAC) ; ./sys2wonx.pl *.[ch]
		cd $(SMAC) ; $(MAKE)

package :
		mkdir -p $(PKGNAME)
		rm -fR $(PKGNAME)/*
		mkdir -p $(PKGNAME)/wonx_include
		cp COPYING COPYRIGHT HISTORY README OMAKE.jpn Makefile \
			makefile_for_smac sys2wonx.pl \
			*.h *.c smac*.zip $(PKGNAME)
		cp wonx_include/*.h $(PKGNAME)/wonx_include
		tar cvzf $(PKGNAME).tar.gz $(PKGNAME)

# End of Makefile.
