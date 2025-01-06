#ifndef LOAD_BALANCER_H
#define LOAD_BALANCER_H

#include "server.h"
#include "request.h"
#include <vector>
#include <queue>

class LoadBalancer {
private:
    std::vector<Server> servers;
    std::queue<Request> requestQueue;
    int minServers;
    int maxServers;

public:
    LoadBalancer(int minServers, int maxServers);

    void addRequest(const Request &req);
    void adjustServers();
    void runSimulation(int timeLimit);
    void logStatus(int currentTime) const;
};

#endif // LOAD_BALANCER_H
