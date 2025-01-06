
/**
 * @file server.cpp
 * @brief Implementation of the Server class.
 */

#include "server.h"

/**
 * @brief Constructs a Server with a given name.
 * @param name Name of the server.
 */
Server::Server(const std::string &name)
    : serverName(name), busy(false), timeSpent(0) {}

/**
 * @brief Checks if the server is busy.
 * @return True if the server is busy, otherwise false.
 */
bool Server::isBusy() const {
    return busy;
}

/**
 * @brief Assigns a new request to the server.
 * @param r Request to process.
 */
void Server::setRequest(const Request &r) {
    currentReq = r;
    busy = true;
    timeSpent = 0;
}

/**
 * @brief Processes the current request for one time step.
 */
void Server::handleRequest() {
    if (busy) {
        timeSpent++;
        if (timeSpent >= currentReq.getDuration()) {
            busy = false;
        }
    }
}

/**
 * @brief Checks if the server has finished processing the current request.
 * @return True if the request is finished, otherwise false.
 */
bool Server::hasRequestFinished() const {
    return (!busy && currentReq.getDuration() != 0);
}

/**
 * @brief Clears the current request after completion.
 */
void Server::clearCurrentRequest() {
    currentReq = Request();
    timeSpent = 0;
}

/**
 * @brief Retrieves the current request being processed.
 * @return Current request.
 */
const Request& Server::getCurrentRequest() const {
    return currentReq;
}

/**
 * @brief Retrieves the name of the server.
 * @return Name of the server.
 */
const std::string& Server::getName() const {
    return serverName;
}
