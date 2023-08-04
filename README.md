# Dining Philosophers Problem

The Dining Philosophers problem is a classic example of a multi-process synchronization problem. The problem consists of five philosophers sitting at a table who do nothing but think and eat. Between each philosopher, there is a single fork. In order to eat, a philosopher must get both forks surrounding him. 

The problem is how to design a discipline of behavior (a concurrent algorithm) such that each philosopher will not starve; i.e., can forever continue to alternate between eating and thinking, assuming that no philosopher can know when others may want to eat or think.

## Learning Outcomes

By implementing a solution to the Dining Philosophers problem, you will gain a deeper understanding of:

- Concurrency and the challenges associated with designing concurrent algorithms.
- The concept of threads and processes, and how they are used in concurrent programming.
- The use of synchronization primitives like mutexes and semaphores.
- The concepts of deadlock and starvation, and strategies to prevent them.

## Definitions

### Thread

A thread is the smallest unit of execution in a process. In other words, a thread is a sequence of instructions that can be scheduled and executed independently by the operating system. Multiple threads within a process share the same data space, which means they can communicate with each other more easily than if they were separate processes.

For example, in a web browser, one thread might display the user interface, another thread might handle network communication, and a third thread might play audio or video.

### Process

A process is an instance of a computer program that is being executed. It contains the program code and its current activity. Each process has a separate memory space, which means that a process runs independently and is isolated from other processes. If a process wants to communicate with another process, it needs to use a form of inter-process communication (IPC).

For example, when you open a text editor or a web browser, you are starting a new process.

### Difference between Thread and Process

The main difference between a thread and a process is that threads within the same process can share the same memory space, while each process has its own memory space. This makes communication between threads fast and straightforward, while communication between processes requires more complex techniques.

### Mutex

A mutex (short for "mutual exclusion") is a synchronization primitive that can be used to protect shared resources from concurrent access by multiple threads or processes. A mutex provides a lock that only one thread can hold at a time. If a thread has locked a mutex, any other thread that attempts to lock the same mutex will block until the first thread has unlocked the mutex.

For example, if multiple threads are writing to the same file, a mutex can be used to ensure that only one thread writes to the file at a time, preventing data corruption.

## Implementation Steps

Here are the steps to implement the Dining Philosophers problem:

1. **Structures**: Define a structure to represent a philosopher. This structure should contain the philosopher's ID, the IDs of the forks it can use (left and right), a mutex for changing the philosopher's state, and other necessary data (like count of times each philosopher has eaten).

2. **Initialization**: Initialize the philosophers and their corresponding forks. You can use dynamic memory allocation (`malloc`) for this. Also, initialize the mutexes. The number of philosophers, time to eat, time to sleep, and time to die are all passed as command-line arguments and stored in the philosopher structure.

3. **Thread Creation**: Create a separate thread for each philosopher. These threads will run concurrently, simulating the philosophers thinking and eating at the same time. The `philosophers_threads` function is used as the start routine for each thread.

4. **Routine Function**: Define a routine function that each thread will execute. This function should implement the logic of a philosopher's actions - thinking, getting forks (both left and right), eating, putting forks down, and then thinking again. Use mutex locks to ensure that when a philosopher picks up a fork, no other philosopher can pick it up at the same time.

5. **Checking for Deadlock/Starvation**: Implement checks to ensure that no philosopher is starving, i.e., each philosopher gets a chance to eat. Also, implement checks to prevent deadlock, i.e., a situation where each philosopher is holding one fork and waiting for the other, causing all of them to wait indefinitely. The `check_death` function checks if a philosopher has not eaten within the time to die, and if so, it prints a message and returns 1, ending the program.

6. **Sleep and Think**: After a philosopher finishes eating, they sleep for a certain amount of time (specified by the `time_to_sleep` parameter), and then think. The `sleep_and_think` function implements this behavior.

7. **Print Status**: The `print` function is used to print the status of each philosopher (taking a fork, eating, sleeping, thinking). A mutex lock is used to ensure that the print statements from different threads do not overlap.

Remember, the key to solving the Dining Philosophers problem is to ensure that the philosophers' actions are properly synchronized, and that resources (the forks) are properly managed to prevent deadlock and starvation.
