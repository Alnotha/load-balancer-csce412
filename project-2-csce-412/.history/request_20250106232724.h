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

/**
 * @file request.cpp
 * @brief Implementation of the Request class.
 * 
 * This file defines the Request class, which represents a network request
 * in the load balancer simulation.
 */

#include "request.h"

/**
 * @brief Constructs a Request with specified parameters.
 * @param in Source IP address.
 * @param out Destination IP address.
 * @param time Duration of the request.
 * @param type Type of the request ('S' or 'P').
 */
Request::Request(const std::string &in, const std::string &out, size_t time, char type) : ipIn(in), ipOut(out), duration(time), jobType(type) {}

/**
 * @brief Default constructor for Request.
 * 
 * Initializes a Request with default values.
 */
Request::Request() : ipIn(""), ipOut(""), duration(0), jobType('U') {}  

/**
 * @brief Gets the duration of the request.
 * @return The duration of the request in ticks.
 */
size_t Request::getDuration() const {
    return duration;
}

/**
 * @brief Gets the type of the request.
 * @return The type of the request ('S', 'P', or 'U').
 */
char Request::getJobType() const {
    return jobType;
}

/**
 * @brief Outputs a string representation of the Request object.
 * @param os The output stream to write to.
 * @param r The Request object to output.
 * @return The modified output stream.
 */
std::ostream& operator<<(std::ostream &os, const Request &r) {
    os << "Request(" << r.ipIn << "->" << r.ipOut
       << ", time=" << r.duration << ", type=" << r.jobType << ")";
    return os;
}

/**
 * @file request.h
 * @brief Header file for the Request class.
 * 
 * This class represents a network request in the load balancer simulation.
 */

#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <iostream>

/**
 * @class Request
 * @brief Represents a network request with a source, destination, duration, and job type.
 */
class Request {
private:
    std::string ipIn;  /**< Source IP address. */
    std::string ipOut; /**< Destination IP address. */
    size_t duration;   /**< Duration of the request in ticks. */
    char jobType;      /**< Type of the request ('S' for Standard, 'P' for Priority, 'U' for Undefined). */

public:
    /**
     * @brief Constructs a Request with specified parameters.
     * @param in Source IP address.
     * @param out Destination IP address.
     * @param time Duration of the request.
     * @param type Type of the request ('S' or 'P').
     */
    Request(const std::string &in, const std::string &out,
            size_t time, char type);

    /**
     * @brief Default constructor (creates an empty / dummy request).
     */
    Request();

    /**
     * @brief Gets the duration of the request.
     * @return The duration of the request in ticks.
     */
    size_t getDuration() const;

    /**
     * @brief Gets the type of the request.
     * @return The type of the request ('S', 'P', or 'U').
     */
    char getJobType() const;

    /**
     * @brief Outputs a string representation of the Request object.
     * @param os The output stream to write to.
     * @param r The Request object to output.
     * @return The modified output stream.
     */
    friend std::ostream& operator<<(std::ostream &os, const Request &r);
};

#endif
