#include "load-balancer.h"
#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>

LoadBalancer::LoadBalancer(int minServers, int maxServers)
    : minServers(minServers), maxServers(maxServers), activeServers(minServers) {
    for (int i = 0; i < minServers; ++i) {
        servers.emplace_back("Server" + std::to_string(i));
    }
}

void LoadBalancer::addRequest(const Request &req) {
    requestQueue.push(req);
}

void LoadBalancer::adjustServers() {
    int queueSize = requestQueue.size();

    // Scale up if the queue is growing and there are not enough active servers
    if (queueSize > activeServers * 2 && activeServers < maxServers) {
        servers.emplace_back("Server" + std::to_string(activeServers));
        activeServers++;
    }

    // Scale down if servers are idle and active servers exceed minimum
    int idleServers = 0;
    for (const auto &server : servers) {
        if (server.isIdle()) {
            idleServers++;
        }
    }

    if (idleServers > 1 && activeServers > minServers) {
        servers.pop_back();
        activeServers--;
    }
}

void LoadBalancer::runSimulation(int timeLimit) {
    int time = 0;

    while (time < timeLimit || !requestQueue.empty()) {
        // Add a random request every 5 time units
        if (time % 5 == 0) {
            Request newReq = Request::generateRandomRequest();
            addRequest(newReq);
            std::cout << "[Time= " << time << "] New request arrives: " 
                      << newReq.getDescription() << "\n";
        }

        // Process requests
        for (auto &server : servers) {
            if (server.isIdle() && !requestQueue.empty()) {
                server.assignRequest(requestQueue.front());
                requestQueue.pop();
            }
            server.processRequest();
        }

        // Adjust the number of active servers
        adjustServers();

        // Print status
        std::cout << "[Time= " << time << "]\n";
        for (size_t i = 0; i < servers.size(); ++i) {
            servers[i].printStatus();
        }
        std::cout << "There are " << activeServers << " servers running.\n";

        time++;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    std::cout << "Simulation finished at time = " << time << "\n";
    std::cout << "Remaining requests in queue: " << requestQueue.size() << "\n";
}
