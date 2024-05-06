#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
 
int main()
{
    struct sockaddr_in client;
    int s, flag;
    char buffer[20], response[2]; // Change response size to hold single character
    s = socket(AF_INET, SOCK_STREAM, 0);
    client.sin_family = AF_INET;
    client.sin_port = htons(2000); // Use htons() to convert port to network byte order
    client.sin_addr.s_addr = inet_addr("127.0.0.1");
    connect(s, (struct sockaddr *)&client, sizeof client);

    do { // Loop until user inputs '0' (no)
        printf("\nEnter a string to check palindrome: ");
        scanf("%s", buffer);
        printf("\nClient: %s", buffer);
        send(s, buffer, sizeof(buffer), 0);
        recv(s, &flag, sizeof(int), 0);
        if (flag == 1) {
            printf("\nServer: the string is a palindrome.\n");
        } else {
            printf("\nServer: the string is not a palindrome.\n");
        }
        printf("Do you want to continue? (1 for yes, 0 for no): ");
        scanf("%s", response);
    } while (response[0] == '1'); // Loop until user inputs '0' (no)

    close(s);
    return 0;
}