#ifndef LOGUTILS_CONSOLELOGGER_HPP
#define LOGUTILS_CONSOLELOGGER_HPP

#include <LogUtils/Logger.hpp>
#include <iostream>
#include <iomanip>

namespace mlg {

    class ConsoleLogger : public mlg::Logger
    {
        std::ostream& out_;

        static constexpr std::ios_base::fmtflags getFlags(FmtFlag flag);
        static constexpr std::ios_base::fmtflags getMasks(FmtMask mask);

    public:
        ConsoleLogger(std::ostream& out) : out_(out) {
            printWelcome();
            out_.setf(std::ios_base::showbase, std::ios_base::showbase);
            out_.setf(std::ios_base::internal, std::ios_base::adjustfield);
            out_ << std::setfill('0');
        }

        virtual ~ConsoleLogger() override { printFinish(); }

        void setFmtFlags(FmtFlag flag, FmtMask mask) override;

        void setWidth(uint64_t w) override;

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
