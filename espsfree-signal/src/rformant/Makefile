#  This material contains proprietary software of Entropic Research Lab, Inc.   
#  Any reproduction, distribution, or publication without the the prior	   
#  written permission of Entropic Speech, Inc. is strictly prohibited.
#  Any public distribution of copies of this work authorized in writing by
#  Entropic Speech, Inc. must bear the notice			
# 								
#      "Copyright (c) 1987 Entropic Research Lab, Inc.; All rights reserved"
# 				
#  makefile for rformant %W% %G% ERL

CFLAGS = -O -I. -I../../h -I/usr/include/atlas $(PROGCFLAGS)
#CFLAGS = -g -I. -I../../h $(PROGCFLAGS)

SUNLIB =  -lm
DOCDIR = $(SPSDIR)/share/doc/espsfree

FORMANT_OBJS = dpform.o rformant.o lpc_poles.o rlpc.o \
	dpfund.o cross.o downsample.o pole_methods.o xversion.o
PROGS =  rformant 
PROGS_I = $(BINDIR)/rformant
OTHER_STUFF = addnoise downsamp gate formsy debias

rformant: $(FORMANT_OBJS) $(NSPSLIB) \
		$(LIBDIR)/$(NHDRLIB)
	cc -o rformant ${CFLAGS} \
	$(FORMANT_OBJS) $(LIBDIR)/libdsigproc.a \
	$(LIBDIR)/xlibsig.a  $(SUNLIB) $(LIBDIR)/$(NHDRLIB) $(NSPSLIB) $(SUNLIB)

pure: $(FORMANT_OBJS) $(NSPSLIB) \
		$(LIBDIR)/$(NHDRLIB)
	purify cc -o rformant ${CFLAGS} \
	$(FORMANT_OBJS) $(LIBDIR)/libdsigproc.a \
	$(LIBDIR)/xlibsig.a  $(SUNLIB) $(LIBDIR)/$(NHDRLIB) $(NSPSLIB) $(SUNLIB)

# RLS: 
#pole_methods.o: $(WAVES)/pole_methods.c
#	-rm -f pole_methods.c
#	-cp $(WAVES)/pole_methods.c .
#	cc -c $(CFLAGS) pole_methods.c
pole_methods.o: pole_methods.c
	cc -c $(CFLAGS) pole_methods.c

install: $(PROGS_I) doc

other_stuff: $(OTHER_STUFF)

$(BINDIR)/rformant: rformant
	-strip $?
	-rm -f $(BINDIR)/$?
	cp $? $(BINDIR)/$?
	chmod $(PROGMOD) $(BINDIR)/$?
	-rm -f $(MANDIR)/man1/rformant.1
	cp rformant.1 $(MANDIR)/man1
	chmod $(MANMOD) $(MANDIR)/man1/rformant.1

doc:	$(DOCDIR)/rformant.help

$(DOCDIR)/rformant.help:	rformant.help
	-rm -f $(DOCDIR)/rformant.help
	cp rformant.help $(DOCDIR)
	chmod $(MANMOD) $(DOCDIR)/rformant.help

addnoise:  addnoise.o  $(LIBDIR)/xlibsig.a
	cc -o addnoise ${CFLAGS} addnoise.o $(LIBDIR)/xlibsig.a -lm

downsamp:  downsamp.o  downsample.o
	cc -o downsamp ${CFLAGS} downsamp.o downsample.o $(LIBDIR)/xlibsig.a \
	-lm

fft: fft.o
	cc -o fft ${CFLAGS} fft.o -lm

sine: sine.o
	cc -o sine ${CFLAGS} sine.o -lm

gate: gate.o
	cc -o gate ${CFLAGS} gate.o $(LIBDIR)/xlibsig.a -lm

debias:  debias.o
	cc -o debias ${CFLAGS} debias.o $(LIBDIR)/xlibsig.a -lm

formsy: formsy.o
	cc -o formsy ${CFLAGS} formsy.o $(LIBDIR)/xlibsig.a -lm

rformant.o: rformant.c
	cc -c $(CFLAGS) -DHELPFILE=\"$(DOCDIR)\" rformant.c

clean:
	rm -f *.o   $(PROGS) $(OTHER_STUFF)
