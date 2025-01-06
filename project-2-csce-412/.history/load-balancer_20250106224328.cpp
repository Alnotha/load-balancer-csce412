#include "load-balancer.h"
#include <iostream>
#include <algorithm>

LoadBalancer::LoadBalancer(int minServers, int maxServers)
    : minServers(minServers), maxServers(maxServers) {
    for (int i = 0; i < minServers; ++i) {
        servers.emplace_back(Server("Server" + std::to_string(i)));
    }
}

void LoadBalancer::addRequest(const Request &req) {
    requestQueue.push(req);
}

void LoadBalancer::adjustServers() {
    size_t activeServers = servers.size();
    size_t queueSize = requestQueue.size();

    // Scale up if queue is large and not at maxServers
    if (queueSize > activeServers * 10 && activeServers < maxServers) {
        servers.emplace_back(Server("Server" + std::to_string(servers.size())));
        std::cout << "[Scaling Up] Added new server. Total servers: " << servers.size() << "\n";
    }

    // Scale down if queue is small and above minServers
    if (queueSize < activeServers * 5 && activeServers > minServers) {
        servers.pop_back();
        std::cout << "[Scaling Down] Removed a server. Total servers: " << servers.size() << "\n";
    }
}

void LoadBalancer::runSimulation(int timeLimit) {
    int time = 0;

    while (!requestQueue.empty() || std::any_of(servers.begin(), servers.end(), [](const Server &s) { return s.isBusy(); })) {
        ++time;

        // Add new requests dynamically (example: every 5 ticks)
        if (time % 5 == 0) {
            Request newReq = Request::generateRandomRequest();
            addRequest(newReq);
            std::cout << "[Time=" << time << "] New request added: " << newReq << "\n";
        }

        // Process requests in servers
        for (auto &server : servers) {
            if (!server.isBusy() && !requestQueue.empty()) {
                server.setRequest(requestQueue.front());
                requestQueue.pop();
                std::cout << "[Time=" << time << "] " << server.getName() << " started: " << server.getCurrentRequest() << "\n";
            }
            server.handleRequest();

            if (server.hasRequestFinished()) {
                std::cout << "[Time=" << time << "] " << server.getName() << " finished: " << server.getCurrentRequest() << "\n";
                server.clearCurrentRequest();
            }
        }

        // Adjust servers dynamically
        adjustServers();

        // Log status
        logStatus(time);

        if (time == timeLimit) {
            std::cout << "Reached max runtime (" << timeLimit << "). Stopping.\n";
            break;
        }
    }

    std::cout << "Simulation finished at time = " << time << "\nRemaining requests in queue: " << requestQueue.size() << "\n";
}

void LoadBalancer::logStatus(int currentTime) const {
    std::cout << "[Time=" << currentTime << "]\n";
    std::cout << "There are " << servers.size() << " servers running.\n";
}
