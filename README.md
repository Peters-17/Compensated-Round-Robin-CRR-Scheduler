## 1) Compensated Round-Robin (CRR) Scheduler Requirements
The current xv6 scheduler implements a very simple Round Robin (RR) policy.  For example, if there are three processes A, B and C, then the xv6 round-robin scheduler will run the jobs in the order  A B C A B C … , where each letter represents a process.  The xv6 scheduler runs each process for at most one timer tick (10 ms); after each timer tick, the scheduler moves the previous job to the end of the ready queue and dispatches the next job in the list.   The xv6 scheduler does not do anything special when a process sleeps or blocks (and is unable to be scheduled); the blocked job is simply skipped until it is ready and it is again its turn in the RR order. 

You will implement a new Compensated RR scheduler with three new features:

Different time-slice lengths (i.e., a different number of timer ticks) for different processes
Compensating processes for the amount of time they were blocked by scheduling those processes for a longer time-slice when they awake
Improving the sleep/wakeup mechanism so that processes are unblocked only after their sleep interval has expired, instead of on every 10 ms timer tick

## 2) New system calls
You’ll need to create several new system calls for this project.

### int setslice(int pid, int slice).  
This sets the time-slice of the specified pid to slice.  You should check that both pid and slice are valid (slice must be > 0); if they are not, return -1.  On successful change, return 0.  The time-slice of a process could be increased, decreased, or not changed; if pid is the currently running process, then its time-slice should be immediately changed and applied to this scheduling interval.    If the process has run for the number ticks it should run (or more) according to the new slice value (e.g. it has run 6 ticks, but the new time slice value is 4 ticks), you should schedule the next process when the timer interrupt fires.

### int getslice(int pid).  
This returns the time slice of the process with pid, which must be a positive interger.  If the pid is not valid, it returns -1.

### int fork2(int slice).  
This routine is exactly like the existing fork() system call, except the newly created process, which should begin with the specified time-slice length.   Thus, fork() could now be implemented as fork2(getslice(getpid())) since by default the child process inherits the time-slice length of the parent process.  If slice is not positive, then fork2() should return -1.

### int getpinfo(struct pstat *).   
Because your scheduler is all in the kernel, you need to extract useful information for each process by creating this system call so as to better test whether your implementation works as expected.

To be more specific, this system call returns 0 on success and -1 on failure (e.g., the argument is not a valid pointer).  If success, some basic information about each process will be returned.

## 3) New User-Level Applications
To demonstrate that your scheduler is doing at least some of the right things, you will create two new user-level applications named loop and schedtest.

First, to have a dummy job with known behavior, you will need to implement a user-level program, loop. It takes exactly 1 argument sleepT, and does the following:

First, sleep for sleepT ticks;
Then, call a loop like this which loops on a huge workload (don't try to code and run any real programs like this! It is just for testing purpose of this project):

Second, schedtest runs two copies of loop as child processes, controlling the time-slice and sleep time of each child.  The schedtest application takes exactly 5 arguments in the following order:
