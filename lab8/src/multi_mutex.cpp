/* multi_mutex class implementation
** author: Albert Mouhoubi
*/

#include <multi_mutex.hpp>

using namespace std;

multi_mutex::multi_mutex() : multi_mutex(1) {}

multi_mutex::multi_mutex(short n) {
    counter = n;
}

void multi_mutex::reduce() {
    unique_lock<mutex> queue(locker);
    while(counter < 1) caller.wait(queue);
    counter--;
    queue.unlock();
}

void multi_mutex::reduce(short n) {
    unique_lock<mutex> queue(locker);
    while(counter < n) caller.wait(queue);
    counter.fetch_sub(n);
    queue.unlock();
}

void multi_mutex::increase() {
    counter++;
    caller.notify_one();
}

void multi_mutex::increase(short n) {
    counter.fetch_add(n);
    caller.notify_one();
}

void multi_mutex::set_value(short n) {
    counter.exchange(n);
}

short multi_mutex::get_value() {
    return counter.load();
}
