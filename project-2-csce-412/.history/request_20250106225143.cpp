#include "request.h"
#include <cstdlib>
#include <sstream>

// Constructor
Request::Request(const std::string &ipIn, const std::string &ipOut, int time, char jobType)
    : ipIn(ipIn), ipOut(ipOut), time(time), jobType(jobType) {}


// Generate a random request
Request Request::generateRandomRequest() {
    auto randomIP = []() {
        return std::to_string(rand() % 256) + "." +
               std::to_string(rand() % 256) + "." +
               std::to_string(rand() % 256) + "." +
               std::to_string(rand() % 256);
    };
    std::string ipIn = randomIP();
    std::string ipOut = randomIP();
    int time = rand() % 20 + 1; // Random processing time between 1 and 20
    char jobType = (rand() % 2 == 0) ? 'S' : 'P'; // 'S' or 'P'
    return Request(ipIn, ipOut, time, jobType);
}

// Get the time of the request
int Request::getTime() const {
    return time;
}

// Get description of the request
std::string Request::getDescription() const {
    std::ostringstream oss;
    oss << "Request(" << ipIn << "->" << ipOut << ", time=" << time << ", type=" << jobType << ")";
    return oss.str();
}
