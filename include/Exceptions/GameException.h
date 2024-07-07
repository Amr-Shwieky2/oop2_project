#pragma once
#include <exception>
#include <string>

// Custom exception class for game-related errors
class GameException : public std::exception {
public:
    explicit GameException(const std::string& message) : m_message(message) {}

    // Override what() method to return exception message
    virtual const char* what() const noexcept override {
        return m_message.c_str();
    }

private:
    std::string m_message; // Exception message
};
