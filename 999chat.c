#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mosquitto.h>

#ifdef _WIN32 || _WIN64
    #define OS "windows"
#endif

#ifdef __linux__ || linux || __linux
    #define OS "linux"
#endif

void init() {
    system("clear");
    if (strcmp(OS, "windows") == 0)
	system("python main.py");
    else
	system("python3 main.py");
}

struct mosquitto *mosq;

void on_connect(struct mosquitto *mosq, void *userdata, int rc) {
    if (rc == 0) {
        printf("Connected to the broker\n");
    } else {
        fprintf(stderr, "Failed to connect to the broker\n");
    }
}

void on_message(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message) {
    printf("Received message on topic %s: %s\n", message->topic, (char *)message->payload);
}


int main(int argc, char const *argv[])
{
    init();

    mosquitto_lib_init();

    mosq = mosquitto_new(NULL, true, NULL);
    if (!mosq) {
        fprintf(stderr, "Error: Unable to initialize Mosquitto\n");
        return 1;
    }

    mosquitto_connect_callback_set(mosq, on_connect);
    mosquitto_message_callback_set(mosq, on_message);

    if (mosquitto_connect(mosq, "52.78.35.165", 1883, 60) != MOSQ_ERR_SUCCESS) {
        fprintf(stderr, "Error: Unable to connect to the broker\n");
        mosquitto_destroy(mosq);
        return 1;
    }

    mosquitto_subscribe(mosq, NULL, "chat", 0);

    char input[100];
    while (1) {
        printf("Enter message: ");
        fgets(input, sizeof(input), stdin);
        if (strlen(input) > 0 && input[strlen(input) - 1] == '\n') {
            input[strlen(input) - 1] = '\0'; // Remove the newline character
        }

        if (strcmp(input, "exit") == 0) {
            break;
        }

        mosquitto_publish(mosq, NULL, "chat", strlen(input), input, 0, false);
    }

    mosquitto_disconnect(mosq);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();	
    return 0;
}
