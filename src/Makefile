LDLIBS += -lchat -lmosquitto

CC = gcc
CFLAGS = -Wall -Wextra -pedantic

LIB_SOURCES = 999chat.c chat.c
LIB_OBJECTS = $(LIB_SOURCES:.c=.o)
LIBRARY = libchat.a

MAIN_SOURCE = 999chat.c
EXECUTABLE = 999chat

all: $(EXECUTABLE)

$(EXECUTABLE): $(LIBRARY) $(MAIN_SOURCE)
	$(CC) $(CFLAGS) -o $@ $(MAIN_SOURCE) -L. $(LDLIBS)

$(LIBRARY): $(LIB_OBJECTS)
	ar rcs $@ $(LIB_OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(LIB_OBJECTS) $(LIBRARY) $(EXECUTABLE)
