#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>   
#include <string>

class Logger {
public:
    static void logMessage(const std::string& message);
    static void logTransaction(int accountId, const std::string& type, double amount, int targetAccountId = -1);
    static void logAuth(int accountId, bool success);

private:
    static const std::string logFile;  
};

#endif // LOGGER_H
