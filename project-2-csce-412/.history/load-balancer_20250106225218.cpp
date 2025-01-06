#include "load-balancer.h"
#include <iostream>

// Constructor
LoadBalancer::LoadBalancer(int minServers, int maxServers)
    : minServers(minServers), maxServers(maxServers) {
    for (int i = 0; i < minServers; ++i) {
        servers.emplace_back("Server" + std::to_string(i));
    }
}

// Add a new request to the queue
void LoadBalancer::addRequest(const Request &req) {
    requestQueue.push(req);
}

// Adjust the number of active servers dynamically
void LoadBalancer::adjustServers() {
    int queueSize = requestQueue.size();
    int activeServers = servers.size();

    if (queueSize > activeServers * 10 && activeServers < maxServers) {
        servers.emplace_back("Server" + std::to_string(activeServers));
    } else if (queueSize < activeServers * 5 && activeServers > minServers) {
        servers.pop_back();
    }
}

// Run the simulation
void LoadBalancer::runSimulation(int timeLimit) {
    for (int time = 1; time <= timeLimit; ++time) {
        // Add new requests at random intervals
        if (rand() % 5 == 0) {
            addRequest(Request::generateRandomRequest());
        }

        // Assign requests to available servers
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

    // Process remaining requests
    while (!requestQueue.empty() || std::any_of(servers.begin(), servers.end(),
                                                [](const Server &server) { return server.isBusy(); })) {
        for (auto &server : servers) {
            if (!server.isBusy() && !requestQueue.empty()) {
                server.assignRequest(requestQueue.front());
                requestQueue.pop();
            }
            server.processRequest();
        }
        logStatus(++timeLimit);
    }

    std::cout << "Simulation finished at time = " << timeLimit << "\n";
    std::cout << "Remaining requests in queue: " << requestQueue.size() << "\n";
}

// Log the status of the load balancer
void LoadBalancer::logStatus(int currentTime) const {
    std::cout << "[Time= " << currentTime << "]\n";
    for (const auto &server : servers) {
        server.printStatus();
    }
    std::cout << "There are " << servers.size() << " servers running.\n";
}
