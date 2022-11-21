#include <cstdint>
#include <iostream>
#include "Application.hpp"
#include <LogUtils/LogUtils.hpp>
#include <Vector/Vector.hpp>

int main(int argc, const char* argv[]){
   
   Application app(argc, argv);
   int retval = app.exec();

   mInfo << "Finished" << mlg::endl;
   return retval;
}
