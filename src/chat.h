#define ADDRESS "13.209.61.52"

void on_connect(struct mosquitto *mosq, 
		void *userdata, 
		int rc
		);

void on_message(struct mosquitto *mosq, 
		void *userdata, 
		const struct mosquitto_message *message
		);

void *subscribe_thread(void *arg);

void *publish_thread(void *arg);

void chat(char *channel, char *username);
