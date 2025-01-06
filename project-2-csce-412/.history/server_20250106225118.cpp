#include "server.h"
#include <iostream>

// Constructor
Server::Server(const std::string &name) : name(name), busy(false), remainingTime(0) {}

// Assign a request to the server
void Server::assignRequest(const Request &req) {
    currentRequest = req;
    busy = true;
    remainingTime = req.getTime();
}

// Process the current request
void Server::processRequest() {
    if (busy) {
        --remainingTime;
        if (remainingTime <= 0) {
            busy = false;
        }
    }
}

// Check if the server is busy
bool Server::isBusy() const {
    return busy;
}

// Print the status of the server
void Server::printStatus() const {
    if (busy) {
        std::cout << name << " processing: " << currentRequest.getDescription()
                  << " (remaining time: " << remainingTime << ")\n";
    } else {
        std::cout << name << " is idle.\n";
    }
}
