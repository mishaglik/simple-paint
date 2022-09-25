#ifndef LOGUTILS_LOGUTILS_HPP
#define LOGUTILS_LOGUTILS_HPP

#include <LogUtils/Logger.hpp>
#include <LogUtils/ConsoleLogger.hpp>
#include <LogUtils/NullLogger.hpp>

mlg::Logger& getGlobalLogger();
void setGlobalLogger(mlg::Logger* logger);


namespace mlg {
    
    struct CodePlace{
        int line;
        const char* const filename;
        const char* const function;
    };

    Logger& operator<< (mlg::Logger& out, const CodePlace& cp);

    [[noreturn]] void assert_fail(const char* cond, const CodePlace& cp);
}

#pragma clang diagnostic push 
#pragma clang diagnostic ignored "-Wunused-macros" 

#define MLG_HERE mlg::CodePlace{__LINE__, __FILE__, __PRETTY_FUNCTION__}

#define mDebug    (getGlobalLogger().debug  ())
#define mInfo     (getGlobalLogger().info   ())
#define mWarning  (getGlobalLogger().warning())
#define mError    (getGlobalLogger().error  ())
#define mFatal    (getGlobalLogger().fatal  ())

#ifndef NDEBUG
#define mAssert(x) ((x) ? void(0) : mlg::assert_fail(#x, MLG_HERE))
#else
#define mAssert(x)
#endif

#define mDUMP_FIELD(field) out << "."#field": " << field << mlg::endl;    

#pragma clang diagnostic pop

#endif /* LOGUTILS_LOGUTILS_HPP */
