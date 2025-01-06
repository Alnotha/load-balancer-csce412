#include "server.h"

Server::Server(const std::string &name)
    : serverName(name), busy(false), timeSpent(0) {
    // currentReq is default-constructed
}

bool Server::isBusy() const {
    return busy;
}

void Server::setRequest(const Request &r) {
    currentReq = r;
    busy = true;
    timeSpent = 0;
}

void Server::handleRequest() {
    // If busy, increment timeSpent
    if (busy) {
        timeSpent++;

        // If we've reached the needed duration, mark done
        if (timeSpent >= currentReq.getDuration()) {
            busy = false;
        }
    }
}

bool Server::hasRequestFinished() const {
    return (!busy && currentReq.getDuration() != 0);
}

void Server::clearCurrentRequest() {
    currentReq = Request();
    timeSpent = 0;
}

const Request& Server::getCurrentRequest() const {
    return currentReq;
}

const std::string& Server::getName() const {
    return serverName;
}
