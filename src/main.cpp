#include <cstdint>
#include <iostream>
#include "Application.hpp"
#include <LogUtils/LogUtils.hpp>
#include <Vector/Vector.hpp>

int main(int argc, const char* argv[]){
   
   Application app(argc, argv);
   app.exec();

   mInfo << "Finished" << mlg::endl;
   return 0;
}
