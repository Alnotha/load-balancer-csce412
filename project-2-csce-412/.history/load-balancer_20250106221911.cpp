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

void LoadBalancer::run(){
    //run the clock until we either exceed runTime or everything finishes (empty queue & all servers idle).
    while (true){
        currentTime++;
        cout << "[Time= "<< currentTime << "] \n";

        //let each server handle its current request for 1 tick
        //bool 
        for (auto &srv : servers){
            srv.handleRequest();
        }

        //checks if any server finished, if so, get next in queue
        for (auto &srv : servers){
            if (srv.hasRequestFinished()){
                cout << srv.getName() << " finished: " 
                          << srv.getCurrentRequest() << "\n";
                srv.clearCurrentRequest();

                //if another request waiting,assign it
                if (!requestQueue.empty()){
                    Request next = requestQueue.front();
                    requestQueue.pop();
                    srv.setRequest(next);
                    cout << srv.getName() << " started: " << next << "\n";
                }
            }
            //if server idle but queue not empty, give it a request
            else if (!srv.isBusy() && !requestQueue.empty()){
                Request next = requestQueue.front();
                requestQueue.pop();
                srv.setRequest(next);
                cout << srv.getName() << " started: " << next << " \n";
            }
        }

        // xtra requests:: at random intervals, add a new request
        if (rand() % 20 == 0){
            //5% chance every clock tick to add 1-3 new requests
            int howMany = 1 + (rand() % 3);
            for (int i = 0; i < howMany; i++){
                Request r(randomIP(), randomIP(), randomDuration(), randomJobType());
                requestQueue.push(r);
                cout << "new request arrives: " << r << "\n";
            }
        }

        //if all servers are idle and queue is empty, we can stop
        // bool allIdle = true;
        // for (auto &srv : servers){
        //     if (srv.isBusy()){
        //         allIdle = false;
        //         break;
        //     }
        // }
        // if (allIdle && requestQueue.empty()){
        //     cout << "All requests completed early. Stopping...\n";
        //     break;
        // }

        //if reached the runTime limit, also stop
        if (currentTime >= runTime){
            cout << "Reached max runtime (" << runTime << "). Stopping. \n";
            break;
        }
        cout << "\n";

        printf("There are %d servers running.\n", servers.size());
        printf("Server %d: busy=%d, remaining_time=%d\n", i, servers[i].busy, servers[i].remaining_time);

    }
}

void LoadBalancer::printResults() const{
    cout << "Simulation finished at time = " << currentTime << "\n";
    cout << "Remaining requests in queue: " << requestQueue.size() << "\n";
}
