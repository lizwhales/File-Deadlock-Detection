# File-Deadlock-Detection
Command line program to detect file deadlocks based off processes and resource allocation.

## 1 Detecting and breaking locks
You will be given a description of running processes and the files they need to execute, where each process
is associated with two files. The first one is the file that the process has locked and the second one is
the file that it is waiting to lock. The goal of your program is to determine whether given the current
resource allocation and requests there is a deadlock or not. Please see Week 2 Lecture 2 on deadlocks
for more information.
If there is no deadlock, you are asked to compute the minimum execution time required for all processes
to finish given the following specification. If a process locked a file, it takes 1 time unit to operate on
this file and release it. If a process requested a file, after a process is given this file, it takes 1 time
unit to operate on this file and release it. Hence, any process takes at least 2 time units to finish. If k
processes have requested the same file, it will take k time units for the processes to finish, where k ≥1.
Processes that have locked or requested distinct files can operate in parallel. That is, if two processes
have requested two different files then it will take a total of 1 time unit for the processes to operate on
these files if both files are not locked by other processes.
If there is a deadlock, you are asked to return process(es) that have to be terminated in order to resolve
the deadlock.

## 2 Program Specification

Your program will be invoked via the command line. It must be called detect and take the following
command line arguments. The arguments can be passed in any order but you can assume that they
will be passed exactly once.
-f **filename** specifies the path to the file describing requests.
-e is an optional parameter, which when provided requires your code to compute execution time. If this
option is not given, your code should identify presence or absence of deadlocks and which processes
need to be terminated to resolve deadlock(s).
-c is an optional parameter, which when provided invokes your file per process allocation from Section 4.
The file specified by *filename* contains the processes and their locked and requested resources in the
following format.
Each line of the file corresponds to a process and consists of a space-separated tuple: 

```process-id space file-id space file-id```

where the first file-id is the file that the process has locked and the second file-id is the file requested by
the process. You can assume that all process-ids will be distinct integers in the domain of [0, 232). You
can assume that all file-ids will be integers in the domain of [0, 232).
Example: ```./detect -f resources.txt```
The detection program is required to determine if there is a deadlock in the current resource allocation.
For example resources.txt with the following information:
0 1 3
1 2 7
describes a system where process 0 has locked file 1 and is waiting for file 3 while process 1 has locked
file 2 and waiting for file 7.
If resources.txt has the following information:
0 1 2
1 2 1
then the system has processes 0 and 1, with locks on files 1 and 2, respectively. In addition, process 0
requested file 2 while process 1 requested file 1. Hence, there is a deadlock.
Each line (including the last) will be terminated with a LF (ASCII 0x0a) control character.
We will not give malformed input (e.g., negative ids for processes and files, non-space delimiters, situa-
tions where more than one process locked the same file).
