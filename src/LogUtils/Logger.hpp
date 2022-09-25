#ifndef LOGUTILS_LOGGER_HPP
#define LOGUTILS_LOGGER_HPP

#include <cstdint>

namespace mlg {
    class Logger{

        using manip_f = void(*)(Logger&);

        enum class LogLevel{
            DEBUG,
            INFO,
            WARNING,
            ERROR,
            FATAL
        };

    protected:

        uint64_t verbosity_ = 0;
        LogLevel logLevel_ = LogLevel::WARNING;
        uint64_t ident_ = 0;
        uint64_t identSize_ = 4;

    public:
        // TODO: Move to cpp
        void setIdentSize(uint64_t identSize) {identSize_ = identSize;}
        void addIdent(uint64_t idents = 1)    {ident_ += idents * identSize_;}
        void remIdent(uint64_t idents = 1)    {if(idents * identSize_ <= ident_) ident_ -= idents * identSize_; else ident_ = 0;}
        void setLogLevel(LogLevel logLevel)   {logLevel_   =  logLevel;}
        void setVerbosity(uint64_t verbosity) {verbosity_  =  verbosity;}
        void addVerbosity(uint64_t verbosity) {verbosity_ |=  verbosity;}
        void remVerbosity(uint64_t verbosity) {verbosity_ &= ~verbosity;}

        virtual ~Logger();

        virtual Logger& operator<<(char x)     = 0;
        
        virtual Logger& operator<<(uint32_t x) = 0;
        virtual Logger& operator<<(int32_t  x) = 0;
        virtual Logger& operator<<(uint64_t x) = 0;
        virtual Logger& operator<<(int64_t  x) = 0;

        virtual Logger& operator<<(const char* x) = 0;
        virtual Logger& operator<<(const void* x) = 0;

        virtual void flush() = 0;
        virtual void endl();

        Logger& operator<<(manip_f manip) { manip(*this); return *this;}
    };

    void endl(Logger& log);

    

}
#endif /* LOGUTILS_LOGGER_HPP */
