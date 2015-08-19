SRC := arvore.c \
	testarv.c

#APP := testarv
APP := testarv.exe
#LIB := ../arcabouc/Produto/ArcaboucoTeste.a
LIB := ../arcabouc/Produto/ArcaboucoTeste.lib
HEADERS := ../arcabouc/Fontes
#OBJ_PATH := Build
OBJ_PATH := Build-win

CFLAGS := -g -Wall -I"$(HEADERS)" -std=c99 -Wno-comment
LDFLAGS := -g -Wall

CC := /home/developer/toolchains/mingw-win32/bin/i686-w64-mingw32-gcc
AR := /home/developer/toolchains/mingw-win32/bin/i686-w64-mingw32-ar
CFLAGS += -fexec-charset="ISO-8859-1" -finput-charset="UTF-8"
######################################

OBJ := $(SRC:.c=.o)
OBJ_P := $(addprefix $(OBJ_PATH)/,$(OBJ))

AUTODEPS := $(patsubst %.c,$(OBJ_PATH)/%.d,$(SRC))
DF = $(OBJ_PATH)/$(*F)

all: $(OBJ_P)
	$(CC) $(LDLAGS) $(OBJ_P) $(LIB) -o $(APP)

clean:
	rm $(OBJ_P) $(APP) $(AUTODEPS)

$(OBJ_PATH)/%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_PATH)/%.d: %.c
#	$(CC) $(CFLAGS) -MM -MP -MT $(DF).o -MT $(DF).d $< > $(DF).d
	$(CC) $(CFLAGS) -MM -MP -MT $(DF).o $< > $(DF).d

-include $(AUTODEPS)
.PHONY: clean
