CC ?= gcc
CXX ?= g++
CPP ?= g++

APP_NAME = hello_server
OBJFILES = hello_server.o


APP_NAME_CLIENT = hello_client
OBJFILES_CLIENT = hello_client.o


LIB_DIRS = .

all: $(APP_NAME) $(APP_NAME_CLIENT)

$(APP_NAME): $(OBJFILES)
	$(CC) $^ -o $@ -L$(LIB_DIRS)

%.o: %.c
	$(CC) -c $^ -o $@

clean:
	rm *.o  $(APP_NAME) $(APP_NAME_CLIENT)

fresh:
	make clean
	make all 