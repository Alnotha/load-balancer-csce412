/**
 * @file load-balancer.cpp
 * @brief Implementation of the LoadBalancer class.
 * 
 * This class simulates a load balancer that distributes requests across multiple servers.
 * It handles request initialization, server management, and random request generation.
 */

#include "load-balancer.h"
#include <iostream>
#include <cstdlib>   // for rand() value generation
#include <ctime>     // for time() value
using namespace std;

/**
 * @brief Constructor for the LoadBalancer class.
 * @param numServers The number of servers in the system.
 * @param timeToRun The total time the simulation should run.
 */
LoadBalancer::LoadBalancer(size_t numServers, size_t timeToRun) : runTime(timeToRun), currentTime(0) {
    // Building servers
    for (size_t i = 0; i < numServers; i++) {
        servers.emplace_back("Server" + to_string(i));
    }

    // Seed randomness for better variability
    srand((unsigned)time(nullptr));

    // Fill initial requests
    initializeQueue(numServers);
}

/**
 * @brief Initializes the request queue with a predefined number of requests.
 * @param numServers The number of servers to base the initial request count on.
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
 * @return A string representing a random IP address in the format "X.X.X.X".
 */
string LoadBalancer::randomIP() const {
    return to_string(1 + rand() % 255) + "." +
           to_string(1 + rand() % 255) + "." +
           to_string(1 + rand() % 255) + "." +
           to_string(1 + rand() % 255);
}

/**
 * @brief Generates a random job type.
 * @return A character representing the job type ('S' or 'P').
 */
char LoadBalancer::randomJobType() const {
    return (rand() % 2 == 0) ? 'S' : 'P';
}

/**
 * @brief Generates a random request duration.
 * @return A size_t representing the duration of the request (between 3 and 16 cycles).
 */
size_t LoadBalancer::randomDuration() const {
    return 3 + (rand() % 14);
}

/**
 * @brief Runs the simulation until the specified runtime or all requests are processed.
 */
void LoadBalancer::run() {
    while (true) {
        currentTime++;
        cout << "[Time= " << currentTime << "]\n";

        // Let each server handle its current request for 1 tick
        for (auto &srv : servers) {
            srv.handleRequest();
        }

        // Check for finished requests and assign new ones if available
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

        // Randomly add new requests to the queue
        if (rand() % 20 == 0) {
            int howMany = 1 + (rand() % 3);
            for (int i = 0; i < howMany; i++) {
                Request r(randomIP(), randomIP(), randomDuration(), randomJobType());
                requestQueue.push(r);
                cout << "new request arrives: " << r << "\n";
            }
        }

        // Stop if the runtime limit is reached
        if (currentTime >= runTime) {
            cout << "Reached max runtime (" << runTime << "). Stopping. \n";
            break;
        }

        // Debugging active and idle servers
        size_t activeServers = 0;
        size_t idleServers = 0;

        for (const auto &srv : servers) {
            if (srv.isBusy()) {
                activeServers++;
            } else {
                idleServers++;
            }
        }
        printf("Servers Running: %lu\n", servers.size());
        printf("Active servers: %lu\n", activeServers);
        printf("Idle servers: %lu\n", idleServers);
    }
}

/**
 * @brief Prints the results of the simulation, including remaining requests.
 */
void LoadBalancer::printResults() const {
    cout << "Simulation finished at time = " << currentTime << "\n";
    cout << "Remaining requests in queue: " << requestQueue.size() << "\n";
}
