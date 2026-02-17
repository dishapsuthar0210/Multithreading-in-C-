#include <iostream>
#include <thread>
#include <vector>

using namespace std;

// Function that each thread will execute
void printThreadID(int threadNumber) {
    cout << "Thread Number: " << threadNumber
         << " | Thread ID: " << this_thread::get_id()
         << endl;
}

int main() {
    vector<thread> threads;

    // Create 5 threads using loop
    for (int i = 1; i <= 5; i++) {
        threads.push_back(thread(printThreadID, i));
    }

    // Join all threads
    for (int i = 0; i < 5; i++) {
        threads[i].join();
    }

    return 0;
}