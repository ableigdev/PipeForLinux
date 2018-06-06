#include <iostream>
#include <cstdio>
#include <cstring>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int fd1;

    const char* myfifo = "/tmp/myfifo";

    mkfifo(myfifo, 0666);
    char str1[80];
    char str2[80];

    while (true)
    {
        fd1 = open(myfifo, O_RDONLY);
        read(fd1, str1, 80);

        std::cout << "User1: " << str1 << std::endl;

        close(fd1);

        fd1 = open(myfifo, O_WRONLY);
        fgets(str2, 80, stdin);
        write(fd1, str2, strlen(str2) + 1);
        close(fd1);
    }
    return 0;
}