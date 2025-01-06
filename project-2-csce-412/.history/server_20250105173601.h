#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <iostream>
#include "request.h"

class Server {
private:
    std::string srvName;    // Server's name
    Request currentReq;     // Current request the server is processing
    size_t currentTime;     // Time spent on the current request
    bool busy;              // Whether the server is busy or idle
    bool enabled;           // Whether the server can accept requests

public:
    // Constructors, destructor
    Server();
    Server(const std::string &name);
    Server(const Server &other);
    Server(Server &&other);
    ~Server();

    // Operators
    Server &operator=(const Server &other);
    Server &operator=(Server &&other);

    // Request-related
    void setRequest(const Request &req);
    void setRequest(Request &&req);
    void clearRequest();

    // Server state
    void setEnabled(bool val);
    void handleRequest(std::ostream &os = std::cout);
    const Request &getRequest() const;

    // Check server status
    bool isBusy() const;
    bool isEnabled() const;

    friend std::ostream &operator<<(std::ostream &os, const Server &server);
};

#endif // SERVER_H
