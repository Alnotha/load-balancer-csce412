#ifndef REQUEST_H
#define REQUEST_H

#include <string>

class Request {
private:
    std::string ipIn;
    std::string ipOut;
    int time;
    char jobType; // 'S' for streaming, 'P' for processing

public:
    Request(); // Default constructor
    Request(const std::string &ipIn, const std::string &ipOut, int time, char jobType);

    static Request generateRandomRequest();
    int getTime() const;
    std::string getDescription() const;
};


#endif // REQUEST_H
