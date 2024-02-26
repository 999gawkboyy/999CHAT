#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32 || _WIN64
	#define OS "windows"
#endif

#ifdef __linux__ || linux || __linux
	#define OS "linux"
#endif

typedef struct {
	char username[30];
	char password[30];
} User;

void init() {
	system("clear");
	if (strcmp(OS, "windows") == 0)
		system("python main.py");
	else
		system("python3 main.py");
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
