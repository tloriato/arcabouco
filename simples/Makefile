SRC := arvore.c \
	testarv.c

APP := testarv
LIB := ../arcabouc/Produto/ArcaboucoTeste.a
HEADERS := ../arcabouc/Fontes
OBJ_PATH := Build

CFLAGS := -g -Wall -I"$(HEADERS)" -std=c99 -Wno-comment
LDFLAGS := -g -Wall

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
