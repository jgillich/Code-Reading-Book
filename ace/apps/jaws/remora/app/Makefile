#### Makefile,v 1.3 1999/06/22 18:44:00 levine Exp

include stdmk

EXE = test

all: $(EXE)

clean:
	-$(RM) core *~ *.o *_c.hh *_c.cc *_s.hh *_s.cc $(EXE)
	-$(RM) -r Templates.DB

remora_c.cc: remora.idl	
	$(ORBCC) remora.idl

remora_s.cc: remora.idl
	$(ORBCC) remora.idl

test: remora_c.o Remora_Import.o Remora_Export.o test.o
	$(CC) -o test test.o remora_c.o Remora_Import.o Remora_Export.o \
		 $(LIBPATH) $(LIBORB) $(STDCC_LIBS) $(LIBACE)
