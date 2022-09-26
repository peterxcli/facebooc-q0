CC = gcc
CFLAGS = -O1 -g -Wall -Werror -I.

#GIT_HOOKS := .git/hooks/applied
#all: $(GIT_HOOKS) test

all: test

# Enable sanitizer(s) or not
ifeq ("$(SANITIZER)","1")
    # https://github.com/google/sanitizers/wiki/AddressSanitizerFlags
    CFLAGS += -fsanitize=address -fno-omit-frame-pointer -fno-common
    LDFLAGS += -fsanitize=address
endif

$(GIT_HOOKS):
	@scripts/install-git-hooks
	@echo

OBJS := test.o queue.o 

deps := $(OBJS:%.o=.%.o.d)

test: $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c -MMD -MF .$@.d $<

valgrind_existence:
	@which valgrind 2>&1 > /dev/null || (echo "FATAL: valgrind not found"; exit 1)

valgrind: valgrind_existence
	# Explicitly disable sanitizer(s)
	$(MAKE) clean SANITIZER=0 test
	valgrind --leak-check=full ./test
	@echo

clean:
	rm -f $(OBJS) $(deps) *~ test /tmp/test.*
	rm -f quetest quetest.o
	rm -rf *.dSYM
	(cd traces; rm -f *~)

quetest:
	make clean
	gcc -O1 -g -I. -c -MMD -MF .test.o.d quetest.c
	gcc -O1 -g -I. -c -MMD -MF .queue.o.d queue.c
	gcc quetest.o queue.o -o quetest
	valgrind --leak-check=full ./quetest
	@echo
	make clean

-include $(deps)

