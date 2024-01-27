
CC ?= gcc

APP_NAME = leds
OBJS = leds.o

all: $(APP_NAME)

$(APP_NAME): $(OBJS)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -c $^ -o $@

clean:
	rm *.o $(APP_NAME)