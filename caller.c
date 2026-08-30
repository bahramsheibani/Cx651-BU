#include <unistd.h>
#include <sys/syscall.h>
#include <string.h>

int main() {
    int out = write(STDOUT_FILENO, "hello STDOUT\n", strlen("hello STDOUT\n"));
    int err = write(STDERR_FILENO, "ERROR: this is an error", strlen("ERROR: this is an error"));
    return 0;
   
}