a.out: asgn2_client.o asgn2_implementation.o
	gcc asgn2_client.o asgn2_implementation.o -lm
asgn2_client.o: asgn2_client.c asgn2_header.h
	gcc -c asgn2_client.c asgn2_header.h
asgn2_implementation.o: asgn2_implementation.c asgn2_header.h
	gcc -c asgn2_implementation.c asgn2_header.h

