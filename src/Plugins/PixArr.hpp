#ifndef PLUGINS_PIXARR_HPP
#define PLUGINS_PIXARR_HPP

#include "Elpstd/tools.hpp"
#include "Color.hpp"

namespace bp {
    class UsedArr
    {
    using size_t = std::size_t;
    public:
        UsedArr(std::size_t w, std::size_t h);
        ~UsedArr();
        UsedArr(const UsedArr& oth) = delete;
        UsedArr& operator=(const UsedArr& oth) = delete;


        std::size_t getH() { return w_; }
        std::size_t getW() { return h_; }
        bool get(size_t x, size_t y);
        void set(size_t x, size_t y);
        void clear();
        void resize(size_t x, size_t y);
        constexpr bool isOnImage(size_t x, size_t y) { return x >= 0 && y >= 0 && x <= w_ && y <= h_;}
    private:
        uint64_t* used_;
        std::size_t w_, h_;
    };
}

#endif /* PLUGINS_PIXARR_HPP */
