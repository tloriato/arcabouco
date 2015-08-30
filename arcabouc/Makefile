SRC := princip.c  \
       generico.c \
       tabsimb.c  \
       lerparm.c  \
       cespdin.c  \
       conta.c    \
       geraalt.c  \
       intrpced.c \
       intrpcnt.c

APP := ArcaboucoTeste.a
APP_WIN := ArcaboucoTeste.lib

SRC_PATH := Fontes
OBJ_PATH := Objetos
APP_PATH := Produto
OBJ_PATH_WIN := Objetos-win
APP_PATH_WIN := Produto

CFLAGS := -x c -g -I$(SRC_PATH) -Wall -std=c99 -Wno-comment

CC_WIN := i686-w64-mingw32-gcc
AR_WIN := i686-w64-mingw32-ar
CFLAGS_WIN := $(CFLAGS) -fexec-charset="ISO-8859-1" -finput-charset="UTF-8"

###############################################################
OBJ := $(SRC:.c=.o)
SRC_P := $(addprefix $(SRC_PATH)/,$(SRC))
OBJ_P := $(addprefix $(OBJ_PATH)/,$(OBJ))
APP_P := $(APP_PATH)/$(APP)

OBJ_WIN := $(SRC:.c=.obj)
OBJ_P_WIN := $(addprefix $(OBJ_PATH_WIN)/,$(OBJ_WIN))
APP_P_WIN := $(APP_PATH_WIN)/$(APP_WIN)

AUTODEPS := $(patsubst %.c,$(OBJ_PATH)/%.d,$(SRC))
DF = $(OBJ_PATH)/$(*F)

all: $(OBJ_P)
	$(AR) -rcs $(APP_P) $^

win: $(OBJ_P_WIN)
	$(AR_WIN) -rcs $(APP_P_WIN) $^

clean:
	rm $(APP_P) $(OBJ_P) $(AUTODEPS) $(OBJ_P_WIN) $(APP_WIN)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_PATH_WIN)/%.obj: $(SRC_PATH)/%.c
	$(CC_WIN) -c $(CFLAGS_WIN) $< -o $@

$(OBJ_PATH)/%.d: $(SRC_PATH)/%.c
#	$(CC) $(CFLAGS) -MM -MP -MT $(DF).o -MT $(DF).d $< > $(DF).d
	$(CC) $(CFLAGS) -MM -MP -MT $(DF).o $< > $(DF).d

-include $(AUTODEPS)
.PHONY: clean
