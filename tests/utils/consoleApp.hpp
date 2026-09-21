// @file ConsoleApp.hpp
#pragma once
#include <iostream>
#include <string>
#include <exception>
#include <csignal>
#include <system_error>
#include <concepts>

#ifndef APP_NAME
#define APP_NAME "Example"
#endif

namespace ConsoleApp {

    // Declarations for standard functions (implemented in .cpp)
    void endProcess(int signum);
    void displaySystemError(const std::error_code& e);
    void handleException(const std::exception& e);
    void initSignals(void);

    // Templates MUST remain in the header file
    template <std::invocable Func>
    inline void tryExecute(Func&& logic) {
        try {
            std::forward<Func>(logic)();
        } 
        catch (const std::exception& e) {
            handleException(e);
        }
        catch (...) {
            std::cerr << "[Critical]: An unknown exception occurred.\n";
            std::exit(-1);
        }
    }

    template <typename ExecuteFn>
    inline void runRepl(ExecuteFn&& executeCommand) {
        initSignals();
        
        std::cout << APP_NAME << " Console Application\n\n";
        std::cout << "Enter any expression to start\n\n\t'quit' or 'Q' to exit.\n\n";
        std::cout << "Press 'Ctrl + D' (EOF) or 'Ctrl + C' to force quit.\n";

        std::string cmd_line;
        while (true) {
            std::cout << "\n> ";
            if (!std::getline(std::cin, cmd_line)) break;

            if (cmd_line == "quit" || cmd_line == "Q") {
                std::cout << "Exiting program...\n";
                std::exit(0);
            }
            if (cmd_line.empty()) continue;

            tryExecute([&]() {
                executeCommand(cmd_line);
            });
        }
    }
} // end namespace ConsoleApp