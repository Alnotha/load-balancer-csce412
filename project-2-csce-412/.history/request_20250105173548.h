#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <iostream>

class Request {
private:
    std::string ipFrom;
    std::string ipTo;
    size_t duration;

public:
    // Constructors, destructor
    Request();
    Request(const std::string &i1, const std::string &i2, size_t d);
    Request(const Request &other);
    Request(Request &&other);
    ~Request();

    // Operators
    Request &operator=(const Request &other);
    Request &operator=(Request &&other);

    // Accessor
    const size_t &getDuration() const;

    // Friend function to print
    friend std::ostream &operator<<(std::ostream &os, const Request &req);
};

#endif // REQUEST_H
