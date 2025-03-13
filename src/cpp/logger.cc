#include <iostream>
#include <fstream>
#include <ctime>
#include "../../include/cpp/logger.h"

using namespace std;

#define LOG_FILE "data/transactions.log"

string getTimestamp() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);
    return string(buffer);
}

void Logger::logMessage(const string &message) {
    ofstream logFile(LOG_FILE, ios::app);
    if (logFile) {
        logFile << "[" << getTimestamp() << "] " << message << endl;
        logFile.close();
    } else {
        cerr << "❌ Error: Could not write to log file.\n";
    }
}

void Logger::logTransaction(int accountId, const string &type, double amount, int targetAccountId) {
    ofstream logFile(LOG_FILE, ios::app);
    if (logFile) {
        logFile << "[" << getTimestamp() << "] Account #" << accountId 
                << " | " << type << " | Amount: $" << amount;

        if (targetAccountId != -1) {
            logFile << " | Target Account #" << targetAccountId;
        }

        logFile << endl;
        logFile.close();
    } else {
        cerr << "❌ Error: Could not write to log file.\n";
    }
}

void Logger::logAuth(int accountId, bool success) {
    ofstream logFile(LOG_FILE, ios::app);
    if (logFile) {
        logFile << "[" << getTimestamp() << "] Account #" << accountId 
                << " | LOGIN " << (success ? "SUCCESS" : "FAILED") << endl;
        logFile.close();
    } else {
        cerr << "❌ Error: Could not write to log file.\n";
    }
}
