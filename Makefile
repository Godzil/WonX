XINCLUDEDIR = /usr/X11R6/include
INCLUDEDIR = .
XLIBDIR = /usr/X11R6/lib

VERSION = WonX-2.2
PKGNAME = wonx-2.2

SMAC = smac-b02
WWTERM = wwterm-b05

OBJS = WWCharacter.o WWColorMap.o WWDisplay.o WWLCDPanel.o WWPalette.o WWScreen.o WWSprite.o WWCursor.o WWText.o WWInterrupt.o WWTimer.o WWSerialPort.o WonX.o WonXDisplay.o WonXSystem.o WonXSerialPort.o XDisplay.o XColorGC.o UNIXTimer.o UNIXSerialPort.o Obj.o bank.o comm.o disp.o text.o key.o sound.o system.o timer.o libwwc.o service.o fcntl.o etc.o wonx.o

PERLS = filters.pl int2sint.pl sout2str.pl sys2wonx.pl
#PERL = /usr/bin/perl

CC ?= gcc
AR ?= ar
RANLIB ?= ranlib
CFLAGS += -O
#CFLAGS += -g
CFLAGS += -Wall

PREFIX ?= /usr/local

.SUFFIXES: .c .o
.SUFFIXES: .perl .pl

all :		libwonx.a $(PERLS)

libwonx.a :	$(OBJS)
		$(AR) ruc libwonx.a $(OBJS)
#		$(RANLIB) libwonx.a

.c.o :		$*.c
		$(CC) -c $*.c $(CFLAGS) -I$(INCLUDEDIR) -I$(XINCLUDEDIR)

clean :
		rm -f libwonx.a sample1 sample2 sample3 *.o *.pl
		rm -fR $(SMAC) $(WWTERM)

sample1 :	libwonx.a sample1.o
		$(CC) sample1.o -o sample1 \
			-L. -L/usr/X11R6/lib -lwonx -lX11 -lXt

sample2 :	libwonx.a sample2.o
		$(CC) sample2.o -o sample2 \
			-L. -L/usr/X11R6/lib -lwonx -lX11 -lXt

sample3 :	libwonx.a sample3.o
		$(CC) sample3.o -o sample3 \
			-L. -L/usr/X11R6/lib -lwonx -lX11 -lXt

smac :		libwonx.a $(SMAC)
		cd $(SMAC) ; $(MAKE)

$(SMAC) :	$(SMAC).zip $(PERLS)
		unzip $(SMAC).zip
		mkdir -p $(SMAC)/wonx
		cp wonx/*.h $(SMAC)/wonx
		cp libwonx.a $(SMAC)
		mv $(SMAC)/makefile $(SMAC)/makefile.orig
		cp makefile_for_smac $(SMAC)/makefile
		cp challsrc.sh $(PERLS) $(SMAC)
		cd $(SMAC) ; ./challsrc.sh *.[ch] makefile

wwterm :	libwonx.a $(WWTERM)
		cd $(WWTERM) ; $(MAKE)

$(WWTERM) :	$(WWTERM).zip $(PERLS)
		unzip $(WWTERM).zip
		mkdir -p $(WWTERM)/wonx
		cp wonx/*.h $(WWTERM)/wonx
		cp libwonx.a $(WWTERM)
		mv $(WWTERM)/makefile $(WWTERM)/makefile.orig
		cp makefile_for_wwterm $(WWTERM)/makefile
		cp challsrc.sh $(PERLS) $(WWTERM)
		cd $(WWTERM) ; ./challsrc.sh *.[ch] makefile

.perl.pl :	$*.perl
		./findperl.sh $(PERL) | cat - $*.perl > $*.pl
		chmod +x $*.pl

install :	libwonx.a $(PERLS)
		mkdir -p $(PREFIX)/include/wonx
		cp wonx/*.h $(PREFIX)/include/wonx
		cp libwonx.a $(PREFIX)/lib
		cp challsrc.sh $(PERLS) $(PREFIX)/bin

uninstall :
		rm -fR $(PREFIX)/include/wonx
		rm -f $(PREFIX)/lib/libwonx.a
		rm -f $(PREFIX)/bin/challsrc.sh
		rm -f $(PREFIX)/bin/filters.pl
		rm -f $(PREFIX)/bin/int2sint.pl
		rm -f $(PREFIX)/bin/sout2str.pl
		rm -f $(PREFIX)/bin/sys2wonx.pl

package :
		mkdir -p $(PKGNAME)
		rm -fR $(PKGNAME)/*
		mkdir -p $(PKGNAME)/wonx
		cp COPYING COPYRIGHT HISTORY README MANUAL OMAKE.jpn Makefile \
			makefile_for_smac makefile_for_wwterm *.sh *.perl \
			*.h *.c $(SMAC).zip $(WWTERM).zip $(PKGNAME)
		cp wonx/*.h $(PKGNAME)/wonx
		tar cvzf $(PKGNAME).tar.gz $(PKGNAME)

# End of Makefile.
