#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    system("date"); //lefut
    system("hello"); //nem fut le
    return 0;
}