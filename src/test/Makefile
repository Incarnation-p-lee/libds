include ./src/Makefile.int

INCDIR  =./src/inc
SRC     =src/test/test.c
OBJ     =$(patsubst %.c, %.o, $(SRC))
INC     +=-I$(INCDIR)

$(OBJ):%.o:%.c
	$(CC) $(CFLAG) $(INC) -o $@ $<

