OBJS = scanner.o integer.o real.o da.o cda.o comparator.o  queue.o stack.o sqsort.o
OOPTS = -Wall -std=c99 -c -g
LOOPTS = -Wall -std=c99 -g

typescript : $(OBJS)
	gcc $(LOOPTS) $(OBJS) -o typescript

typescript.o : typescript.c integer.h real.h scanner.h comparator.h da.h cda.h stack.h queue.h
	gcc $(OOPTS) sqsort.c

da.o : da.c da.h
	gcc $(OOPTS) da.c

cda.o : cda.c cda.h
	gcc $(OOPTS) cda.c

stack.o : stack.c stack.h da.h
	gcc $(OOPTS) stack.c

queue.o : queue.c queue.h cda.h
	gcc $(OOPTS) queue.c

comparator.o: comparator.c comparator.h integer.h real.h
	gcc $(OOPTS) comparator.c

integer.o : integer.c integer.h
	gcc $(OOPTS) integer.c

real.o : real.c real.h
	gcc $(OOPTS) real.c

scanner.o : scanner.c scanner.h
	gcc $(OOPTS) scanner.c

test :
	#testing integer file read#
	typescript
	@echo
	@echo

clean   :
	rm -f *.o typescript
