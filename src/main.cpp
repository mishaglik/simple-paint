#include <cstdint>
#include <iostream>
#include "Application.hpp"

#include <LogUtils/LogUtils.hpp>

int main(int argc, const char* argv[]){
   
   Application app(argc, argv);

   return app.exec();
}
