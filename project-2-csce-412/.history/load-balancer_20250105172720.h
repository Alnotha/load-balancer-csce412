#ifndef LOAD_BALANCER_H
#define LOAD_BALANCER_H

#include <vector>
#include <queue>
#include <tuple>
#include <string>
#include <sstream>
#include <cstdlib>  // for rand, srand
#include "server.h"

using std::vector;
using std::queue;
using std::string;
using std::tuple;
using std::cout;
using std::ostringstream;
using std::ostream;

// A class that tries to distribute requests among servers
class LoadBalancer {
private:
    // how long we run
    size_t totalTime;

    // how far we've gone
    size_t currentTick;

    // servers in use
    vector<Server> serverList;

    // requests that got processed (with server and time)
    vector<tuple<Request, Server, size_t>> doneList;

    // requests we still have to process
    queue<Request> reqQueue;

    // how many requests we had to drop
    size_t rejectedCount;

    // get random number between min and max
    size_t randomNum(size_t mini, size_t maxi) {
        return mini + rand() % (maxi - mini + 1);
    }

    // generate random IP
    string makeRandomIP() {
        ostringstream out;
        out << randomNum(1, 255) << "."
            << randomNum(0, 255) << "."
            << randomNum(0, 255) << "."
            << randomNum(1, 255);
        return out.str();
    }

    // put some requests into the queue
    void createRequests(size_t count, ostream &os = cout) {
        size_t generated = 0;
        for (size_t i = 0; i < count; i++) {
            if (reqQueue.size() + 1 > serverList.size() * 5) {
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

    // spin up servers
    void buildServers(size_t count, ostream &os = cout) {
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

public:
    // default
    LoadBalancer()
        : totalTime(0), currentTick(0), serverList(),
          doneList(), reqQueue(), rejectedCount(0) {
    }

    // main constructor
    LoadBalancer(size_t runTime, size_t numServers, size_t numRequests)
        : totalTime(runTime), currentTick(0), serverList(),
          doneList(), reqQueue(), rejectedCount(0) {
        buildServers(numServers);
        createRequests(numRequests);
    }

    // copy
    LoadBalancer(const LoadBalancer &other)
        : totalTime(other.totalTime),
          currentTick(other.currentTick),
          serverList(other.serverList),
          doneList(other.doneList),
          reqQueue(other.reqQueue),
          rejectedCount(other.rejectedCount) {
    }

    // move
    LoadBalancer(LoadBalancer &&other)
        : totalTime(other.totalTime),
          currentTick(other.currentTick),
          serverList(move(other.serverList)),
          doneList(move(other.doneList)),
          reqQueue(move(other.reqQueue)),
          rejectedCount(other.rejectedCount) {
        other.totalTime = 0;
        other.currentTick = 0;
        other.rejectedCount = 0;
    }

    ~LoadBalancer() {}

    // copy assign
    LoadBalancer &operator=(const LoadBalancer &other) {
        if (this != &other) {
            totalTime = other.totalTime;
            currentTick = other.currentTick;
            serverList = other.serverList;
            doneList = other.doneList;
            reqQueue = other.reqQueue;
            rejectedCount = other.rejectedCount;
        }
        return *this;
    }

    // move assign
    LoadBalancer &operator=(LoadBalancer &&other) {
        if (this != &other) {
            totalTime = other.totalTime;
            currentTick = other.currentTick;
            serverList = move(other.serverList);
            doneList = move(other.doneList);
            reqQueue = move(other.reqQueue);
            rejectedCount = other.rejectedCount;

            other.totalTime = 0;
            other.currentTick = 0;
            other.rejectedCount = 0;
        }
        return *this;
    }

    // give a server the front request
    void giveRequest(Server &srv) {
        srv.setRequest(reqQueue.front());
        reqQueue.pop();
    }

    // run the simulation
    void run(ostream &os = cout) {
        // enable all servers and start them off with requests
        for (auto &srv : serverList) {
            srv.setEnabled(true);
            giveRequest(srv);
        }

        while (++currentTick <= totalTime) {
            os << "Clock: " << currentTick << "\n";
            for (auto &srv : serverList) {
                if (srv.isBusy()) {
                    srv.handleRequest();
                } else {
                    if (srv.isEnabled()) {
                        // we finished that request
                        doneList.push_back({srv.getRequest(), srv, currentTick});
                        if (reqQueue.empty()) {
                            srv.setEnabled(false);
                            os << srv << " turned off (no more queue).\n";
                        } else {
                            giveRequest(srv);
                        }
                        os << srv << " finished last request.\n";
                        os << srv.getRequest() << " was completed.\n";
                    } else {
                        // if server is not enabled, but we have requests
                        if (!reqQueue.empty()) {
                            srv.setEnabled(true);
                            giveRequest(srv);
                        }
                    }
                }
            }
            os << "\n";

            // randomly add more requests sometimes
            if (!randomNum(0, 100)) {
                createRequests(randomNum(1, 64));
            }
        }
    }

    // show which requests got handled
    void showLog(ostream &os = cout) const {
        for (auto &record : doneList) {
            const Request &r = std::get<0>(record);
            const Server &s = std::get<1>(record);
            size_t t = std::get<2>(record);
            os << "At time " << t << ", " << s << " processed " << r << "\n";
        }
        os << "We handled " << doneList.size() << " request(s).\n";
        os << "We rejected " << rejectedCount << " request(s).\n";
    }
};

#endif // LOAD_BALANCER_H
