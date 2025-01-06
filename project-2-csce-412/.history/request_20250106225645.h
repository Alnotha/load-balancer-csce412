#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <iostream>

class Request {
private:
    std::string ipIn; 
    std::string ipOut;  
    size_t duration; 
    char jobType;         // 'S' (streaming) or 'P' (processing)m

public:
    // Basic constructor
    Request(const std::string &in, const std::string &out,
            size_t time, char type);

    // Default constructor (creates an empty / dummy request)
    Request();

    // Get how long it takes
    size_t getDuration() const;

    // Get job type
    char getJobType() const;

    // For printing a request
    friend std::ostream& operator<<(std::ostream &os, const Request &r);
};

#endif
