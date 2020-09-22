#include "processor.h"
#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {

    auto totalJiffies = (float)LinuxParser::Jiffies();
    auto idleJiffies = (float)LinuxParser::IdleJiffies();

    float utilization = 1.0 - idleJiffies / totalJiffies;
    return utilization;
}