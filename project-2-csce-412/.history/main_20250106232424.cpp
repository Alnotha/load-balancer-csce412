/**
 * @file load-balancer.h
 * @brief Header file for the LoadBalancer class.
 * 
 * This class defines a load balancer that distributes requests across multiple servers
 * and manages request processing over a defined runtime.
 */

#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <vector>
#include <queue>
#include <string>
#include "server.h"

/**
 * @class LoadBalancer
 * @brief Simulates a load balancer with multiple servers handling requests.
 */
class LoadBalancer {
private:
    std::vector<Server> servers;        /**< List of servers managed by the load balancer. */
    std::queue<Request> requestQueue;   /**< Queue of requests waiting to be processed. */
    size_t runTime;                     /**< Maximum runtime for the simulation. */
    size_t currentTime;                 /**< Current simulation time (in ticks). */

    /**
     * @brief Generates a random IP address.
     * @return A string representing a random IP address in the format "X.X.X.X".
     */
    std::string randomIP() const;

    /**
     * @brief Generates a random job type.
     * @return A character representing the job type ('S' or 'P').
     */
    char randomJobType() const;

    /**
     * @brief Generates a random duration for a request.
     * @return A size_t representing the duration (in ticks).
     */
    size_t randomDuration() const;

public:
    /**
     * @brief Constructs a LoadBalancer with a specified number of servers and runtime.
     * @param numServers The number of servers in the system.
     * @param timeToRun The total simulation runtime (in ticks).
     */
    LoadBalancer(size_t numServers, size_t timeToRun);

    /**
     * @brief Initializes the request queue with a predefined number of requests.
     * @param numServers The number of servers to base the initial request count on.
     */
    void initializeQueue(size_t numServers);

    /**
     * @brief Runs the main simulation loop, processing requests and updating servers.
     */
    void run();

    /**
     * @brief Prints the results of the simulation, including remaining requests.
     */
    void printResults() const;
};

#endif

/**
 * @file main.cpp
 * @brief Entry point for the LoadBalancer simulation.
 * 
 * This program allows users to simulate a load balancer handling requests across multiple servers.
 */

#include <iostream>
#include <string>
#include "load-balancer.h"

/**
 * @brief Main function to run the LoadBalancer simulation.
 * 
 * Prompts the user for the number of servers and simulation runtime, then starts the simulation.
 * 
 * @return int Returns 0 upon successful execution.
 */
int main() {
    size_t numServers; /**< Number of servers in the load balancer. */
    size_t runTime;    /**< Duration for which the simulation will run. */

    std::cout << "Enter number of servers: ";
    std::cin >> numServers;
    std::cout << "Enter how long to run simulation: ";
    std::cin >> runTime;

    LoadBalancer lb(numServers, runTime); /**< Create a LoadBalancer instance. */
    lb.run();
    lb.printResults();

    return 0;
}
