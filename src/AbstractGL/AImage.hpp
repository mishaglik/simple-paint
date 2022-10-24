#ifndef ABSTRACTGL_AIMAGE_HPP
#define ABSTRACTGL_AIMAGE_HPP

#include "AbstractGL/Color.hpp"

namespace aGL {
    class Image
    {
        class Image_;
        Image_* ip_ = nullptr;
    public:
        Image();
        Image(const char* filename);
        Image(const Image& oth);
        Image& operator=(const Image& oth); 
        ~Image();

        void loadFromFile(const char* filename);

        const Color* getPixels() const;
        Color getPixel(unsigned int x, unsigned int y) const;
    };
}

#endif /* ABSTRACTGL_AIMAGE_HPP */
