#ifndef LOGUTILS_CONSOLELOGGER_HPP
#define LOGUTILS_CONSOLELOGGER_HPP

#include <LogUtils/Logger.hpp>
#include <iostream>

namespace mlg {

    class ConsoleLogger : public mlg::Logger
    {
        std::ostream& out_;
    public:
        ConsoleLogger(std::ostream& out) : out_(out) {
            printWelcome();
        }

        virtual ~ConsoleLogger() override { printFinish(); }


        virtual Logger& operator<<(char x) override;
        
        virtual Logger& operator<<(uint32_t x) override;
        virtual Logger& operator<<(int32_t  x) override;
        virtual Logger& operator<<(uint64_t x) override;
        virtual Logger& operator<<(int64_t  x) override;

        virtual Logger& operator<<(const char* x) override;
        virtual Logger& operator<<(const void* x) override;

        virtual void flush() override;
        
        virtual void newline() override;

        virtual void printWelcome  () override;
        virtual void printFinish   () override;
        virtual void printLineStart() override;

        virtual Logger& operator<<(Logger::CoStyle newStyle) override;
        
    };

}

#endif /* LOGUTILS_CONSOLELOGGER_HPP */
