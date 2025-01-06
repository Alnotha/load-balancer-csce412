#include <iostream>
#include <string>
#include <cstdlib>
#include "load_balancer.h"

using std::cout;
using std::cin;
using std::getline;
using std::string;

int main() {
    srand(0);

    string input;
    size_t numServers = 0;
    size_t runTime = 0;

    cout << "Enter number of servers: ";
    getline(cin, input);
    numServers = std::stoul(input);

    cout << "Enter how long to run the load balancer: ";
    getline(cin, input);
    runTime = std::stoul(input);

    cout << "-----------------------------------------------------\n";
    cout << "We will start with: " << (numServers * 5) << " initial requests\n";
    cout << "Will run for: " << runTime << " time units\n";
    cout << "Request durations range from 3 to 16\n";
    cout << "-----------------------------------------------------\n";
    cout << "Starting load balancer now...\n";

    LoadBalancer lb(runTime, numServers, numServers * 5);
    lb.run();

    cout << "\nDone.\n\n";
    lb.showLog();

    return 0;
}
