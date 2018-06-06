#include <iostream>
#include <cstdio>
#include <cstring>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>

#define STRING_SIZE 80

int main()
{

    int fd;

    const char *myfifo = "/tmp/myfifo";

    mkfifo(myfifo, 0666);

    std::string str;
    str.resize(STRING_SIZE);

    std::string str2;
    str2.resize(STRING_SIZE);

    fd = open (myfifo, O_WRONLY);
    std::cin >> str;

    write (fd, str.data(), str.size() + 1);
    close(fd);

    fd = open (myfifo, O_RDONLY);
    read(fd, &str2.at(0), sizeof(str2));

    std::cout << "User2: " << str2.data() << std::endl;
    close(fd);



    return 0;
}
