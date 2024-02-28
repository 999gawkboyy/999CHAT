#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <mosquitto.h>
#include "chat.h"

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

void *subscribe_thread(void *arg) {
    mosquitto_loop_start(mosq);
    return NULL;
}

void *publish_thread(void *arg) {
    char input[100];
    while (1) {
        printf("Enter message: ");
        fgets(input, sizeof(input), stdin);
        if (strlen(input) > 0 && input[strlen(input) - 1] == '\n') {
            input[strlen(input) - 1] = '\0';
        }

        if (strcmp(input, "exit") == 0) {
            break;
        }
        char *channel = (char *)arg;
        mosquitto_publish(mosq, NULL, channel, strlen(input), input, 0, false);
    }

    return NULL;
}

void chat(char *channel) {
    mosquitto_lib_init();

    mosq = mosquitto_new(NULL, true, NULL);
    if (!mosq) {
        fprintf(stderr, "Error: Unable to initialize Mosquitto\n");
        return 1;
    }

    mosquitto_connect_callback_set(mosq, on_connect);
    mosquitto_message_callback_set(mosq, on_message);

    if (mosquitto_connect(mosq, ADDRESS, 1883, 60) != MOSQ_ERR_SUCCESS) {
        fprintf(stderr, "Error: Unable to connect to the broker\n");
        mosquitto_destroy(mosq);
        return 1;
    }
    mosquitto_subscribe(mosq, NULL, channel, 0);
    pthread_t subscribe_tid, publish_tid;

    pthread_create(&subscribe_tid, NULL, subscribe_thread, NULL);
    pthread_create(&publish_tid, NULL, publish_thread, (void *)channel);

    pthread_join(subscribe_tid, NULL);
    pthread_join(publish_tid, NULL);

    mosquitto_disconnect(mosq);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
}