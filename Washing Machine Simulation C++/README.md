# AOS ASSIGNMENT 5

The solution employs multi-threading to simulate the concurrent usage of washing machines by students. Each student is represented by a separate thread that handles their arrival, waiting for a washing machine, and either starting the washing process or leaving based on their patience.

# Key Components:
## Semaphores:

washing_machines Semaphore: Represents the pool of available washing machines (M). Initialized with a value of M, allowing up to M students to wash simultaneously.

## Mutexes:

print_mutex: Ensures that log messages are printed without interleaving, maintaining clarity in the output.
counter_mutex: Protects the shared counter tracking the number of students who left without washing.

## Student Threads:

Each thread simulates a student:
Arrival: Sleeps until the student's arrival time (T<sub>i</sub>).
Attempt to Acquire Washing Machine: Tries to acquire the washing_machines semaphore within the patience time (P<sub>i</sub>).
Washing Process:
If successful, logs the start of washing, sleeps for the washing duration (W<sub>i</sub>), and then logs the completion.
Leaving Without Washing:
If unable to acquire a washing machine within the patience time, logs the departure and increments the counter.

## Final Statistics:

After all threads complete, the program calculates whether additional washing machines are needed based on the number of students who left without washing.

# Implementation

1. Student Representation
Each student is modeled using a Student struct containing:

id: Unique identifier (1-based index).
arrival_time (T<sub>i</sub>): Time after program execution when the student arrives.
wash_time (W<sub>i</sub>): Duration required to wash clothes.
patience_time (P<sub>i</sub>): Maximum time the student is willing to wait before leaving.

2. Thread Functionality
The student_thread function handles the lifecycle of a student:

Arrival Simulation:
The thread sleeps for arrival_time seconds to simulate the student's arrival.
Logging Arrival:
Upon waking, the student logs their arrival.
Attempt to Acquire Washing Machine:
Uses sem_timedwait with a timeout set to arrival_time + patience_time to attempt acquiring a washing machine.
Washing or Leaving:
If the semaphore is acquired before patience runs out, the student logs the start of washing, sleeps for wash_time seconds, logs completion, and releases the semaphore.
If unable to acquire the semaphore within the patience time, the student logs leaving without washing and increments the students_left_without_washing counter.

3. Synchronization Mechanisms
Semaphores:
Manage access to the limited number of washing machines.
Mutexes:
print_mutex: Ensures that log messages from different threads do not interleave, maintaining readable and coherent output.
counter_mutex: Protects the shared counter students_left_without_washing to prevent race conditions during increments.

4. Main Function Workflow
Input Handling:
Reads the number of students (N) and washing machines (M).
Collects each student's T<sub>i</sub>, W<sub>i</sub>, and P<sub>i</sub>.
Initialization:
Initializes the washing_machines semaphore with a value of M.
Initializes mutexes.
Thread Creation:
Creates a thread for each student, passing the corresponding Student struct.
Thread Joining:
Waits for all student threads to complete their execution.
Statistics Calculation:
Outputs the total number of students who left without washing.
Determines and outputs whether more washing machines are needed based on the 25% threshold.
Cleanup:
Destroys the semaphore and mutexes to free resources.

# Compilation

g++ -std=c++11 -pthread -o solution solution.cpp

./solution
