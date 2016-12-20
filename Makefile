SOURCES.c = main.c execCD.c parse.c  print.c  execPINFO.c execRestCmd.c execECHO.c  
INCLUDES= 
CFLAGS=
SLIBS= 
PROGRAM= main

OBJECTS= $(SOURCES.c:.c=.o)

.KEEP_STATE:

debug := CFLAGS= -g

all debug: $(PROGRAM)

$(PROGRAM): $(INCLUDES) $(OBJECTS)
	$(LINK.c) -o $@ $(OBJECTS) $(SLIBS)

clean:
	rm -f $(PROGRAM) $(OBJECTS)
