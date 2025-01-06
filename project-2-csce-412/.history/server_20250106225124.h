#ifndef SERVER_H
#define SERVER_H

#include "request.h"
#include <string>

class Server {
private:
    std::string name;
    Request currentRequest;
    bool busy;
    int remainingTime;

public:
    Server(const std::string &name);

    void assignRequest(const Request &req);
    void processRequest();
    bool isBusy() const;
    void printStatus() const;
};

#endif // SERVER_H
