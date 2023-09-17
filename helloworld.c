#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
int main(){
    const char* message = "Hello, World!\n";
    write(1, message, sizeof(message) - 1); 
    return 0;
}
