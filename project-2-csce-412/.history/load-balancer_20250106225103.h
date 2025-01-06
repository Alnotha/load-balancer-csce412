#ifndef LOAD_BALANCER_H
#define LOAD_BALANCER_H

#include <queue>
#include <vector>
#include "server.h"
#include "request.h"

class LoadBalancer {
private:
    int minServers;
    int maxServers;
    int activeServers; // Tracks the current number of active servers
    std::vector<Server> servers;
    std::queue<Request> requestQueue;

public:
    LoadBalancer(int minServers, int maxServers);

    void addRequest(const Request &req);
    void adjustServers();
    void runSimulation(int timeLimit);
};

#endif // LOAD_BALANCER_H
