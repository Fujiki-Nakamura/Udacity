#ifndef PROCESS_H
#define PROCESS_H

#include <string>

class Process {
    public:
        Process(int pid);
        int Pid() const;
        std::string User const;
        std::string Command() const;
        float CpuUtilization() const;
        void CpuUtilization(long active_ticks_, long system_ticks);
        long Jiffies() const;
        std::string Ram() const;
        log int UpTime() const;
        bool operator<(const Process& a) const;
        bool operator>(const Process& a) const;

    private:
        int pid_;
        float cpu_{0};
        long cached_active_ticks_{0};
        long cached_idle_ticks_{0};
        long cached_system_ticks_{0};
};

#endif
