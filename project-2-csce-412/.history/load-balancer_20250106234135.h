/**
 * @file load-balancer.h
 * @brief Header file for the LoadBalancer class.
 */

#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <vector>
#include <queue>
#include <string>
#include "server.h"

/**
 * @class LoadBalancer
 * @brief Manages a collection of servers and a queue of requests.
 */
class LoadBalancer {
private:
    std::vector<Server> servers;        ///< List of servers managed by the load balancer.
    std::queue<Request> requestQueue;   ///< Queue of requests waiting to be processed.
    size_t runTime;                     ///< Total runtime of the simulation.
    size_t currentTime;                 ///< Current simulation time.

    /**
     * @brief Generates a random IP address.
     * @return Randomly generated IP address.
     */
    std::string randomIP() const;

    /**
     * @brief Generates a random job type ('S' or 'P').
     * @return Randomly generated job type.
     */
    char randomJobType() const;

    /**
     * @brief Generates a random request duration.
     * @return Randomly generated request duration.
     */
    size_t randomDuration() const;

public:
    /**
     * @brief Constructor for LoadBalancer.
     * @param numServers Number of servers to create.
     * @param timeToRun Total simulation time.
     */
    LoadBalancer(size_t numServers, size_t timeToRun);

    /**
     * @brief Initializes the request queue with a predefined number of requests.
     * @param numServers Number of servers in the load balancer.
     */
    void initializeQueue(size_t numServers);

    /**
     * @brief Runs the load balancer simulation.
     */
    void run();

    /**
     * @brief Prints the results of the simulation.
     */
    void printResults() const;
};

#endif