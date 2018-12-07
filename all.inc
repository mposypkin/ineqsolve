#General make file settings
CC = cc
CPP = c++
LIBTOOL = ar -r


#Pthread linking support options
PTHREADLD=-lpthread

#OpenMP specific compiler options
OPENMPOPT=-fopenmp

#OpenMP specific linker options
OPENMPLD=-fopenmp

#optimization options
# OPTIMOPT=-g
OPTIMOPT=-O


#Static linking option (if needed)
#STATIC=-static

#C++ 14 support on
STD_OPT = -std=c++14 -U__STRICT_ANSI__



#common options
COMOPTS = $(STD_OPT)\
	   -I$(ROOT)

#C++ options
CPPOPTS= $(COMOPTS) $(PCPPOPTS) $(OPTIMOPT) $(OPENMPOPT)

#Linker options for static linking
LDFLAGS = -lm $(OPENMPLD) $(PTHREADLD) $(STATIC)


MFLAGS = MPICC=$(MPICC) COPTS="$(COPTS)" CPPOPTS="$(CPPOPTS) LIBTOOL="$(LIBTOOL)"


all: $(BINS) $(LIBS)

tests:
	@for i in $(TESTS); do if ./$$i > /dev/null; then echo TEST PASSED; continue; else echo TEST FAILED; fi done

# Uncomment this if you want testing finishes after first finished test
#	@for i in $(TESTS); do if ./$$i > /dev/null; then echo TEST PASSED; continue; else echo TEST FAILED; return 1; fi done
	

$(BINS): $(LIBS) $(EXTLIBS)

$(LIBS): $(OBJS)
	$(LIBTOOL) $@ $(OBJS)

indent: 
	indent *.cpp ; indent *.hpp
clean: 
	rm -f *.exe *.o *.a *~ *.log deps.inc

dep:
	$(CC) $(COPTS) -MM -c *.c > deps.inc;\
	$(CPP) $(CPPOPTS) -MM -c *.cpp >> deps.inc;\
        true

.o.exe:
	$(CPP) $(OPTS) -o $@ $< $(LIBS) $(EXTLIBS) $(LDFLAGS)

.cpp.o:
	$(CPP) $(CPPOPTS) -c $<

.c.o:
	$(CC) $(COPTS) -c $<

.SUFFIXES:
.SUFFIXES: .o .a .cpp .c .exe
