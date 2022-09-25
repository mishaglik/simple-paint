#include "ConsoleLogger.hpp"
#include <chrono>

namespace mlg {

    const size_t MAX_TIMESTAMP_LEN = 50;
    char const * const TIMESTAMP_FORMAT = "%d %b %T"; 

    Logger& ConsoleLogger::operator<<(char x) 
    {
        out_ << x;
        return *this;
    }
    
    Logger& ConsoleLogger::operator<<(uint32_t x) 
    {
        out_ << x;
        return *this;
    }

    Logger& ConsoleLogger::operator<<(int32_t  x) 
    {
        out_ << x;
        return *this;
    }
    
    Logger& ConsoleLogger::operator<<(uint64_t x) 
    {
        out_ << x;
        return *this;
    }

    Logger& ConsoleLogger::operator<<(int64_t  x) 
    {
        out_ << x;
        return *this;
    }

    Logger& ConsoleLogger::operator<<(const char* x) 
    {
        out_ << x;
        return *this;
    }

    Logger& ConsoleLogger::operator<<(const void* x) 
    {
        out_ << x;
        return *this;
    }

    void ConsoleLogger::flush() 
    {
        out_.flush();
    }

    void ConsoleLogger::newline() 
    {
        out_ << '\n';
    }

    void ConsoleLogger::printWelcome() 
    {
        operator<<(CoStyle::Reset);

        std::time_t time = std::time(nullptr);
        char timestamp[MAX_TIMESTAMP_LEN + 1] = "";

        std::strftime(timestamp, MAX_TIMESTAMP_LEN, TIMESTAMP_FORMAT, std::localtime(&time));

        out_ <<
        "/-----------------------------< LOG STARTS >-----------------------------\\\n" <<
        "| Time of start: " << timestamp << '\n' << 
        "| Let source be with you!                                                |\n" <<
        "\\------------------------------------------------------------------------/\n";
    }

    void ConsoleLogger::printFinish() 
    {
        operator<<(CoStyle::Reset);
        std::time_t time = std::time(nullptr);
        char timestamp[MAX_TIMESTAMP_LEN + 1] = "";

        std::strftime(timestamp, MAX_TIMESTAMP_LEN, TIMESTAMP_FORMAT, std::localtime(&time));

        out_ <<
        "/-----------------------------< LOG FINISHED >---------------------------\\\n" <<
        "| Time of finish: " << timestamp << '\n' << 
        "| Meow moew meow meow                                                    |\n" <<
        "\\------------------------------------------------------------------------/\n";
    }

    void ConsoleLogger::printLineStart() 
    {
        operator<<(CoStyle::Reset);

        std::time_t time = std::time(nullptr);
        char timestamp[MAX_TIMESTAMP_LEN + 1] = "";

        std::strftime(timestamp, MAX_TIMESTAMP_LEN, TIMESTAMP_FORMAT, std::localtime(&time));

        out_ << timestamp << ": ";
    }

    Logger& ConsoleLogger::operator<<(Logger::CoStyle newStyle) 
    {
        out_ << "\033[" << static_cast<int>(newStyle) << "m";
        return *this;
    }
}
