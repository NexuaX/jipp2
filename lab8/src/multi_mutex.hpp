/* multi_mutex class header
** author: Albert Mouhoubi
*/

#ifndef MULTI_MUTEX
#define MULTI_MUTEX

#include <condition_variable>
#include <atomic>
#include <mutex>

using namespace std;

class multi_mutex {
private:
    mutex locker;
    atomic_short counter;
    condition_variable caller;
public:
    multi_mutex();
    multi_mutex(short value);
    void reduce();
    void reduce(short n);
    void increase();
    void increase(short n);

    void set_value(short n);
    short get_value();
};

#endif
