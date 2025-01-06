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
    int activeServers;
    std::queue<Request> requestQueue;
    std::vector<Server> servers;

public:
    LoadBalancer(int minServers, int maxServers);

    void addRequest(const Request &req);
    void adjustServers();
    void runSimulation(int timeLimit);
    void logStatus(int currentTime) const;
};

#endif // LOAD_BALANCER_H
