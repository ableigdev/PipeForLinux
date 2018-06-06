#include <iostream>
#include <cstdio>
#include <cstring>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


int main()
{

    int fd;

    const char *myfifo = "/tmp/myfifo";

    mkfifo(myfifo, 0666);

    char arr1[80];
    char arr2[80];

    while (true)
    {
        fd = open (myfifo, O_WRONLY);
        fgets(arr2, 80, stdin);

        write (fd, arr2, strlen(arr2) + 1);
        close(fd);

        fd = open (myfifo, O_RDONLY);
        read(fd, arr1, sizeof(arr1));

        std::cout << "User2: " << arr1 << std::endl;
        close(fd);
    }


    return 0;
}
