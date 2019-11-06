# Operating-System-Schedulers
Implementation of various Operating System Schedulers for EECS678 at the University of Kansas

## Team Members
```
Saharsh Gupta : 2826224
Blake Rieschick : 2829512
```

## Introduction
One piece of software that every modern operating system must contain in a scheduler: without one, only one task could be run at a time. In this MP, you will be writing a library to perform basic scheduling of tasks. Rather than interacting directly with the operating system, we have provided for you a discrete event simulator: we will simulate time, jobs arriving, and jobs running. Your library will inform the scheduler which job should run next.

## You will find several files:

### Programming files:
- src/simulator.c: You should not edit this file. This file is the discrete event simulator that, when ran, will interact with your library. You can find more information on how to run this at the end of this web page. This file will be replaced by the autograder, so any changes you make will be ignored.
- src/libpriqueue/libpriqueue.c and src/libpriqueue/libpriqueue.h: Files related to the priority queue. You will need to edit both of the files. You can feel free to add any helper functions, but you must implement all the functions where we provide outlines.
- src/queuetest.c: A small test case to test your priority queue, independent of the simulator. You may want to create more complex test cases in this file. The file is not used by the autograder.
- src/libscheduler/libscheduler.c and src/libscheduler/libscheduler.h: Files related to the scheduler. You may need to edit both of the files. You can feel free to add any helper functions, but you must implement all the functions where we provide outlines.

### examples.pl: 
A perl script of diff runs that tests your program aganist the 54 test output files. This file will output differences between your program and the examples.

Example input files:
- examples/proc1.csv
- examples/proc2.csv
- examples/proc3.csv
- Example output files:
- examples/proc1-c1-fcfs.out: Sample output of the simulator, using proc1.csv, 1 core, and FCFS scheduling.
- examples/proc1-c2-fcfs.out: Sample output of the simulator, using proc1.csv, 2 cores, and FCFS scheduling.
- examples/proc1-c1-sjf.out: Sample output of the simulator, using proc1.csv, 1 core, and SJF scheduling.
- examples/proc1-c2-sjf.out: Sample output of the simulator, using proc1.csv, 2 cores, and SJF scheduling.
- examples/proc1-c1-sjf.out: Sample output of the simulator, using proc1.csv, 1 core, and PSJF scheduling.
- examples/proc1-c2-sjf.out: Sample output of the simulator, using proc1.csv, 2 cores, and PSJF scheduling.
- ... (View the example directory for the full set.)

## [Part 1]: Priority Queue
To build a scheduler, a fundamental data structure is a priority queue. The first part of this MP requires you to complete libpriqueue, a priority queue library. You will be using this library in your scheduler.

libpriqueue API
To complete libpriqueue, you must implement the functions outlined in libpriqueue.c. Full function descriptions are provided for each function. In every function, you may assume that all pointers given will be valid, non-NULL pointers.

## [Part 2]: Scheduler
You will need to implement a multi-core scheduler in a simulated computer. You will be provided with a set of cores to schedule a set of tasks on, much like a real Linux scheduler.

You should use your priority queue you just built to help you complete this part of the MP.

To complete this MP, you must implement the eight functions defined in src/libscheduler/libscheduler.c. These functions are self-descriptive, but a full function outline is provided for you for each function.

Scheduler Details
The simulator will always follow a few, very specific rules. It's not important to understand the specifics of the simulator, but we provide these to help you with debugging:

All execution of tasks will happen at the very end of a time unit.
The events in a time unit will occur in this order:
1. If a job's last unit of execution occurred in the previous time unit, a scheduler_job_finished() call will be made as the first call in the new time unit.
2. If a job has finished, the quantum timer for the core will be reset. (Therefore, scheduler_quantum_expired() will never be called on a specific core at the same unit that a job has finished.)
3. In RR, if the quantum timer has expired, a scheduler_quantum_expired() will be called.
4. If any job arrives at the time unit, the scheduler_new_job() function will be called.
5. Finally, the CPU will execute the active jobs on each core.

There are a few specific cases where a scheduler needs to define behavior based on the scheduling policy provided. In this MP, you should apply the following rules:
- When multiple cores are available to take on a job, the core with the lowest id should take the job.
- A job cannot be ran on multiple cores in the same time unit. However, a job may start on one core, get preempted, and continue on a different core.
- In PSJF, if the job has been partially executed, schedule the job based on its remaining time (not the full running time).
- In RR, when a new job arrives, it must be placed at the end of the cycle of jobs. Every existing job must run some amount of time before the new job should run.
- In all schemes except RR, if two or more jobs are tied (eg: if in PRI multiple jobs have the priority of 1), use the job with the earliest arrival time. In new_job(), we provided the assumption that all jobs will have a unique arrival time. In RR, when a job is unscheduled as a result of the quantum timer expiring, it must always be placed at the end of the queue.

Consider a schedule running PPRI on a single core. After some amount of time:
- A job finished in the last time unit, resulting in a scheduler_job_finished() call to be made to your scheduler. The scheduler returns that job(id=4) should run.
- In this time unit, a new job also arrived. This results in a scheduler_new_job() call to be made to your scheduler. If the new job has greater priority, it will preempt job(j=4), which was scheduled by scheduler_job_finished(). Now job(id=5) is scheduled to run.
- Only after all jobs finished and any new job arrives will the CPU execute the task. In this example, job(id=4) was never run on the CPU when it was scheduled by scheduler_job_finished(). When calculating response time, you should not consider job as responded until it runs a CPU cycle.

### Compile and Run
To compile this MP, run:
```
make clean
make
```

To run the helper tester program for part1, run:
```
./queuetest
To run the simulator, run:
./simulator -c <cores> -s <scheme> <input file>
For example:
./simulator -c 2 -s fcfs examples/proc1.csv
```

The acceptable values for scheme (outlined above) are:
```
FCFS
SJF
PSFJ
PRI
PPRI
RR#
```
where # indicates any numeric value

We provide three sample schedules: 
- examples/proc1.csv
- examples/proc2.csv
- examples/proc3.csv. 
We also provide the expected output of those schedules in the examples directory. It's only important that lines starting with FINAL TIMING DIAGRAM match. We will not grade any output except the last few lines, as show_queue() is not required to be implemented in the same way as we did.

To test your program aganist all the test cases in an automated way, we provide a simple perl script. To run all 54 tests, simply run:
```
perl examples.pl
```
All differences will be printed. Therefore, if no data is printed, your program has passed the test cases in the examples directory.

## Grading, Submission, and Other Details
The grading will be broken down by the following percentages:
- 30% for libpriqueue
- 40% for libscheduler running with 1 core
- 30% for libscheduler running with N core
