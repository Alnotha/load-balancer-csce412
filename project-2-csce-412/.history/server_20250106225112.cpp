#include "server.h"
#include <iostream>

Server::Server(const std::string &name)
    : name(name), busy(false), remainingTime(0), currentRequest("", "", 0, 'P') {}

void Server::assignRequest(const Request &req) {
    currentRequest = req;
    busy = true;
    remainingTime = req.getProcessingTime();
}

void Server::processRequest() {
    if (busy) {
        remainingTime--;
        if (remainingTime <= 0) {
            busy = false;
        }
    }
}

bool Server::isIdle() const {
    return !busy;
}

void Server::printStatus() const {
    if (busy) {
        std::cout << name << " processing: " << currentRequest.getDescription()
                  << " (remaining time: " << remainingTime << ")\n";
    } else {
        std::cout << name << " is idle.\n";
    }
}
