#include "load-balancer.h"
#include <iostream>
#include <random>
#include <string>

// Constructor for LoadBalancer
LoadBalancer::LoadBalancer(int minServers, int maxServers, int timeLimit)
    : minServers_(minServers), maxServers_(maxServers), timeLimit_(timeLimit) {
    for (int i = 0; i < minServers_; ++i) {
        servers.emplace_back(Server("Server" + std::to_string(i)));
    }
}

// Add a request to the queue
void LoadBalancer::addRequest(const Request& req) {
    requestQueue.push(req);
}

// Adjust the number of active servers dynamically
void LoadBalancer::adjustServers() {
    int queueSize = requestQueue.size();
    int activeServers = servers.size();

    if (queueSize > activeServers * 10 && activeServers < maxServers_) {
        servers.emplace_back(Server("Server" + std::to_string(servers.size())));
        std::cout << "Added a server. Total servers: " << servers.size() << std::endl;
    } else if (queueSize < activeServers * 5 && activeServers > minServers_) {
        servers.pop_back();
        std::cout << "Removed a server. Total servers: " << servers.size() << std::endl;
    }
}

// Run the load balancer simulation
void LoadBalancer::runSimulation() {
    for (int time = 0; time < timeLimit_; ++time) {
        // Simulate incoming requests
        if (rand() % 2 == 0) {
            Request newRequest(generateRandomIP(), generateRandomIP(), rand() % 15 + 1, rand() % 2 == 0 ? 'S' : 'P');
            addRequest(newRequest);
        }

        // Assign requests to servers
        for (auto& server : servers) {
            if (!requestQueue.empty() && !server.isBusy()) {
                server.assignRequest(requestQueue.front());
                requestQueue.pop();
            }
            server.processRequest();
        }

        // Adjust the number of servers
        adjustServers();

        // Log the status
        logStatus(time);
    }

    // Ensure all requests are processed
    while (!requestQueue.empty()) {
        for (auto& server : servers) {
            if (!requestQueue.empty() && !server.isBusy()) {
                server.assignRequest(requestQueue.front());
                requestQueue.pop();
            }
            server.processRequest();
        }
        adjustServers();
    }

    std::cout << "Simulation complete." << std::endl;
}

// Log the current status of the load balancer
void LoadBalancer::logStatus(int currentTime) const {
    std::cout << "[Time=" << currentTime << "] ";
    std::cout << "Queue size: " << requestQueue.size() << " ";
    std::cout << "Active servers: " << servers.size() << std::endl;
}

// Generate a random IP address
std::string LoadBalancer::generateRandomIP() {
    return std::to_string(rand() % 256) + "." + std::to_string(rand() % 256) + "." +
           std::to_string(rand() % 256) + "." + std::to_string(rand() % 256);
}
