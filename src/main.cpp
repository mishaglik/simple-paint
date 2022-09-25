#include <cstdint>
#include <iostream>
#include "Application.hpp"

#include <LogUtils/LogUtils.hpp>

int main(int argc, const char* argv[]){

   mlg::ConsoleLogger logger(std::cerr);
   setGlobalLogger(&logger);

   mInfo << "Hello " << mlg::Logger::CoStyle::Red << "BUGS!!!" << mlg::endl;
   mWarning << "Hello " << mlg::Logger::CoStyle::Red << "BUGS!!!" << mlg::endl;
   mError << "Hello " << mlg::Logger::CoStyle::Red << "BUGS!!!" << mlg::endl;
   mFatal << "Hello " << mlg::Logger::CoStyle::Red << "BUGS!!!" << mlg::endl;
   mAssert(0);
   Application app(argc, argv);
   return app.exec();
}
