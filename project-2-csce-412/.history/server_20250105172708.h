#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <iostream>
#include "request.h"

using std::string;
using std::ostream;
using std::cout;
using std::move;

// A basic Server class that tries to handle requests.
class Server {
private:
    // Just store server's label
    string srvName;

    // The request that the server is currently working on.
    Request currentReq;

    // Keep track of how long we've been at the current request.
    size_t currentTime;

    // Tells if the server is actually busy or not
    bool busy;

    // Tells if the server is allowed to take new requests
    bool enabled;

public:
    // default setup
    Server()
        : srvName(""), currentReq(), currentTime(0), busy(false), enabled(false) {
    }

    // make server with a name
    Server(const string &name)
        : srvName(name), currentReq(), currentTime(0), busy(false), enabled(false) {
    }

    // copy constructor
    Server(const Server &other)
        : srvName(other.srvName),
          currentReq(other.currentReq),
          currentTime(other.currentTime),
          busy(other.busy),
          enabled(other.enabled) {
    }

    // move constructor
    Server(Server &&other)
        : srvName(move(other.srvName)),
          currentReq(move(other.currentReq)),
          currentTime(other.currentTime),
          busy(other.busy),
          enabled(other.enabled) {
        other.currentTime = 0;
        other.busy = false;
        other.enabled = false;
    }

    ~Server() {}

    // copy assignment
    Server &operator=(const Server &other) {
        if (this != &other) {
            srvName = other.srvName;
            currentReq = other.currentReq;
            currentTime = other.currentTime;
            busy = other.busy;
            enabled = other.enabled;
        }
        return *this;
    }

    // move assignment
    Server &operator=(Server &&other) {
        if (this != &other) {
            srvName = move(other.srvName);
            currentReq = move(other.currentReq);
            currentTime = other.currentTime;
            busy = other.busy;
            enabled = other.enabled;

            other.currentTime = 0;
            other.busy = false;
            other.enabled = false;
        }
        return *this;
    }

    // set the request (by copy)
    void setRequest(const Request &req) {
        currentReq = req;
        currentTime = 0;
        busy = true;
    }

    // set the request (by move)
    void setRequest(Request &&req) {
        currentReq = move(req);
        currentTime = 0;
        busy = true;
    }

    // clear the request
    void clearRequest() {
        busy = false;
        currentTime = 0;
    }

    // if the load balancer says we are allowed to run
    void setEnabled(bool val) {
        enabled = val;
    }

    // handle the current request a little bit
    void handleRequest(ostream &os = cout) {
        os << *this << " working on " << currentReq << "\n";
        currentTime++;
        if (currentTime == currentReq.getDuration()) {
            busy = false;
        }
    }

    // get the request we are working on
    const Request &getRequest() const {
        return currentReq;
    }

    // are we busy?
    bool isBusy() const {
        return busy;
    }

    // are we allowed to run?
    bool isEnabled() const {
        return enabled;
    }

    // just print out server name
    friend ostream &operator<<(ostream &os, const Server &server) {
        os << "Server{" << server.srvName << "}";
        return os;
    }
};

#endif // SERVER_H
