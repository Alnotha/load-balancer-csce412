#ifndef SERVER_H
#define SERVER_H

#include <string>
#include "request.h"

class Server {
private:
    std::string name;
    bool busy;
    int remainingTime;
    Request currentRequest;

public:
    Server(const std::string &name);

    void assignRequest(const Request &req);
    void processRequest();
    bool isIdle() const; // Added isIdle method
    void printStatus() const;
};

#endif // SERVER_H
