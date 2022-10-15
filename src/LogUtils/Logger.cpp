#include "Logger.hpp"
#include "NullLogger.hpp"

namespace mlg {

    extern mlg::NullLogger& NULL_LOGGER;
    const mlg::NullLogger nullLogger{};

    NullLogger& NULL_LOGGER = const_cast<NullLogger&>(nullLogger);


    void endl(Logger& log)
    {
        log.newline();
    }

    void Logger::setIdentSize(uint64_t identSize)
    {
        identSize_ = identSize;
    }

    void Logger::addIdent(uint64_t idents)
    {
        ident_ += idents * identSize_;
    }

    void Logger::remIdent(uint64_t idents)
    {
        if(idents * identSize_ <= ident_)
            ident_ -= idents * identSize_;
        else ident_ = 0;
    }

    void Logger::setLogLevel(LogLevel logLevel){
        logLevel_ = logLevel;
    }

    void Logger::setVerbosity(uint64_t verbosity)
    {
        verbosity_ = verbosity;
    }

    void Logger::addVerbosity(uint64_t verbosity) 
    {
        verbosity_ |= verbosity;
    }

    void Logger::remVerbosity(uint64_t verbosity)
    {
        verbosity_ &= ~verbosity;
    }   

    Logger& Logger::debug()
    {
        if(logLevel_ > LogLevel::DEBUG) return NULL_LOGGER;
        operator<<(CoStyle::Reset);
        printLineStart();
        return *this << "[" << CoStyle::Blue << "Debug" << CoStyle::Reset << "  ]: ";
    }
    
    Logger& Logger::info()
    {
        if(logLevel_ > LogLevel::INFO) return NULL_LOGGER;
        operator<<(CoStyle::Reset);
        printLineStart();
        return *this << "[Info   ]: ";
    }

    Logger& Logger::warning(){
        if(logLevel_ > LogLevel::WARNING) return NULL_LOGGER;
        operator<<(CoStyle::Reset);
        printLineStart();
        return *this << "[" << CoStyle::Yellow << "Warning" << CoStyle::Reset << "]: ";
    }

    Logger& Logger::error()
    {
        if(logLevel_ > LogLevel::ERROR) return NULL_LOGGER;
        operator<<(CoStyle::Reset);
        printLineStart();
        return *this << "[" << CoStyle::Red << "Error" << CoStyle::Reset << "  ]: ";
    }

    Logger& Logger::fatal(){
        if(logLevel_ > LogLevel::FATAL) return NULL_LOGGER;
        operator<<(CoStyle::Reset);
        printLineStart();
        return *this << "[" << CoStyle::Red << CoStyle::Bold << "Fatal" << CoStyle::Reset << "  ]: ";
    }

    void hex(Logger& log)
    {
        log.setFmtFlags(Logger::FmtFlag::Hex, Logger::FmtMask::BaseMask);
    }

    void dec(Logger& log)
    {
        log.setFmtFlags(Logger::FmtFlag::Dec, Logger::FmtMask::BaseMask);

    }

    void oct(Logger& log)
    {
        log.setFmtFlags(Logger::FmtFlag::Oct, Logger::FmtMask::BaseMask);
    }
    
    void Logger::setFmtFlags(FmtFlag flag, FmtMask mask)
    {
        outputFlags_ = (outputFlags_ & ~mask) | flag;
    }
    
    void Logger::setWidth(uint64_t w){
        widht_ = w;
    }
    
}
