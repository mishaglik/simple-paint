#ifndef LOGUTILS_NULLLOGGER_HPP
#define LOGUTILS_NULLLOGGER_HPP

#include <LogUtils/Logger.hpp>

namespace mlg {

    /**
     * @brief Null logger -
     *           - one logger to rule nothing.
     * 
     */
    class NullLogger final : public Logger 
    {
    public:
        constexpr NullLogger() {}
        constexpr ~NullLogger() override final {}
        virtual Logger& operator<<(char) override final {return *this;}
        
        constexpr virtual Logger& operator<<(uint32_t)override final {return *this;}
        constexpr virtual Logger& operator<<(int32_t )override final {return *this;}
        constexpr virtual Logger& operator<<(uint64_t)override final {return *this;}
        constexpr virtual Logger& operator<<(int64_t )override final {return *this;}
        constexpr virtual Logger& operator<<(double  )override final {return *this;}

        constexpr virtual Logger& operator<<(const char*) override final {return *this;}
        constexpr virtual Logger& operator<<(const void*) override final {return *this;}

        constexpr virtual void flush()   override final {}
        constexpr virtual void newline() override final {}
        constexpr virtual void endline() override final {}
        constexpr virtual void printWelcome  () override final {}
        constexpr virtual void printFinish   () override final {}
        constexpr virtual void printLineStart() override final {}

        constexpr virtual Logger& operator<<(CoStyle) override final {return *this;}
    };
}

#endif /* LOGUTILS_NULLLOGGER_HPP */
