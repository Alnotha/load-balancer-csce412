
/**
 * @file request.cpp
 * @brief Implementation of the Request class.
 */

#include "request.h"

/**
 * @brief Constructs a Request with given parameters.
 * @param in Source IP address.
 * @param out Destination IP address.
 * @param time Duration of the request.
 * @param type Type of the job.
 */
Request::Request(const std::string &in, const std::string &out, size_t time, char type)
    : ipIn(in), ipOut(out), duration(time), jobType(type) {}

/**
 * @brief Constructs a default Request object.
 */
Request::Request() : ipIn(""), ipOut(""), duration(0), jobType('U') {}

/**
 * @brief Retrieves the duration of the request.
 * @return Duration of the request.
 */
size_t Request::getDuration() const {
    return duration;
}

/**
 * @brief Retrieves the job type of the request.
 * @return Job type.
 */
char Request::getJobType() const {
    return jobType;
}

/**
 * @brief Overloads the stream operator for printing requests.
 * @param os Output stream.
 * @param r Request object.
 * @return Output stream reference.
 */
std::ostream& operator<<(std::ostream &os, const Request &r) {
    os << "Request(" << r.ipIn << "->" << r.ipOut
       << ", time=" << r.duration << ", type=" << r.jobType << ")";
    return os;
}