#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <sstream>

using std::string;
using std::to_string;
using std::ostringstream;
using std::ostream;
using std::move;

// A simple Request class with IP in, IP out, and how long the request takes
class Request {
private:
    string ipFrom;    // incoming IP
    string ipTo;      // outgoing IP
    size_t duration;  // how many units of time it takes

public:
    Request()
        : ipFrom(""), ipTo(""), duration(0) {
    }

    Request(const string &i1, const string &i2, size_t d)
        : ipFrom(i1), ipTo(i2), duration(d) {
    }

    Request(const Request &other)
        : ipFrom(other.ipFrom), ipTo(other.ipTo), duration(other.duration) {
    }

    Request(Request &&other)
        : ipFrom(move(other.ipFrom)), ipTo(move(other.ipTo)), duration(other.duration) {
        other.duration = 0;
    }

    ~Request() {}

    Request &operator=(const Request &other) {
        if (this != &other) {
            ipFrom = other.ipFrom;
            ipTo = other.ipTo;
            duration = other.duration;
        }
        return *this;
    }

    Request &operator=(Request &&other) {
        if (this != &other) {
            ipFrom = move(other.ipFrom);
            ipTo = move(other.ipTo);
            duration = other.duration;
            other.duration = 0;
        }
        return *this;
    }

    // get how long it takes
    const size_t &getDuration() const {
        return duration;
    }

    // print it for debugging
    friend ostream &operator<<(ostream &os, const Request &req) {
        os << "Request(" << req.ipFrom << " -> " << req.ipTo
           << ", duration=" << to_string(req.duration) << ")";
        return os;
    }
};

#endif // REQUEST_H
