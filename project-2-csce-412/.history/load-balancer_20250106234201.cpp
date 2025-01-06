/**
 * @file load-balancer.cpp
 * @brief Implementation of the LoadBalancer class.
 */

#include "load-balancer.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

/**
 * @brief Constructs a LoadBalancer with a given number of servers and runtime.
 * @param numServers Number of servers to manage.
 * @param timeToRun Maximum runtime for the simulation.
 */
LoadBalancer::LoadBalancer(size_t numServers, size_t timeToRun)
    : runTime(timeToRun), currentTime(0) {
    for (size_t i = 0; i < numServers; i++) {
        servers.emplace_back("Server" + to_string(i));
    }
    srand((unsigned)time(nullptr));
    initializeQueue(numServers);
}

/**
 * @brief Populates the request queue with an initial set of requests.
 * @param numServers Number of servers in the system.
 */
void LoadBalancer::initializeQueue(size_t numServers) {
    size_t initialRequests = numServers * 20;
    for (size_t i = 0; i < initialRequests; i++) {
        Request req(randomIP(), randomIP(), randomDuration(), randomJobType());
        requestQueue.push(req);
    }
}

/**
 * @brief Generates a random IP address.
 * @return A randomly generated IP address.
 */
string LoadBalancer::randomIP() const {
    return to_string(1 + rand() % 255) + "." +
           to_string(1 + rand() % 255) + "." +
           to_string(1 + rand() % 255) + "." +
           to_string(1 + rand() % 255);
}

/**
 * @brief Generates a random job type ('S' or 'P').
 * @return A random job type.
 */
char LoadBalancer::randomJobType() const {
    return rand() % 2 == 0 ? 'S' : 'P';
}

/**
 * @brief Generates a random duration for a request.
 * @return A random duration value.
 */
size_t LoadBalancer::randomDuration() const {
    return 3 + (rand() % 14);
}

/**
 * @brief Runs the load balancer simulation.
 */
void LoadBalancer::run() {
    while (true) {
        currentTime++;
        cout << "[Time= " << currentTime << "] \n";

        for (auto &srv : servers) {
            srv.handleRequest();
        }

        for (auto &srv : servers) {
            if (srv.hasRequestFinished()) {
                cout << srv.getName() << " finished: "
                     << srv.getCurrentRequest() << "\n";
                srv.clearCurrentRequest();

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
                cout << srv.getName() << " started: " << next << " \n";
            }
        }

        if (rand() % 20 == 0) {
            int howMany = 1 + (rand() % 3);
            for (int i = 0; i < howMany; i++) {
                Request r(randomIP(), randomIP(), randomDuration(), randomJobType());
                requestQueue.push(r);
                cout << "new request arrives: " << r << "\n";
            }
        }

        if (currentTime >= runTime) {
            cout << "Reached max runtime (" << runTime << "). Stopping. \n";
            break;
        }
        cout << "\n";
    }
}

/**
 * @brief Prints the results of the simulation.
 */
void LoadBalancer::printResults() const {
    cout << "Simulation finished at time = " << currentTime << "\n";
    cout << "Remaining requests in queue: " << requestQueue.size() << "\n";
}
