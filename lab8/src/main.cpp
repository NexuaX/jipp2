#include <iostream>
#include <cstring>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <sstream>
#include <multi_mutex.hpp>

using namespace std;

mutex forks[5];
thread phils[5];
/*
mutex valet;
atomic_short count = 4;
condition_variable caller;
void philosopher(int id) {
    cout << id << " Philosopher"  << endl;
    
    while(1) {
        unique_lock<mutex> queue(valet);
        cout << id << " Thinking.. " << count << endl;
        while(count == 0) caller.wait(queue);
        count--;
        queue.unlock();
        forks[id].lock();
        forks[(id+1)%5].lock();
        cout << id << " Eating.." << endl;
        this_thread::sleep_for(chrono::seconds(5));
        forks[id].unlock();
        forks[(id+1)%5].unlock();
        cout << id << " Done." << endl;
        count++;
        caller.notify_one();
    }
    
}
/*/
multi_mutex valet(4);
void philosopher(int id) {
    cout << id << " Philosopher"  << endl;
    
    while(1) {
        cout << id << " Thinking.. " << valet.get_value() << endl;
        valet.reduce();
        forks[id].lock();
        forks[(id+1)%5].lock();
        cout << id << " Eating.." << endl;
        this_thread::sleep_for(chrono::seconds(5));
        forks[id].unlock();
        forks[(id+1)%5].unlock();
        cout << id << " Done." << endl;
        valet.increase();
    }
    
}
//*/

int main(int argc, char const * argv[]) {

    if (argc != 1 && strcmp(argv[1], "--help") == 0) {
        cout << "Usage: " << argv[0] << endl;
        cout << "Five philosophers problem example, with thread, mutex, atomic, conditional_variable libs" << endl;
        cout << "Stoped by typing stop or terminating" << endl << endl;
        return 0;
    }

    for (size_t i = 0; i < 5; i++) {
        phils[i] = thread(philosopher, i);
    }

    string command;
    while (1) {
        cin >> command;
        if (command.compare("stop") == 0) break;
    }

    cout << "All finished!" << endl; 

    return 0;
}
