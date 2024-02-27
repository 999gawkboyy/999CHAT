LDLIBS += -lmosquitto

CC = gcc

all: 999chat 

999chat: 999chat.c
	$(CC) -o 999chat 999chat.c $(LDLIBS)

exe: 999chat.c
	$(CC) -o 999chat 999chat.c -I"C:\Program Files\Mosquitto\devel" -L"C:\Program Files\Mosquitto\devel" $(LDLIBS)

clean:
	rm -f 999chat *.o
