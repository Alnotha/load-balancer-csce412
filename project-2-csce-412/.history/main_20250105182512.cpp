#include <iostream>
#include <string>
#include "load-balancer.h"

int main() {
    size_t numServers;
    size_t runTime;

    std::cout << "Enter number of servers: ";
    std::cin >> numServers;
    std::cout << "Enter how long to run simulation: ";
    std::cin >> runTime;

    LoadBalancer lb(numServers, runTime);
    lb.run();
    lb.printResults();

    return 0;
}
