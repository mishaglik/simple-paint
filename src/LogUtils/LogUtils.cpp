#include "LogUtils.hpp"

static mlg::NullLogger NULL_LOG{};

static mlg::Logger* LOG = &NULL_LOG;

mlg::Logger& getGlobalLogger()
{
    return *LOG;
}

void setGlobalLogger(mlg::Logger* logger)
{
    LOG = logger;
}

namespace mlg {

    Logger& operator<< (mlg::Logger& out, const CodePlace& cp)
    {
        return out << "at " << cp.filename << ":" << cp.line << " in " << cp.function << "\n";
    }

    void assert_fail(const char* cond, const CodePlace& cp)
    {
        
        mFatal << Logger::CoStyle::Red << Logger::CoStyle::Bold << "Assertion (" << cond << ") failed " << cp << endl;
        LOG->~Logger(); 
        abort();
    }


}
