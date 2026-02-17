#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

Node* head = nullptr;
mutex mtx;   // 🔐 Global mutex

// ✅ THREAD SAFE INSERT
void insert(int value) {
    lock_guard<mutex> lock(mtx);   // Automatically locks & unlocks

    Node* newNode = new Node(value);
    newNode->next = head;
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

    // Join all threads
    for (auto &t : threads) {
        t.join();
    }

    printList();

    return 0;
}