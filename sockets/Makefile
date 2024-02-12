CC ?= gcc

APP_NAME = hello_client
OBJFILES = hello_client.o


LIB_DIRS = .

all: $(APP_NAME) 

$(APP_NAME): $(OBJFILES)
	$(CC) $^ -o $@ -L$(LIB_DIRS)

%.o: %.c
	$(CC) -c $^ -o $@

clean:
	rm *.o  $(APP_NAME)  

fresh:
	make clean
	make all 