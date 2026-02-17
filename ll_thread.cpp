#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

Node* head = nullptr;   // Shared global pointer

// 🚨 NOT THREAD SAFE
void insert(int value) {
    Node* newNode = new Node(value);

    // Step 1: read current head
    newNode->next = head;

    // 🔥 Force context switch to increase race chance
    this_thread::sleep_for(chrono::microseconds(50));

    // Step 2: update head
    head = newNode;
}

void threadTask(int startValue) {
    for (int i = 0; i < 10; i++) {
        insert(startValue + i);
    }
}

void printList() {
    Node* temp = head;
    int count = 0;

    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
        count++;
    }

    cout << "\nTotal nodes: " << count << endl;
}

int main() {
    vector<thread> threads;

    // Create 5 threads
    for (int i = 0; i < 5; i++) {
        threads.push_back(thread(threadTask, i * 100));
    }

    // Wait for all threads
    for (auto &t : threads) {
        t.join();
    }

    printList();

    return 0;
}