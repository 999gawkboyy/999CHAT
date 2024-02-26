LDLIBS += -lmosquitto

CC = gcc

all: 999chat.sh

999chat.sh: 999chat.c
	$(CC) -o 999chat.sh 999chat.c $(LDLIBS)

clean:
	rm -f 999chat.sh *.o
