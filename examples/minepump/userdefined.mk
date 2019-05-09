USER_OBJS += simu.o

simu.o: ../../simu.c ../../simu.h
	$(CC) -c $(INCLUDE) $(CFLAGS) ../../simu.c -o simu.o
