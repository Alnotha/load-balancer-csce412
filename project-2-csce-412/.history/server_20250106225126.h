#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string>
#include "request.h"

class Server {
private:
    std::string serverName;
    Request currentReq;   // The request we're working on
    bool busy;            // True if actively processing
    size_t timeSpent;     // How many ticks spent on current request

public:
    // Simple constructor
    Server(const std::string &name);

    // Check if server is busy
    bool isBusy() const;

    // Assign a new request to this server
    void setRequest(const Request &r);

    // Process the current request by 1 time step
    void handleRequest();

    // Return name (for printing/logging)
    const std::string& getName() const;

    // Did we finish a request on this tick?
    bool hasRequestFinished() const;

    // Access the current request
    const Request& getCurrentRequest() const;

    // Clear after finishing
    void clearCurrentRequest();
};

#endif
