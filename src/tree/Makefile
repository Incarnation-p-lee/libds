include ./src/base.Makefile

INCDIR  =./src/inc
SRC     =src/tree/tree.c
OBJ     =$(patsubst %.c, %.o, $(SRC))
INC     +=-I$(INCDIR)

$(OBJ):%.o:%.c
	$(CC) $(CFLAG) $(INC) -o $@ $<

