
APP = wc
OBJS = main.o

all: $(APP)

$(APP): $(OBJS)
	$(CC) $(OBJS) -o $(APP)

clean:
	$(RM) $(APP) $(OBJS)
