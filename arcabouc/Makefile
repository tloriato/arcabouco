SRC := princip.c  \
       generico.c \
       tabsimb.c  \
       lerparm.c  \
       cespdin.c  \
       conta.c    \
       geraalt.c  \
       intrpced.c \
       intrpcnt.c

#APP := ArcaboucoTeste.a
APP := ArcaboucoTeste.lib

SRC_PATH := Fontes
#OBJ_PATH := Objetos
APP_PATH := Produto
OBJ_PATH := Objetos-win

CFLAGS := -g -I$(SRC_PATH) -Wall -std=c99 -Wno-comment

CC := /home/developer/toolchains/mingw-win32/bin/i686-w64-mingw32-gcc
AR := /home/developer/toolchains/mingw-win32/bin/i686-w64-mingw32-ar
CFLAGS += -fexec-charset="ISO-8859-1" -finput-charset="UTF-8"

###############################################################
OBJ := $(SRC:.c=.o)
SRC_P := $(addprefix $(SRC_PATH)/,$(SRC))
OBJ_P := $(addprefix $(OBJ_PATH)/,$(OBJ))
APP_P := $(APP_PATH)/$(APP)

AUTODEPS := $(patsubst %.c,$(OBJ_PATH)/%.d,$(SRC))
DF = $(OBJ_PATH)/$(*F)

all: $(OBJ_P)
	$(AR) -rcs $(APP_P) $^

clean:
	rm $(APP_P) $(OBJ_P) $(AUTODEPS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_PATH)/%.d: $(SRC_PATH)/%.c
#	$(CC) $(CFLAGS) -MM -MP -MT $(DF).o -MT $(DF).d $< > $(DF).d
	$(CC) $(CFLAGS) -MM -MP -MT $(DF).o $< > $(DF).d

-include $(AUTODEPS)
.PHONY: clean
