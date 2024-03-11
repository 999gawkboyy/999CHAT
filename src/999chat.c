#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chat.h"

void init(char* FileName) {
    system("clear");
    FILE *file = fopen(FileName, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char line[2048];

    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }

    fclose(file);
}

int main(int argc, char const *argv[])
{
    init("txt.txt");

    char channel[10];
    char username[10];

    printf("Channel: ");
    fgets(channel, sizeof(channel), stdin);
    size_t len = strlen(channel);
    if (len > 0 && channel[len - 1] == '\n') {
        channel[len - 1] = '\0';
    }

    printf("Username: ");
    fgets(username, sizeof(username), stdin);
    len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
	username[len - 1] = '\0';
    }
    
    chat(channel, username);

    return 0;
}
