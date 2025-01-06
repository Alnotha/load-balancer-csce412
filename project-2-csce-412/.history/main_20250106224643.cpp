#include "load-balancer.h"
#include <iostream>

int main() {
    int numServers, timeLimit;

    std::cout << "Enter number of servers: ";
    std::cin >> numServers;

    std::cout << "Enter how long to run simulation: ";
    std::cin >> timeLimit;

    LoadBalancer loadBalancer(numServers, numServers * 2);
    loadBalancer.runSimulation(timeLimit);

    return 0;
}
