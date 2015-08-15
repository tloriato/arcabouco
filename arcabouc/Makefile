SRC := PRINCIP.C  \
       GENERICO.C \
       TABSIMB.C  \
       LERPARM.C  \
       CESPDIN.C  \
       CONTA.C    \
       GERAALT.C  \
       INTRPCED.C \
       INTRPCNT.C

APP := ArcaboucoTeste.a

SRC_PATH := Fontes
OBJ_PATH := Objetos
APP_PATH := Produto

CFLAGS := -g -I$(SRC_PATH) -Wall -std=c99

###############################################################
OBJ := $(SRC:.C=.o)
SRC_P := $(addprefix $(SRC_PATH)/,$(SRC))
OBJ_P := $(addprefix $(OBJ_PATH)/,$(OBJ))
APP_P := $(APP_PATH)/$(APP)

AUTODEPS := $(patsubst %.C,$(OBJ_PATH)/%.d,$(SRC))
DF = $(OBJ_PATH)/$(*F)

all: $(OBJ_P)
	$(AR) -rcs $(APP_P) $^

clean:
	rm $(APP_P) $(OBJ_P)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.C
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_PATH)/%.d: $(SRC_PATH)/%.C
#	$(CC) $(CFLAGS) -MM -MP -MT $(DF).o -MT $(DF).d $< > $(DF).d
	$(CC) $(CFLAGS) -MM -MP -MT $(DF).o $< > $(DF).d

-include $(AUTODEPS)
