include ../base.Makefile

INCDIR  =../inc
SRC     =linked_list.c
OBJ     =$(patsubst %.c, %.o, $(SRC))
INC     +=-I$(INCDIR)

$(OBJ):%.o:%.c
	$(CC) $(CFLAG) $(INC) -o $@ $<
