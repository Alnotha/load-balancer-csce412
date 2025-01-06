#include "request.h"

Request::Request(const std::string &in, const std::string &out, size_t time, char type) : ipIn(in), ipOut(out), duration(time), jobType(type) {}

 : ipIn(""), ipOut(""), duration(0), jobType('U') {}  
    // 'U' for undefined

size_t Request::getDuration() const {
    return duration;
}

char Request::getJobType() const {
    return jobType;
}

std::ostream& operator<<(std::ostream &os, const Request &r) {
    os << "Request(" << r.ipIn << "->" << r.ipOut
       << ", time=" << r.duration << ", type=" << r.jobType << ")";
    return os;
}
