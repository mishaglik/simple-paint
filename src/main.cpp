#include <cstdint>
#include <iostream>
#include "Application.hpp"

#include <LogUtils/LogUtils.hpp>

int main(int argc, const char* argv[]){
   mlg::ConsoleLogger logger(std::cerr);
   logger.setLogLevel(mlg::Logger::LogLevel::INFO);
   setGlobalLogger(&logger);
   Application app(argc, argv);

   return app.exec();
}
