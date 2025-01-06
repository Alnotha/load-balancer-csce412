#include "load-balancer.h"
#include <iostream>
#include <sstream>
#include <cstdlib> // rand, srand
#include <utility> // std::move

LoadBalancer::LoadBalancer()
    : totalTime(0), currentTick(0), serverList(),
      doneList(), reqQueue(), rejectedCount(0) {}

LoadBalancer::LoadBalancer(size_t runTime, size_t numServers, size_t numRequests)
    : totalTime(runTime), currentTick(0), serverList(),
      doneList(), reqQueue(), rejectedCount(0)
{
    buildServers(numServers);
    createRequests(numRequests);
}

LoadBalancer::LoadBalancer(const LoadBalancer &other)
    : totalTime(other.totalTime),
      currentTick(other.currentTick),
      serverList(other.serverList),
      doneList(other.doneList),
      reqQueue(other.reqQueue),
      rejectedCount(other.rejectedCount) {}

LoadBalancer::LoadBalancer(LoadBalancer &&other)
    : totalTime(other.totalTime),
      currentTick(other.currentTick),
      serverList(std::move(other.serverList)),
      doneList(std::move(other.doneList)),
      reqQueue(std::move(other.reqQueue)),
      rejectedCount(other.rejectedCount)
{
    other.totalTime   = 0;
    other.currentTick = 0;
    other.rejectedCount = 0;
}

LoadBalancer::~LoadBalancer() {}

LoadBalancer &LoadBalancer::operator=(const LoadBalancer &other) {
    if (this != &other) {
        totalTime     = other.totalTime;
        currentTick   = other.currentTick;
        serverList    = other.serverList;
        doneList      = other.doneList;
        reqQueue      = other.reqQueue;
        rejectedCount = other.rejectedCount;
    }
    return *this;
}

LoadBalancer &LoadBalancer::operator=(LoadBalancer &&other) {
    if (this != &other) {
        totalTime     = other.totalTime;
        currentTick   = other.currentTick;
        serverList    = std::move(other.serverList);
        doneList      = std::move(other.doneList);
        reqQueue      = std::move(other.reqQueue);
        rejectedCount = other.rejectedCount;

        other.totalTime   = 0;
        other.currentTick = 0;
        other.rejectedCount = 0;
    }
    return *this;
}

// Helper: get random from [mini..maxi]
size_t LoadBalancer::randomNum(size_t mini, size_t maxi) {
    return mini + rand() % (maxi - mini + 1);
}

// Helper: random IP
std::string LoadBalancer::makeRandomIP() {
    std::ostringstream out;
    out << randomNum(1, 255) << "."
        << randomNum(0, 255) << "."
        << randomNum(0, 255) << "."
        << randomNum(1, 255);
    return out.str();
}

// Queue up some requests
void LoadBalancer::createRequests(size_t count, std::ostream &os) {
    size_t generated = 0;
    for (size_t i = 0; i < count; i++) {
        // Simple queue capacity check (5 * # of servers)
        if (reqQueue.size() >= serverList.size() * 5) {
            rejectedCount += (count - i);
            os << "Too many incoming requests. Rejected "
               << (count - i) << " requests.\n";
            break;
        }
        Request tmp(makeRandomIP(), makeRandomIP(), randomNum(3, 16));
        os << "Making request: " << tmp << "\n";
        reqQueue.push(tmp);
        generated++;
    }
    os << generated << " new requests put in queue.\n";
    os << "-------------------------------\n\n";
}

// Create servers
void LoadBalancer::buildServers(size_t count, std::ostream &os) {
    os << "Created these servers: ";
    for (size_t i = 0; i < count; i++) {
        serverList.emplace_back("Srv" + std::to_string(i));
        os << serverList.back();
        if (i + 1 < count) {
            os << ", ";
        }
    }
    os << "\n";
}

// Give front-of-queue request to a server
void LoadBalancer::giveRequest(Server &srv) {
    srv.setRequest(reqQueue.front());
    reqQueue.pop();
}

// Main simulation loop
void LoadBalancer::run(std::ostream &os) {
    // Start all servers with a request (if queue isn’t empty)
    for (auto &srv : serverList) {
        srv.setEnabled(true);
        if (!reqQueue.empty()) {
            giveRequest(srv);
        }
    }

    // Tick the clock
    while (++currentTick <= totalTime) {
        os << "Clock: " << currentTick << "\n";

        for (auto &srv : serverList) {
            if (srv.isBusy()) {
                srv.handleRequest();
            } else {
                // if server finished the request
                if (srv.isEnabled()) {
                    // log the finished request
                    doneList.push_back({srv.getRequest(), srv, currentTick});

                    // check if queue empty
                    if (reqQueue.empty()) {
                        srv.setEnabled(false);
                        os << srv << " turned off (no more queue).\n";
                    } else {
                        // next request for the server
                        giveRequest(srv);
                    }
                    os << srv << " finished last request.\n";
                    os << srv.getRequest() << " was completed.\n";
                } else {
                    // server is disabled, but if we have a request, re-enable
                    if (!reqQueue.empty()) {
                        srv.setEnabled(true);
                        giveRequest(srv);
                    }
                }
            }
        }
        os << "\n";

        // Randomly add more requests occasionally
        if (!randomNum(0, 100)) {
            createRequests(randomNum(1, 64));
        }
    }
}

// Print a summary of processed requests
void LoadBalancer::showLog(std::ostream &os) const {
    for (auto &record : doneList) {
        const Request &r = std::get<0>(record);
        const Server &s   = std::get<1>(record);
        size_t t          = std::get<2>(record);
        os << "At time " << t << ", " << s << " processed " << r << "\n";
    }
    os << "We handled " << doneList.size() << " request(s).\n";
    os << "We rejected " << rejectedCount << " request(s).\n";
}
