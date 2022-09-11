#include <bits/chrono.h>
#include <cstdint>
#include <iostream>
#include <chrono>
#include "AbstractGL/AWindow.hpp"

int main(){
    // std::cout << v.len();
    aGL::Window window(800, 600, "Test window");
    unsigned char i = 0;
    auto timestamp = std::chrono::high_resolution_clock::now();
    while(window.pollEvent().type != aGL::EventType::Exit){
        window.clear();
        window.drawRect({100u, 200, 300, 400}, 0xFF00FFFF);
        window.drawText("Aboba\nb\no\nb\na");
        window.drawLine({10,10}, {100, 300}, 0xFFFFFFFF);
        window.update();
        i++;
        if(!i){
            auto now = std::chrono::high_resolution_clock::now();
            int64_t interval = std::chrono::duration_cast<std::chrono::milliseconds>(now - timestamp).count();
            timestamp = now;
            std::cout << "FPS: " << (256 * 1000ll / interval) << std::endl;
        }
    }
    window.hide();
}
