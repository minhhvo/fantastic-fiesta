// @file ConsoleApp.cpp
#include "ConsoleApp.hpp"

namespace ConsoleApp {

    void endProcess(int signum) {
        std::cout << "\n\n[" << APP_NAME << "] Interrupt signal (" << signum << ") received. Exiting gracefully...\n";
        std::exit(0);
    }

    void displaySystemError(const std::error_code& e) {
        std::cerr << "[SystemError]: " << e.message() << "\n";
    }

    void handleException(const std::exception& e) {
        std::string exceptionMsg = e.what();
        
        if (exceptionMsg.find("Syntax") != std::string::npos) {
            std::cerr << "[SyntaxError]: " << exceptionMsg << "\n";
        } 
        else if (exceptionMsg.find("Domain") != std::string::npos) {
            std::cerr << "[DomainError]: " << exceptionMsg << "\n";
        } 
        else {
            std::cerr << "[InputError]: " << exceptionMsg << "\n";
        }
    }

    void initSignals(void) {
#ifdef SIGQUIT
        std::signal(SIGQUIT, endProcess); 
#endif
        std::signal(SIGINT, endProcess);
    }

} // end namespace ConsoleApp