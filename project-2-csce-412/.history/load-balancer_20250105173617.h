#ifndef LOAD_BALANCER_H
#define LOAD_BALANCER_H

#include <vector>
#include <queue>
#include <tuple>
#include <string>
#include "server.h"

class LoadBalancer {
private:
    size_t totalTime;   // total time to run
    size_t currentTick; // current time step

    std::vector<Server> serverList;
    std::vector<std::tuple<Request, Server, size_t>> doneList;
    std::queue<Request> reqQueue;

    size_t rejectedCount; // how many we couldn't queue

    // Helpers
    size_t randomNum(size_t mini, size_t maxi);
    std::string makeRandomIP();
    void createRequests(size_t count, std::ostream &os = std::cout);
    void buildServers(size_t count, std::ostream &os = std::cout);

public:
    // Constructors, destructor
    LoadBalancer();
    LoadBalancer(size_t runTime, size_t numServers, size_t numRequests);
    LoadBalancer(const LoadBalancer &other);
    LoadBalancer(LoadBalancer &&other);
    ~LoadBalancer();

    // Operators
    LoadBalancer &operator=(const LoadBalancer &other);
    LoadBalancer &operator=(LoadBalancer &&other);

    // Core methods
    void giveRequest(Server &srv);
    void run(std::ostream &os = std::cout);
    void showLog(std::ostream &os = std::cout) const;
};

#endif // LOAD_BALANCER_H
