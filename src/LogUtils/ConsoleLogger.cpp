#include "ConsoleLogger.hpp"
#include "LogUtils/LogUtils.hpp"
#include <chrono>
#include <iomanip>

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


    void ConsoleLogger::setFmtFlags(FmtFlag flag, FmtMask mask)
    {

        out_.setf(getFlags(flag), getMasks(mask));
        Logger::setFmtFlags(flag, mask);
    }

    constexpr std::ios_base::fmtflags ConsoleLogger::getFlags(FmtFlag flag){
        switch (flag) {
        case Logger::Dec:
            return std::ios_base::dec;
        case Logger::Hex:
            return std::ios_base::hex;
        case Logger::Oct:
            return std::ios_base::oct;
        case Logger::Bin:
            break;
        case Logger::ShowBase:
          return std::ios_base::showbase;
        }
        mAssert(0 && "Error flag");
        abort();
    }

    constexpr std::ios_base::fmtflags ConsoleLogger::getMasks(FmtMask mask){
        switch (mask) {
        case Logger::BaseMask:
          return std::ios_base::basefield;
        case Logger::ShowBaseMask:
            return std::ios_base::showbase;
        }
        mAssert(0 && "Error mask");
        abort();
    }

    void ConsoleLogger::setWidth(uint64_t w)
    {
        out_ << std::setw(static_cast<int>(w));
    }

}
