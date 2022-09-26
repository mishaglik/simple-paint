#ifndef LOGUTILS_NULLLOGGER_HPP
#define LOGUTILS_NULLLOGGER_HPP

#include <LogUtils/Logger.hpp>

namespace mlg {

    /**
     * @brief Null logger -
     *           - one logger to rule nothing.
     * 
     */
    class NullLogger : public Logger
    {
    public:
        ~NullLogger() override {}
        virtual Logger& operator<<(char) override {return *this;}
        
        virtual Logger& operator<<(uint32_t)override {return *this;}
        virtual Logger& operator<<(int32_t )override {return *this;}
        virtual Logger& operator<<(uint64_t)override {return *this;}
        virtual Logger& operator<<(int64_t )override {return *this;}
        virtual Logger& operator<<(double  )override {return *this;}

        virtual Logger& operator<<(const char*) override {return *this;}
        virtual Logger& operator<<(const void*) override {return *this;}

        virtual void flush()   override {}
        virtual void newline() override {}
        virtual void printWelcome  () override {}
        virtual void printFinish   () override {}
        virtual void printLineStart() override {}

        virtual Logger& operator<<(CoStyle) override {return *this;}
    };
}

#endif /* LOGUTILS_NULLLOGGER_HPP */
