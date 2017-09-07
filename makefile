DAOBJS = integer.o da.o test-da.o
CDAOBJS = integer.o cda.o test-cda.o
STACKOBJS = integer.o da.o stack.o test-stack.o
QUEUEOBJS = integer.o cda.o queue.o test-queue.o
OOPTS = -Wall -std=c99 -c -g
LOOPTS = -Wall -std=c99 -g

all : test-da test-cda test-stack test-queue

test-da : $(DAOBJS)
	gcc $(LOOPTS) -o test-da $(DAOBJS)

test-cda : $(CDAOBJS)
	gcc $(LOOPTS) -o test-cda $(CDAOBJS)

test-stack : $(STACKOBJS)
	gcc $(LOOPTS) -o test-stack $(STACKOBJS)

test-queue : $(QUEUEOBJS)
	gcc $(LOOPTS) -o test-queue $(QUEUEOBJS)

da.o : da.c da.h
	gcc $(OOPTS) da.c

cda.o : cda.c cda.h
	gcc $(OOPTS) cda.c

stack.o : stack.c stack.h da.h
	gcc $(OOPTS) stack.c

queue.o : queue.c queue.h cda.h
	gcc $(OOPTS) queue.c

integer.o : integer.c integer.h
	gcc $(OOPTS) integer.c

test-da.o : test-da.c integer.h da.h
	gcc $(OOPTS) test-da.c

test-cda.o : test-cda.c integer.h cda.h
	gcc $(OOPTS) test-cda.c

test-stack.o : test-stack.c integer.h da.h stack.h
	gcc $(OOPTS) test-stack.c

test-queue.o : test-queue.c integer.h cda.h queue.h
	gcc $(OOPTS) test-queue.c

test :
	#testing da#
	test-da
	@echo
	@echo
	#testing cda#
	test-cda
	@echo
	@echo
	#testing stack#
	test-stack
	@echo
	@echo
	#testing queue#
	test-queue
	@echo

clean   :
	rm -f *.o test-da test-cda test-stack test-queue