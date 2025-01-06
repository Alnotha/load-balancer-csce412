#include "load-balancer.h"
#include <iostream>
#include <cstdlib>   // for rand() val gen
#include <ctime>     // for time() value 
using namespace std;

LoadBalancer::LoadBalancer(size_t numServers, size_t timeToRun) : runTime(timeToRun), currentTime(0){
    
    //building servers
    for (size_t i = 0; i < numServers; i++){
        servers.emplace_back("Server" + to_string(i));
    }

    //seed randomness - more randomeness this way
    //srand(0);
    srand((unsigned)time(nullptr));

    // fill initial requests
    initializeQueue(numServers);
}

void LoadBalancer::initializeQueue(size_t numServers){
    size_t initialRequests = numServers * 20;
    for (size_t i = 0; i < initialRequests; i++){
        Request req(randomIP(), randomIP(), randomDuration(), randomJobType());
        requestQueue.push(req);
    }
}
string LoadBalancer::randomIP() const{
    // ex. "192.168.0.10"
    // range from 1-256 for each num
    return to_string(1 + rand() % 255) + "." +
           to_string(1 + rand() % 255) + "." +
           to_string(1 + rand() % 255) + "." +
           to_string(1 + rand() % 255);
}

char LoadBalancer::randomJobType() const{
    // return 'S' or 'P'
    if (rand() % 2 == 0) {
        return 'S';
    } else {
        return 'P';
    }
}

size_t LoadBalancer::randomDuration() const{
    //ex. 3 cycles - 16 cycles
    return 3 + (rand() % 14);
    //rand 0, leaves @ 3
}
void LoadBalancer::run() {
    while (true) {
        currentTime++;
        cout << "[Time= " << currentTime << "] \n";

        // Let each server handle its current request for 1 tick
        for (auto &srv : servers) {
            srv.handleRequest();
        }

        // Check if any server finished, if so, get the next in queue
        for (auto &srv : servers) {
            if (srv.hasRequestFinished()) {
                cout << srv.getName() << " finished: "
                     << srv.getCurrentRequest() << "\n";
                srv.clearCurrentRequest();

                // If another request is waiting, assign it
                if (!requestQueue.empty()) {
                    Request next = requestQueue.front();
                    requestQueue.pop();
                    srv.setRequest(next);
                    cout << srv.getName() << " started: " << next << "\n";
                }
            } else if (!srv.isBusy() && !requestQueue.empty()) {
                Request next = requestQueue.front();
                requestQueue.pop();
                srv.setRequest(next);
                cout << srv.getName() << " started: " << next << "\n";
            }
        }

        // Dynamically scale servers based on the request queue size
        if (requestQueue.size() > servers.size()) {
            // Add new servers if the queue grows significantly
            size_t newServers = (requestQueue.size() / 2) - servers.size();
            for (size_t i = 0; i < newServers; i++) {
                servers.emplace_back("Server" + to_string(servers.size()));
                cout << "Added new server: Server" + to_string(servers.size() - 1) << "\n";
            }
        } else if (requestQueue.empty() && servers.size() > 1) {
            // Remove idle servers if the queue is empty
            size_t activeServers = 0;
            for (const auto &srv : servers) {
                if (srv.isBusy()) {
                    activeServers++;
                }
            }
            if (activeServers < servers.size()) {
                servers.pop_back();
                cout << "Removed a server. Total servers: " << servers.size() << "\n";
            }
        }

        // Extra requests: At random intervals, add a new request
        if (rand() % 20 == 0) {
            int howMany = 1 + (rand() % 3);
            for (int i = 0; i < howMany; i++) {
                Request r(randomIP(), randomIP(), randomDuration(), randomJobType());
                requestQueue.push(r);
                cout << "New request arrives: " << r << "\n";
            }
        }

        // Stop if all servers are idle and the queue is empty
        bool allIdle = true;
        for (const auto &srv : servers) {
            if (srv.isBusy()) {
                allIdle = false;
                break;
            }
        }
        if (allIdle && requestQueue.empty()) {
            cout << "All requests completed early. Stopping...\n";
            break;
        }

        // Stop if reached the runtime limit
        if (currentTime >= runTime) {
            cout << "Reached max runtime (" << runTime << "). Stopping.\n";
            break;
        }

        // Print the number of running servers
        cout << "There are " << servers.size() << " servers running.\n\n";
    }
}


void LoadBalancer::printResults() const{
    cout << "Simulation finished at time = " << currentTime << "\n";
    cout << "Remaining requests in queue: " << requestQueue.size() << "\n";
}
