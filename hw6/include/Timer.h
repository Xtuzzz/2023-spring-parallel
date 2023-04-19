//
// Created by Xtzzzz on 2023/4/7.
//

#ifndef HW6_TIMER_H
#define HW6_TIMER_H

#include <iostream>
#include <iomanip>
#include <chrono>
#include <string>
#include <unordered_map>
#include <sstream>

class Timer {
public:
    static void begin(const std::string &class_name, const std::string &func_name);

    static void end(const std::string &class_name, const std::string &func_name);

    friend std::ostream &operator<<(std::ostream &out, Timer &timer);

    Timer();

    ~Timer();

private:


    inline static Timer &get_this();

    struct Data {
        double total_run_time;
        std::chrono::time_point<std::chrono::system_clock> begin_time;
        unsigned long long count;

        Data() : total_run_time{0.0}, begin_time{}, count{0} {}
    };

    Data all;
    std::unordered_map<std::string, Data> datas;
};


#endif //HW6_TIMER_H
