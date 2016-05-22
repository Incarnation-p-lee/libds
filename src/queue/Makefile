include ./src/Makefile.int

INCDIR  =./src/inc
SRC     =src/queue/queue.c
OBJ     =$(patsubst %.c, %.o, $(SRC))
INC     +=-I$(INCDIR)

$(OBJ):%.o:%.c
	$(CC) $(CFLAG) $(INC) -o $@ $<

