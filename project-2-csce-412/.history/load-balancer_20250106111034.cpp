#include "load-balancer.h"
#include <iostream>
#include <cstdlib>   // for rand(
#include <ctime>     // for time()

LoadBalancer::LoadBalancer(size_t numServers, size_t timeToRun)
    : runTime(timeToRun), currentTime(0)
{
    // build servers
    for (size_t i = 0; i < numServers; i++) {
        servers.emplace_back("Server" + std::to_string(i));
    }

    // seed randomness
    std::srand((unsigned)std::time(nullptr));

    // fill initial requests
    initializeQueue(numServers);
}

void LoadBalancer::initializeQueue(size_t numServers) {
    size_t initialRequests = numServers * 20;
    for (size_t i = 0; i < initialRequests; i++) {
        Request req(randomIP(), randomIP(), randomDuration(), randomJobType());
        requestQueue.push(req);
    }
}

std::string LoadBalancer::randomIP() const {
    // e.g. "192.168.0.10"
    // range from 1..255 for each octet
    return std::to_string(1 + std::rand() % 255) + "." +
           std::to_string(std::rand() % 256) + "." +
           std::to_string(std::rand() % 256) + "." +
           std::to_string(1 + std::rand() % 255);
}

char LoadBalancer::randomJobType() const {
    // return 'S' or 'P'
    return (std::rand() % 2 == 0) ? 'S' : 'P';
}

size_t LoadBalancer::randomDuration() const {
    // e.g. 3..16
    return 3 + (std::rand() % 14);
}

void LoadBalancer::run() {
    // We'll run the clock until we either exceed runTime
    // or everything finishes (empty queue & all servers idle).
    while (true) {
        currentTime++;
        std::cout << "[Time=" << currentTime << "]\n";

        // Let each server handle its current request for 1 tick
        for (auto &srv : servers) {
            srv.handleRequest();
        }

        // Check if any server finished; if so, get next in queue
        for (auto &srv : servers) {
            if (srv.hasRequestFinished()) {
                std::cout << srv.getName() << " finished: " 
                          << srv.getCurrentRequest() << "\n";
                srv.clearCurrentRequest();

                // If there's another request waiting, assign it
                if (!requestQueue.empty()) {
                    Request next = requestQueue.front();
                    requestQueue.pop();
                    srv.setRequest(next);
                    std::cout << srv.getName() << " started: " << next << "\n";
                }
            }
            // If server is idle but queue not empty, give it a request
            else if (!srv.isBusy() && !requestQueue.empty()) {
                Request next = requestQueue.front();
                requestQueue.pop();
                srv.setRequest(next);
                std::cout << srv.getName() << " started: " << next << "\n";
            }
        }

        // Optionally, at random intervals, add a new request
        if (std::rand() % 20 == 0) {
            // 1 in 20 chance each tick to add 1..3 new requests
            int howMany = 1 + (std::rand() % 3);
            for (int i = 0; i < howMany; i++) {
                Request r(randomIP(), randomIP(), randomDuration(), randomJobType());
                requestQueue.push(r);
                std::cout << "New request arrives: " << r << "\n";
            }
        }

        // If all servers are idle and queue is empty, we can stop
        bool allIdle = true;
        for (auto &srv : servers) {
            if (srv.isBusy()) {
                allIdle = false;
                break;
            }
        }
        if (allIdle && requestQueue.empty()) {
            std::cout << "All requests completed early. Stopping.\n";
            break;
        }

        // If we reached the runTime limit, also stop
        if (currentTime >= runTime) {
            std::cout << "Reached max runtime (" << runTime << "). Stopping.\n";
            break;
        }

        std::cout << "\n";
    }
}

void LoadBalancer::printResults() const {
    std::cout << "Simulation finished at time = " << currentTime << "\n";
    std::cout << "Remaining requests in queue: " << requestQueue.size() << "\n";
    // If any servers are still busy, you could also report that here if desired
}
