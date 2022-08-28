APP := sztype

APP_VER := "0.3"

CC ?= cc

CLIBS:=

CFLAGS += -Wall -std=c99 

CFLAGS_RELEASE:= -O3 -DNDEBUG

CFLAGS_DEBUG:= -O0 -g -DDEBUG -Wextra -Werror -Wimplicit-fallthrough

SOURCE := $(wildcard *.c)

OBJ := $(SOURCE:.c=.o)

default: release

config:
	-@sed -e 's/@APP_NAME@/\"$(APP)\"/g' -e 's/@APP_VER@/$(APP_VER)/g' config.h.in > config.h

release: CFLAGS+=$(CFLAGS_RELEASE)
release: CLIBS+=-Wl,-s
release: config $(APP)

debug: CFLAGS+=$(CFLAGS_DEBUG)
debug: config $(APP)


$(APP): $(OBJ)
	$(CC) $(OBJ) $(CLIBS) -o $(APP)

.o:
	$(CC) -c $<

clean:
	rm  -v *.o $(APP) config.h


