include ./src/base.Makefile

INCDIR  =./src/inc
SRC     =src/linked_list/linked_list.c
OBJ     =$(patsubst %.c, %.o, $(SRC))
INC     +=-I$(INCDIR)

$(OBJ):%.o:%.c
	$(CC) $(CFLAG) $(INC) -o $@ $<

