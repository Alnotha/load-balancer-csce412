#include "request.h"
#include <utility> // for std::move

Request::Request()
    : ipFrom(""), ipTo(""), duration(0) {}

Request::Request(const std::string &i1, const std::string &i2, size_t d)
    : ipFrom(i1), ipTo(i2), duration(d) {}

Request::Request(const Request &other)
    : ipFrom(other.ipFrom), ipTo(other.ipTo), duration(other.duration) {}

Request::Request(Request &&other)
    : ipFrom(std::move(other.ipFrom)),
      ipTo(std::move(other.ipTo)),
      duration(other.duration)
{
    other.duration = 0;
}

Request::~Request() {}

Request &Request::operator=(const Request &other) {
    if (this != &other) {
        ipFrom   = other.ipFrom;
        ipTo     = other.ipTo;
        duration = other.duration;
    }
    return *this;
}

Request &Request::operator=(Request &&other) {
    if (this != &other) {
        ipFrom   = std::move(other.ipFrom);
        ipTo     = std::move(other.ipTo);
        duration = other.duration;
        other.duration = 0;
    }
    return *this;
}

const size_t &Request::getDuration() const {
    return duration;
}

std::ostream &operator<<(std::ostream &os, const Request &req) {
    os << "Request(" << req.ipFrom << " -> " << req.ipTo
       << ", duration=" << req.duration << ")";
    return os;
}
