#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <vector>
#include <chrono>
#include <thread>
#include <errno.h>
#include <cstring>
#include <mutex>

using namespace std;

struct Student {
    int id;            
    int arrival_time;  
    int wash_time;      
    int patience_time;  
};

int N, M; 
sem_t washing_machines; 
pthread_mutex_t print_mutex = PTHREAD_MUTEX_INITIALIZER; 
int students_left_without_washing = 0; 
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER; 

void* student_thread(void* arg) {
    Student* student = (Student*)arg;

    sleep(student->arrival_time);

    struct timespec t_arrival;
    clock_gettime(CLOCK_REALTIME, &t_arrival);

    pthread_mutex_lock(&print_mutex);
    cout << "Student " << student->id << " arrives" << endl;
    pthread_mutex_unlock(&print_mutex);

    struct timespec t_deadline = t_arrival;
    t_deadline.tv_sec += student->patience_time;

    struct timespec ts = t_deadline;
    ts.tv_sec += 1; 

    int ret = sem_timedwait(&washing_machines, &ts);

    if (ret == 0) {
        struct timespec t_now;
        clock_gettime(CLOCK_REALTIME, &t_now);

        if (t_now.tv_sec <= t_deadline.tv_sec) {
            pthread_mutex_lock(&print_mutex);
            cout << "Student " << student->id << " starts washing" << endl;
            pthread_mutex_unlock(&print_mutex);

            sleep(student->wash_time);

            sem_post(&washing_machines);

            pthread_mutex_lock(&print_mutex);
            cout << "Student " << student->id << " leaves after washing" << endl;
            pthread_mutex_unlock(&print_mutex);
        } 
        else {
            sem_post(&washing_machines);

            pthread_mutex_lock(&print_mutex);
            cout << "Student " << student->id << " leaves without washing" << endl;
            pthread_mutex_unlock(&print_mutex);

            pthread_mutex_lock(&counter_mutex);
            students_left_without_washing++;
            pthread_mutex_unlock(&counter_mutex);
        }
    } else {
        pthread_mutex_lock(&print_mutex);
        cout << "Student " << student->id << " leaves without washing" << endl;
        pthread_mutex_unlock(&print_mutex);

        pthread_mutex_lock(&counter_mutex);
        students_left_without_washing++;
        pthread_mutex_unlock(&counter_mutex);
    }

    pthread_exit(NULL);
}

int main() {
    cin >> N >> M;

    vector<Student> students(N);

    for (int i = 0; i < N; ++i) {
        students[i].id = i + 1; 
        cin >> students[i].arrival_time >> students[i].wash_time >> students[i].patience_time;
    }

    pthread_mutex_lock(&print_mutex);
    pthread_mutex_unlock(&print_mutex);

    sem_init(&washing_machines, 0, M);

    vector<pthread_t> threads(N);

    for (int i = 0; i < N; ++i) {
        pthread_create(&threads[i], NULL, student_thread, (void*)&students[i]);
    }

    for (int i = 0; i < N; ++i) {
        pthread_join(threads[i], NULL);
    }

    cout << students_left_without_washing << endl;

    if (students_left_without_washing * 4 >= N) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    sem_destroy(&washing_machines);
    pthread_mutex_destroy(&print_mutex);
    pthread_mutex_destroy(&counter_mutex);

    return 0;
}
