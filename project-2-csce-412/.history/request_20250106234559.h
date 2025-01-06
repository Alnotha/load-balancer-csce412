/**
 * @file request.h
 * @brief Header file for the Request class.
 */

#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <iostream>

/**
 * @class Request
 * @brief Represents a network request with associated properties.
 */
class Request {
private:
    std::string ipIn;  ///< Source IP address.
    std::string ipOut; ///< Destination IP address.
    size_t duration;   ///< Duration required to process the request.
    char jobType;      ///< Type of job ('S' for simple, 'P' for priority).

public:
    /**
     * @brief Parameterized constructor for Request.
     * @param in Source IP address.
     * @param out Destination IP address.
     * @param time Duration of the request.
     * @param type Type of the job.
     */
    Request(const std::string &in, const std::string &out,
            size_t time, char type);

    /**
     * @brief Default constructor for Request.
     */
    Request();

    /**
     * @brief Retrieves the duration of the request.
     * @return Duration of the request.
     */
    size_t getDuration() const;

    /**
     * @brief Retrieves the job type of the request.
     * @return Job type.
     */
    char getJobType() const;

    /**
     * @brief Overloads the stream operator for printing requests.
     * @param os Output stream.
     * @param r Request object.
     * @return Output stream reference.
     */
    friend std::ostream& operator<<(std::ostream &os, const Request &r);
};

#endif