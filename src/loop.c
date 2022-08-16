#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char **argv) {
    int sleepT = 0;
    if (argc != 2) {
        printf(1, "Usage: loop <# of sleep ticks>\n");
        exit();
    }
    sleepT = atoi(argv[1]);
    sleep(sleepT);
    int i = 0, j = 0;
    while (i < 800000000) {
        j += i * j + 1;
        i++;
    }
    exit();
}
