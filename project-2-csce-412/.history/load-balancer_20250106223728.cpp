#include "load-balancer.h"
#include <iostream>
#include <cstdlib>   // for rand() val gen
#include <ctime>     // for time() value 
using namespace std;
\

LoadBalancer::LoadBalancer(int minServers, int maxServers, int timeLimit) 
    : minServers(minServers), maxServers(maxServers), timeLimit(timeLimit) {
    for (int i = 0; i < minServers; ++i) {
        servers.emplace_back(Server());
    }
}

void LoadBalancer::addRequest(const Request& req) {
    requestQueue.push(req);
}

void LoadBalancer::adjustServers() {
    int queueSize = requestQueue.size();
    int activeServers = servers.size();

    if (queueSize > activeServers * 10 && activeServers < maxServers) {
        servers.emplace_back(Server());
        std::cout << "Added a server. Total servers: " << servers.size() << "\n";
    } else if (queueSize < activeServers * 5 && activeServers > minServers) {
        servers.pop_back();
        std::cout << "Removed a server. Total servers: " << servers.size() << "\n";
    }
}

void LoadBalancer::runSimulation() {
    for (int time = 0; time < timeLimit; ++time) {
        // Add new requests randomly
        if (std::rand() % 5 == 0) {
            Request newRequest("RandomIP_In", "RandomIP_Out", std::rand() % 15 + 1, (std::rand() % 2) ? 'S' : 'P');
            addRequest(newRequest);
            std::cout << "Added new request at time " << time << "\n";
        }

        // Assign requests to servers
        for (auto& server : servers) {
            if (!server.isBusy() && !requestQueue.empty()) {
                server.assignRequest(requestQueue.front());
                requestQueue.pop();
            }
            server.processRequest();
        }

        // Adjust servers dynamically
        adjustServers();

        // Log status
        logStatus(time);
    }

    std::cout << "Simulation finished. Remaining requests in queue: " << requestQueue.size() << "\n";
}

void LoadBalancer::logStatus(int currentTime) const {
    std::cout << "[Time= " << currentTime << "] \n";
    std::cout << "Active servers: " << servers.size() << "\n";
    std::cout << "Requests in queue: " << requestQueue.size() << "\n";
}
