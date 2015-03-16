Tom Diehl
CS360
Philo.c

This program simulates the dining philosopher problem by forking 5 
process to simulate the philosophers.  It the uses shared memory to
hold the chopsticks and a mutex semaphore to avoid shared memory
conflicts.  It prints out which philosopher is eating and thinking
along with the total time spent eating or thinking.  When a 
philosopher reaches 100 seconds eating time they get up and leave the table. 

Include Files:

philo.c
README.txt

When compiling from terminal use:

gcc -Wall -std=c99 philo.c -o philo -lm

