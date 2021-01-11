#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

int Process::Pid() { return 0;} 

float Process::CpuUtilization() { return 0; }

string Process::Command() { return string(); }

string Process::Ram() { return string(); }

string Process::User() { return string(); }

long int Process::UpTime() { return 0; }

bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }

