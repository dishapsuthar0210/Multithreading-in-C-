#include <iostream>
#include <thread>
#include <vector>
#include <shared_mutex>
#include<mutex>

using namespace std;

#define SIZE 100

class Stack {
private:
    int arr[SIZE];
    int top;
    mutable shared_mutex smtx;   // allows multiple readers

public:
    Stack() : top(-1) {}

    // Writer (exclusive lock)
    void push(int value) {
        unique_lock<shared_mutex> lock(smtx);

        if (top >= SIZE - 1) {
            cout << "Overflow\n";
            return;
        }

        arr[++top] = value;
        cout << "Pushed: " << value << endl;
    }

    // Writer (exclusive lock)
    void pop() {
        unique_lock<shared_mutex> lock(smtx);

        if (top < 0) {
            cout << "Underflow\n";
            return;
        }

        cout << "Popped: " << arr[top] << endl;
        top--;
    }

    // Reader (shared lock)
    void peek() const {
        shared_lock<shared_mutex> lock(smtx);

        if (top < 0) {
            cout << "Stack Empty\n";
            return;
        }

        cout << "Top: " << arr[top] << endl;
    }

    // Reader
    void printSize() const {
        shared_lock<shared_mutex> lock(smtx);
        cout << "Current size: " << top + 1 << endl;
    }
};

int main() {

    Stack st;

    // Writer thread
    thread t1([&]() {
        for (int i = 0; i < 20; i++)
            st.push(i);
    });

    // Writer thread
    thread t2([&]() {
        for (int i = 0; i < 10; i++)
            st.pop();
    });

    // Multiple reader threads
    thread t3([&]() {
        for (int i = 0; i < 10; i++)
            st.peek();
    });

    thread t4([&]() {
        for (int i = 0; i < 10; i++)
            st.printSize();
    });

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}