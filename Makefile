LDLIBS += -lmosquitto

CC = gcc

winCC = x86_64-w64-mingw32-gcc

all: 999chat 999chat.exe

999chat: 999chat.c
	$(CC) -o 999chat 999chat.c $(LDLIBS)

999chat.exe: 999chat.c
	$(winCC) -o 999chat.exe 999chat.c $(LDLIBS) -L /usr/lib/x86_64-linux-gnu/

clean:
	rm -f 999chat 999chat.exe *.o
