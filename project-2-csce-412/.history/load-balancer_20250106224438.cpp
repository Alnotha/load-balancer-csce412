#include "load-balancer.h"
#include <iostream>

// Constructor
LoadBalancer::LoadBalancer(int minServers, int maxServers)
    : minServers(minServers), maxServers(maxServers), activeServers(minServers) {
    for (int i = 0; i < minServers; ++i) {
        servers.emplace_back(Server("Server" + std::to_string(i)));
    }
}

// Add request to queue
void LoadBalancer::addRequest(const Request &req) {
    requestQueue.push(req);
}

// Adjust servers dynamically
void LoadBalancer::adjustServers() {
    int queueSize = requestQueue.size();
    if (queueSize > activeServers * 10 && activeServers < maxServers) {
        servers.emplace_back(Server("Server" + std::to_string(activeServers)));
        ++activeServers;
    } else if (queueSize < activeServers * 5 && activeServers > minServers) {
        servers.pop_back();
        --activeServers;
    }
}

// Run simulation
void LoadBalancer::runSimulation(int timeLimit) {
    for (int time = 1; time <= timeLimit || !requestQueue.empty(); ++time) {
        if (time <= timeLimit) {
            Request newReq = Request::generateRandomRequest();
            addRequest(newReq);
        }
        for (auto &server : servers) {
            if (!server.isBusy() && !requestQueue.empty()) {
                server.assignRequest(requestQueue.front());
                requestQueue.pop();
            }
            server.processRequest();
        }
        adjustServers();
        logStatus(time);
    }
    std::cout << "Simulation finished. Remaining requests in queue: " << requestQueue.size() << std::endl;
}

// Log system status
void LoadBalancer::logStatus(int currentTime) const {
    std::cout << "[Time= " << currentTime << "]\n";
    for (const auto &server : servers) {
        server.printStatus();
    }
    std::cout << "There are " << activeServers << " servers running.\n";
}
