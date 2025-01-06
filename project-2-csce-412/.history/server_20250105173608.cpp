#include "server.h"
#include <utility> // for std::move

Server::Server()
    : srvName(""), currentReq(), currentTime(0), busy(false), enabled(false) {}

Server::Server(const std::string &name)
    : srvName(name), currentReq(), currentTime(0), busy(false), enabled(false) {}

Server::Server(const Server &other)
    : srvName(other.srvName),
      currentReq(other.currentReq),
      currentTime(other.currentTime),
      busy(other.busy),
      enabled(other.enabled) {}

Server::Server(Server &&other)
    : srvName(std::move(other.srvName)),
      currentReq(std::move(other.currentReq)),
      currentTime(other.currentTime),
      busy(other.busy),
      enabled(other.enabled)
{
    other.currentTime = 0;
    other.busy        = false;
    other.enabled     = false;
}

Server::~Server() {}

Server &Server::operator=(const Server &other) {
    if (this != &other) {
        srvName     = other.srvName;
        currentReq  = other.currentReq;
        currentTime = other.currentTime;
        busy        = other.busy;
        enabled     = other.enabled;
    }
    return *this;
}

Server &Server::operator=(Server &&other) {
    if (this != &other) {
        srvName     = std::move(other.srvName);
        currentReq  = std::move(other.currentReq);
        currentTime = other.currentTime;
        busy        = other.busy;
        enabled     = other.enabled;

        other.currentTime = 0;
        other.busy        = false;
        other.enabled     = false;
    }
    return *this;
}

void Server::setRequest(const Request &req) {
    currentReq  = req;
    currentTime = 0;
    busy        = true;
}

void Server::setRequest(Request &&req) {
    currentReq  = std::move(req);
    currentTime = 0;
    busy        = true;
}

void Server::clearRequest() {
    busy        = false;
    currentTime = 0;
}

void Server::setEnabled(bool val) {
    enabled = val;
}

void Server::handleRequest(std::ostream &os) {
    os << *this << " working on " << currentReq << "\n";
    currentTime++;
    if (currentTime == currentReq.getDuration()) {
        busy = false;
    }
}

const Request &Server::getRequest() const {
    return currentReq;
}

bool Server::isBusy() const {
    return busy;
}

bool Server::isEnabled() const {
    return enabled;
}

std::ostream &operator<<(std::ostream &os, const Server &server) {
    os << "Server{" << server.srvName << "}";
    return os;
}
