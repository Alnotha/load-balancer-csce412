#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <vector>
#include <queue>
#include <string>
#include "server.h"

class LoadBalancer {
private:
    std::vector<Server> servers;        //servers
    std::queue<Request> requestQueue;   //queue of requests which are waititng
    size_t runTime;                     //run time attempt
    size_t currentTime;                 //clock (tick time)

    // Helpers
    std::string randomIP() const;
    char randomJobType() const;
    size_t randomDuration() const;

public:
    // Create the load balancer with N servers, and fill initial queue
    LoadBalancer(size_t numServers, size_t timeToRun);

    // Setup initial queue with (numServers * 20) requests
    void initializeQueue(size_t numServers);

    // Main simulation
    void run();

    // Show final results
    void printResults() const;
};

#endif
