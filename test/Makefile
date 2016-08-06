

# Unit-test Makefile
#--------------------------------------------------------- Definitions
TGT_NAME    =    calc
TGT_SRC     =    ../calc.c

OPT         =    -O2 -fprofile-arcs -ftest-coverage
ERR         =    -Wall
INC_PATH    =    -I. -I..
LIB_PATH    =    -L..
LD_PATH     =     ..

#---------------------------------------------------------
CC          =    gcc
RM          =    rm -f


CHECK_LIBS  =    -Wl,--whole-archive -lcheck -Wl,--no-whole-archive
LIBS        =    $(CHECK_LIBS) -lcheck_pic -lpthread -lrt -lsubunit -lm


CC_FLAGS    =    $(INC_PATH) $(OPT) $(ERR) -DUNIT_TEST -pthread

LD_FLAGS    =    $(LIB_PATH) 


TEST        =    test_$(TGT_NAME)
TEST_SRC    =    $(TEST).c \
                 $(TGT_SRC)
TEST_FLAGS  =    $(CC_FLAGS) $(LD_FLAGS)

TEST_LIBS   =    $(LIBS) 

TESTS        =   $(TEST)

#---------------------------------------------------------- Targets
all: $(TESTS)
.PHONY: all clean check


clean:
	$(RM) $(TESTS) *.gcno *.gcda


check:
	@for t in $(TESTS); do                          \
		LD_LIBRARY_PATH='$(LD_PATH)' ./$$t;     \
	done

$(TEST): $(TEST_SRC)
	$(CC) $(TEST_FLAGS) -o $@ $^ $(TEST_LIBS)        