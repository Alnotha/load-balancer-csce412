/**
 * @file server.h
 * @brief Header file for the Server class.
 */

#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string>
#include "request.h"

/**
 * @class Server
 * @brief Represents a server that processes requests.
 */
class Server {
private:
    std::string serverName; ///< Name of the server.
    Request currentReq;     ///< The current request being processed.
    bool busy;              ///< Indicates whether the server is busy.
    size_t timeSpent;       ///< Time spent on the current request.

public:
    /**
     * @brief Constructs a Server with a given name.
     * @param name Name of the server.
     */
    Server(const std::string &name);

    /**
     * @brief Checks if the server is busy.
     * @return True if the server is busy, otherwise false.
     */
    bool isBusy() const;

    /**
     * @brief Assigns a new request to the server.
     * @param r Request to process.
     */
    void setRequest(const Request &r);

    /**
     * @brief Processes the current request for one time step.
     */
    void handleRequest();

    /**
     * @brief Retrieves the name of the server.
     * @return Name of the server.
     */
    const std::string& getName() const;

    /**
     * @brief Checks if the server has finished processing the current request.
     * @return True if the request is finished, otherwise false.
     */
    bool hasRequestFinished() const;

    /**
     * @brief Retrieves the current request being processed.
     * @return Current request.
     */
    const Request& getCurrentRequest() const;

    /**
     * @brief Clears the current request after completion.
     */
    void clearCurrentRequest();
};

#endif