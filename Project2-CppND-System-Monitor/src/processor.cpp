#include "processor.h"
#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {

    auto stats = LinuxParser::CpuUtilization();
    int user = std::stoi(stats[0]);
    int nice = std::stoi(stats[1]);
    int system = std::stoi(stats[2]);
    int idle = std::stoi(stats[3]);
    int iowait = std::stoi(stats[4]);
    int irq = std::stoi(stats[5]);
    int softirq = std::stoi(stats[6]);
    int steal = std::stoi(stats[7]);

    idle = idle + iowait; //include iowait in idle
    int nonIdle = user + nice + system + irq + softirq + steal;

    int prevTotal = prevIdle_ + prevNonIdle_;
    int total = idle + nonIdle;

    // differentiate : actual value minus the previous one
    int totald = total - prevTotal;
    int idled = idle - prevIdle_;

    prevIdle_ = idle;
    prevNonIdle_ = nonIdle;

    return (float)(totald - idled) / (float)totald;
}