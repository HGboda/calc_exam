# Makefile
# -------------------------------------------------------------------
NAME        =    calc
LIBNAME     =    lib$(NAME).so
ARCHIVE     =    lib$(NAME).a

DEBUG       =    -DDEBUG -ggdb
OPT         =    -O2
ERR         =    -Wall
INC_PATH    =    -I.
LIB_PATH    =    

#----------------------------------------------------------------
CC          =    gcc
LD          =    ld
AR          =    ar rc
RANLIB      =    ranlib
RM          =    rm -f

LIBS        =    -lm
CC_FLAGS    =    $(INC_PATH) $(DEBUG) $(OPT) $(ERR) -fPIC
LD_FLAGS    =    $(LIB_PATH) $(LIBS) -shared -soname=$(LIBNAME)
           

SRC         =    calc.c

OBJ         =    calc.o

#---------------------------------------------------------- Targets
all: $(LIBNAME)
.PHONY: all clean check

$(ARCHIVE): $(OBJ)
	$(AR) $(ARCHIVE) $^
	$(RANLIB) $(ARCHIVE)

$(LIBNAME): $(ARCHIVE)
	$(LD) $(LD_FLAGS) --whole-archive $< --no-whole-archive -o $@

.c.o: $(SRC)
	$(CC) $(CC_FLAGS) -o $@ -c $<

clean:
	[ -f $(LIBNAME) ] && $(RM) $(LIBNAME)|| [ 1 ]
	[ -f $(ARCHIVE) ] && $(RM) $(ARCHIVE)|| [ 1 ]
	[ -f $(OBJ) ] && $(RM) $(OBJ) || [ 1 ]
	cd test && make clean

check: $(LIBNAME)
	cd test && make && make check