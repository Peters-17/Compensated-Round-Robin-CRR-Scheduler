#include "pstat.h"
#include "types.h"
#include "user.h"

int main(int argc, char **argv) {
    if (argc != 6) {
        printf(2, "invalid schedtest arguments\n");
        exit();
    }
    int sliceA = atoi(argv[1]);
    int sliceB = atoi(argv[3]);
    int sleepParent = atoi(argv[5]);
    // spawn two children with fork2()
    int pidA = fork2(sliceA);
    if (pidA < 0) {
        printf(2, "schedtest: fork failed\n");
        exit();
    } else if (pidA == 0) {
        // child A
        // exec "sleep" with sleepA as argument
        char *argvA[3];
        argvA[0] = "loop";
        argvA[1] = argv[2];
        argvA[2] = 0;
        exec(argvA[0], argvA);
        exit();
    } else {
        // parent
        int pidB = fork2(sliceB);
        if (pidB < 0) {
            printf(2, "schedtest: fork failed\n");
            exit();
        } else if (pidB == 0) {
            // child B
            char *argvB[3];
            argvB[0] = "loop";
            argvB[1] = argv[4];
            argvB[2] = 0;
            exec(argvB[0], argvB);
            exit();
        } else {
            // parent
            sleep(sleepParent);
            // getpinfo
            struct pstat p;
            int code = getpinfo(&p);
            if (code != 0) {
                printf(2, "schedtest: getpinfo failed\n");
                kill(pidA);
                kill(pidB);
                exit();
            }
            int compticksA = -1;
            int compticksB = -1;
            for (int i = 0; i < NPROC; i++) {
                if (p.pid[i] == pidA) {
                    compticksA = p.compticks[i];
                }
                if (p.pid[i] == pidB) {
                    compticksB = p.compticks[i];
                }
            }
            printf(1, "%d %d\n", compticksA, compticksB);
            // wait for children to exit
            wait();
            wait();
            exit();
        }
    }
}

