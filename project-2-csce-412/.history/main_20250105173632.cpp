#include <iostream>
#include <string>
#include <cstdlib>      // for srand
#include "load-balancer.h"

int main() {
    srand(0);

    std::string input;
    size_t numServers = 0;
    size_t runTime = 0;

    std::cout << "Enter number of servers: ";
    std::getline(std::cin, input);
    numServers = std::stoul(input);

    std::cout << "Enter how long to run the load balancer: ";
    std::getline(std::cin, input);
    runTime = std::stoul(input);

    std::cout << "-----------------------------------------------------\n";
    std::cout << "We will start with: " << (numServers * 5) << " initial requests\n";
    std::cout << "Will run for: " << runTime << " time units\n";
    std::cout << "Request durations range from 3 to 16\n";
    std::cout << "-----------------------------------------------------\n";
    std::cout << "Starting load balancer now...\n";

    LoadBalancer lb(runTime, numServers, numServers * 5);
    lb.run();

    std::cout << "\nDone.\n\n";
    lb.showLog();

    return 0;
}
