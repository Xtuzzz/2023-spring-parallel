//
// Created by Xtzzzz on 2023/4/7.
//

#include "Timer.h"

#define max(a, b) a>b?a:b

Timer::Timer() {
    this->all.begin_time = std::chrono::system_clock::now();
    this->all.count = 1;
}

Timer &Timer::get_this() {
    static Timer t;
    return t;
}

Timer::~Timer() {

}

void Timer::begin(const std::string &class_name, const std::string &func_name) {
    std::string name = class_name + " " + func_name;
    std::unordered_map<std::string, Data>::iterator it = get_this().datas.find(name);
    if (it == get_this().datas.end()) {
        get_this().datas[name] = Data();
        it = get_this().datas.find(name);
    }
    it->second.begin_time = std::chrono::system_clock::now();
}

void Timer::end(const std::string &class_name, const std::string &func_name) {
    std::string name = class_name + " " + func_name;
    std::unordered_map<std::string, Data>::iterator it = get_this().datas.find(name);
    if (it != get_this().datas.end()) {
        std::chrono::duration<double, std::milli> duration_ms =
                std::chrono::system_clock::now() - it->second.begin_time;
        it->second.total_run_time += duration_ms.count() / 1000;
        it->second.count++;
    } else {
        std::cout << "function " << name << " is not defined" << std::endl;
    }
}

std::ostream &operator<<(std::ostream &out, Timer &timer) {
    std::chrono::duration<double, std::milli> duration_ms =
            std::chrono::system_clock::now() - timer.get_this().all.begin_time;
    timer.get_this().all.total_run_time = duration_ms.count() / 1000;

    static const std::string class_name = "Class Name";
    static const int class_name_size = max((int) class_name.length(), 18);

    static const std::string func_name = "Function Name";
    static const int func_name_size = max((int) func_name.length(), 18);

    static const std::string total_time = "Total";
    static const int total_time_size = max((int) total_time.length(), 12);

    static const std::string called_times = "Called Times";
    const int called_times_size = max((int) called_times.length(), 12);

    static const std::string avg = "Avg Times";
    const int avg_size = max((int) avg.length(), 12);

    static const std::string percentage = "Percentage";
    const int percentage_size = max((int) percentage.length(), 12);

    out << "+--------------------" << std::endl;
    out << "| Profiling Summery ..." << std::endl;
    out << "+---------------------------------------" << std::endl;

    out << "| ";
    out.width(class_name_size);
    out << std::left << class_name;
    out << " |";
    out.width(func_name_size);
    out << std::right << func_name;
    out << " |";
    out.width(total_time_size);
    out << std::right << total_time;
    out << " |";
    out.width(called_times_size);
    out << std::right << called_times;
    out << " |";
    out.width(avg_size);
    out << std::right << avg;
    out << " |";
    out.width(percentage_size);
    out << std::right << percentage;
    out << " |" << std::endl;

    double total_run_time = timer.get_this().all.total_run_time;
    out << "| ";
    out.width(class_name_size);
    out << std::left << "" << " |";

    out.width(func_name_size);
    out << std::right << "Total Run Time" << " |";

    out.width(total_time_size - (int) sizeof("s"));
    out << std::right << std::setprecision(6) << std::fixed << total_run_time << " s |";

    out.width(called_times_size - (int) sizeof("times"));
    out << std::right << 1 << " times |";

    out.width(avg_size - (int) sizeof("s"));
    out << std::right << std::setprecision(6) << std::fixed << total_run_time << " s |";

    out.width(percentage_size - (int) sizeof("%"));
    out << std::right << std::setprecision(1) << std::fixed << 100.0 << " % |" << std::endl;

    std::unordered_map<std::string, Timer::Data>::iterator it;
    for (it = timer.get_this().datas.begin(); it != timer.get_this().datas.end(); it++) {

        std::string func_, class_;
        std::istringstream ss{it->first};
        ss >> class_ >> func_;

        out << "| ";
        out.width(class_name_size);
        out << std::left << class_ << " |";

        out.width(func_name_size);
        out << std::right << func_ << " |";

        out.width(total_time_size - (int) sizeof("s"));
        out << std::right << std::setprecision(6) << std::fixed
            << it->second.total_run_time << " s |";

        out.width(called_times_size - (int) sizeof("times"));
        out << std::right << it->second.count << " times |";

        out.width(avg_size - (int) sizeof("s"));
        out << std::right << std::setprecision(6) << std::fixed
            << it->second.total_run_time / it->second.count << " s |";

        out.width(percentage_size - (int) sizeof("%"));
        out << std::right << std::setprecision(1) << std::fixed
            << 100*it->second.total_run_time / total_run_time << " % |"
            << std::endl;
    }

    return out;
}
