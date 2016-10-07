
APP = wc
OBJS = main.o options.o

WARNINGS = -Wall -Wextra -Werror -Wpedantic
CFLAGS ?= -std=c99 -ansi $(WARNINGS)

all: $(APP)

$(APP): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(APP)

clean:
	$(RM) $(APP) $(OBJS)
