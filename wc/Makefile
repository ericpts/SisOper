
APP = wc
OBJS = main.o options.o

WARNINGS = -Wall -Wextra -Werror -Wpedantic
CFLAGS ?= -pedantic -std=c99 -g $(WARNINGS)

all: $(APP)

$(APP): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(APP)

main.o: main.c 

options.o: options.c options.h

clean:
	$(RM) $(APP) $(OBJS)
