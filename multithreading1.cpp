#include <iostream>
#include <thread>

using namespace std;

// This function will run in the secondary thread
void secondaryTask() {
    // get_id() returns the unique identifier for this thread
    cout << "Secondary Thread ID: " << this_thread::get_id() << endl;
}

int main() {
    // Print the ID of the thread that starts the program
    cout << "Main Thread ID: " << this_thread::get_id() << endl;

    // Create a new thread object 't1' and pass the function 'secondaryTask'
    thread t1(secondaryTask);

    // Join ensures the main thread waits for t1 to finish before exiting
    // This is a key focus area for Rubrik interviews 
    t1.join();

    return 0;
}