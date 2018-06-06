#include <iostream>
#include <cstdio>
#include <cstring>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>
#include <regex>

#define STRING_SIZE 80

int main()
{
    std::regex logPassRegex("(.*)\\/(.*)");
    std::cmatch pieces_match;

    int fd1;

    const char* myfifo = "/tmp/myfifo";

    mkfifo(myfifo, 0666);

    std::string str1;
    str1.resize(STRING_SIZE);

    std::string str2;
    str2.resize(STRING_SIZE);

    fd1 = open(myfifo, O_RDONLY);
    read(fd1, &str1.at(0), STRING_SIZE);

    std::cout << "User1: " << str1.data() << std::endl;
    close(fd1);

    fd1 = open(myfifo, O_WRONLY);

    if (std::regex_search(str1.data(), pieces_match, logPassRegex))
    {
        if (pieces_match[1].str() == "log" && pieces_match[2].str() == "pass")
        {
            str2 = "succesfull";
        }
        else
        {
            str2 = "fail";
        }
    }
    else
    {
        str2 = "fail";
    }

    write(fd1, str2.data(), str2.size() + 1);
    close(fd1);

    return 0;
}