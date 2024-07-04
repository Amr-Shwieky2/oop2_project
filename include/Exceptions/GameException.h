#pragma once
#include <exception>
#include <string>

class GameException : public std::exception {
public:
    explicit GameException(const std::string& message) : m_message(message) {}
    virtual const char* what() const noexcept override {
        return m_message.c_str();
    }
private:
    std::string m_message;
};
