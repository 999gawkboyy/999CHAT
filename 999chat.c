#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char username[30];
	char password[30];
} User;

void init() {
	system("clear");
	system("python main.py");
}

User Login() {
	User user;

	while (1) {
		printf("username: ");
		scanf("%s", user.username);
		printf("password: ");
		scanf("%s", user.password);

		if (strcmp(user.username, "qwe") == 0 && strcmp(user.password, "qwe123") == 0) {
			printf("LOGIN SUCCESS!!\n"); 
			break;
		}
		printf("incorrect username or password... \n\n");
		continue;
	}
	return user;
}

int main(int argc, char const *argv[])
{
	init();
	
	User user = Login();
	printf("username: %s\npassword: %s", user.username, user.password);
	
	return 0;
}
