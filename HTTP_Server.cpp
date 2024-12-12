#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <errno.h>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include "FuncA.h" 

#define PORT 8081

void sendGETresponse(int fd, char strFilePath[], char strResponse[]);
void sendPUTresponse(int fd, char strFilePath[], char strBody[], char strResponse[]);

char HTTP_200HEADER[] = "HTTP/1.1 200 Ok\r\n";
char HTTP_201HEADER[] = "HTTP/1.1 201 CREATED\r\n";
char HTTP_404HEADER[] = "HTTP/1.1 404 Not Found\r\n";
char HTTP_400HEADER[] = "HTTP/1.1 400 Bad request\r\n";

int CreateHTTPserver() {
    int connectionSocket, clientSocket, pid;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((connectionSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket open failed\n");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    memset(address.sin_zero, '\0', sizeof address.sin_zero);

    if (bind(connectionSocket, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("socket bind failed\n");
        close(connectionSocket);
        exit(EXIT_FAILURE);
    }

    if (listen(connectionSocket, 10) < 0) { // queue up to 10 connections ready for accept
        perror("socket listen failed\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("\n+++++++ Waiting for a new connection ++++++++\n\n");

        if ((clientSocket = accept(connectionSocket, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Error accept()");
            exit(EXIT_FAILURE);
        }

        pid = fork();

        if (pid < 0) {
            perror("Error on fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) { // Child process
            char buffer[30000] = {0};
            char* ptrBuffer = &buffer[0];

            int iBytesRead = read(clientSocket, ptrBuffer, 30000);
            printf("\nClient message of %d bytes:\n%s\n", iBytesRead, buffer);

            if (iBytesRead == 0) {
                printf("Client closed connection prematurely\n");
                close(clientSocket);
                continue;
            }

            printf("\nParsing request...\n");

            char strHTTP_requestMethod[10] = {0};
            char* pch = strchr(ptrBuffer, ' ');
            strncpy(strHTTP_requestMethod, ptrBuffer, pch - ptrBuffer);
            printf("Client method: %s\n", strHTTP_requestMethod);

            ptrBuffer = pch + 1;
            char strHTTP_requestPath[200] = {0};
            pch = strchr(ptrBuffer, ' ');
            strncpy(strHTTP_requestPath, ptrBuffer, pch - ptrBuffer);
            printf("Client asked for path: %s\n", strHTTP_requestPath);

            char strHTTPreqExt[200] = {0};
            pch = strrchr(strHTTP_requestPath, '.');
            if (pch != NULL) strcpy(strHTTPreqExt, pch + 1);

            char strFilePath[500] = {0};
            char strResponse[500] = {0};
            char strTimeEllapsed[20] = {0};  // Declare strTimeEllapsed outside the /compute block

            if (!strcmp(strHTTP_requestMethod, "GET")) {
                if (!strcmp(strHTTP_requestPath, "/compute")) {
                    printf("Processing /compute...\n");

                    auto t1 = std::chrono::high_resolution_clock::now();

                    std::vector<double> aValues;
                    FuncA func;

                    const int n = 5; // Number of terms in the series
                    const double xStart = 0.0; // Starting value for calculations
                    const int arraySize = 2000000; // Number of elements in the array

                    for (int i = 0; i < arraySize; i++) {
                        double x = xStart + i * 0.0001; // Increment x slightly for each value
                        aValues.push_back(func.calculateTrigFunction(n, x));
                    }

                    for (int i = 0; i < 500; i++) {
                        sort(aValues.begin(), aValues.end());
                        reverse(aValues.begin(), aValues.end());
                    }

                    auto t2 = std::chrono::high_resolution_clock::now();
                    auto int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

                    int iMS = int_ms.count();
                    sprintf(strTimeEllapsed, "%d", iMS);

                    sprintf(strResponse, "%sContent-Type: text/plain\r\nContent-Length: %ld\r\n\r\n%s", 
                            HTTP_200HEADER, strlen(strTimeEllapsed), strTimeEllapsed);

                    if (write(clientSocket, strResponse, strlen(strResponse)) < 0) {
                        perror("Error writing response");
                    } else {
                        printf("Response sent successfully\n");
                    }
                } else {
                    sprintf(strResponse, "%sContent-Type: text/plain\r\nContent-Length: 13\r\n\r\n404 Not Found", HTTP_404HEADER);
                    write(clientSocket, strResponse, strlen(strResponse));
                }
            }

            close(clientSocket);
            return 0;
        } else {
            close(clientSocket);
        }
    }

    close(connectionSocket);
    return 0;
}

