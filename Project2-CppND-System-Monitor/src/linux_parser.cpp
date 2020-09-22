#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  string line, key;
  float memTotal, memFree;

  std::ifstream stream(kProcDirectory + kMeminfoFilename);

  if (stream.is_open()) {
    // Read total system memory
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> key >> memTotal;

    // Read free system memory
    std::getline(stream, line);
    linestream = std::istringstream(line);
    linestream >> key >> memFree;

    // Calculate memory utilization
    float result = 1.0f - (memFree / memTotal);
    return result;
  }

  // Fall back to 0% utilization if we can't read the file
  return 0;
}

// TODO: Read and return the system uptime
int LinuxParser::UpTime() { 
    std::string line;
    long uptime;
    std::ifstream stream(kProcDirectory + kUptimeFilename);
    if (stream.is_open()) {
        std::getline(stream, line);
        std::istringstream linestream(line);
        linestream >> uptime;
        return uptime;
    }
    // Fall back to 0 uptime if we can't read the file
    return 0;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
    std::string line, key;
    int totalJiffies = 0;
    int currentJiffies = 0;
    std::ifstream stream(kProcDirectory + kStatFilename);
    if (stream.is_open()) {
      if(std::getline(stream, line)) {
        auto linestream = std::istringstream(line);
        linestream >> key;
        
        for (int i = 0; i < 10; i++) {
          linestream >> currentJiffies;
          totalJiffies += currentJiffies;
        }

        return totalJiffies;
      }
    }
    // Fall back to 0 jiffies if we can't read the file
    return 0;
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { 
    std::string line, key;
    int idleJiffies = 0;
    int temp = 0;
    std::ifstream stream(kProcDirectory + kStatFilename);
    if (stream.is_open()) {
      if(std::getline(stream, line)) {
        auto linestream = std::istringstream(line);
        linestream >> key;
        
        for (int i = 0; i < 3; i++) {
          linestream >> temp;
        }

        linestream >> idleJiffies;

        return idleJiffies;
      }
    }
    // Fall back to 0 processes if we can't read the file
    return 0;
}

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
    std::string line;
    std::string key;
    int totalProcesses;
    std::ifstream stream(kProcDirectory + kStatFilename);
    if (stream.is_open()) {
        while (std::getline(stream, line)) {
          auto linestream = std::istringstream(line);
          linestream >> key;

          if (key == "processes") {
            linestream >> totalProcesses;
            return totalProcesses;
          }
        }
    }
    // Fall back to 0 processes if we can't read the file
    return 0;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
    std::string line;
    std::string key;
    int runningProcesses;
    std::ifstream stream(kProcDirectory + kStatFilename);
    if (stream.is_open()) {
        while (std::getline(stream, line)) {
          auto linestream = std::istringstream(line);
          linestream >> key;

          if (key == "procs_running") {
            linestream >> runningProcesses;
            return runningProcesses;
          }
        }
    }
    // Fall back to 0 processes if we can't read the file
    return 0;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }