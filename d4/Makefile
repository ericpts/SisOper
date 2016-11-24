APP = d4

OBJS = main.o vector.o

WARNINGS = -Wall -Wextra -Werror -Wpedantic
CFLAGS ?= -pedantic -std=c99 -g $(WARNINGS)


all: $(APP)

$(APP): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(APP)

main.o: main.c

vector.o: vector.c vector.h

clean:
	$(RM) $(APP) $(OBJS)
