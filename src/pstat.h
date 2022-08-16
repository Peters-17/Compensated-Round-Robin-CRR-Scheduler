#include "param.h"

#ifndef SRC_PSTAT_H_
#define SRC_PSTAT_H_

// process stats snapshot, these
// corresponds to global ptable.proc structure fields
struct pstat {
    // whether this slot of the process table is in use (1 or 0)
    int inuse[NPROC];
    int pid[NPROC];  // PID of each process
    int timeslice[NPROC];
    int compticks[NPROC];
    int schedticks[NPROC];
    int sleepticks[NPROC];
    int switches[NPROC];
};

#endif  // SRC_PSTAT_H_
