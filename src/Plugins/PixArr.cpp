#include "PixArr.hpp"
#include <cassert>

using namespace bp;

UsedArr::UsedArr(size_t w, size_t h) : w_(w), h_(h)
{
    used_ = new uint64_t[(w_ * h_) / 64 + 1];
    clear();
}

void UsedArr::resize(size_t x, size_t y)
{
    delete [] used_;
    w_ = x;
    h_ = y;
    used_ = new uint64_t[(w_ * h_) / 64 + 1]; 
    clear();
}


UsedArr::~UsedArr() 
{
    delete [] used_;
}

bool UsedArr::get(size_t x, size_t y) 
{
    assert(isOnImage(x, y));
    size_t pos = y * w_ + x;
    return used_[pos / 64] & (1ull << (pos & 63));
}

void UsedArr::set(size_t x, size_t y) 
{
    size_t pos = y * w_ + x;
    used_[pos / 64] |= (1ull << (pos & 63));
}     

void UsedArr::clear()
{
    for (uint32_t i = 0; i < (w_ * h_) / 64 + 1; i++) 
    {
        used_[i] = 0;
    }
}
