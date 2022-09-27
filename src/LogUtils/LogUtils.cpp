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
        // LOG->~Logger(); 
        // abort();
    }


}

#ifdef MEM_VERBOSE

void* operator new (size_t size)
{
    void* pt = malloc(size);
    while(pt == nullptr)
    {
        mInfo << "new:" <<"malloc returned " << mlg::Logger::CoStyle::Bold << "nullptr" << mlg::endl;
        std::new_handler hdl = std::get_new_handler();
        if(hdl == nullptr){
            mError << "new: get_new_handler returned " << mlg::Logger::CoStyle::Bold << "nullptr" << mlg::endl;
            throw std::bad_alloc();
        }
        (*hdl)();
        pt = malloc(size);
    }

    mInfo << "new: malloc returned " << mlg::Logger::CoStyle::Bold << pt << mlg::endl;
    return pt;
} 


void* operator new[] (size_t size) 
{ 
    mInfo << "new[" << size << "] -- calling base new" << mlg::endl;
    return operator new(size); 
}

void operator delete (void* pt) noexcept
{
    
    mInfo << "delete: " << pt << mlg::endl;
    
    free(pt);
}

void operator delete[]( void* pt) noexcept
{
    mInfo << "delete[]: " << pt << mlg::endl;

    operator delete(pt);
}

#endif
