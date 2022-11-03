#ifndef ABSTRACTGL_AIMAGE_HPP
#define ABSTRACTGL_AIMAGE_HPP

#include "AbstractGL/Color.hpp"

namespace aGL {
    class Image
    {
        class Image_;
        Image_* ip_ = nullptr;
        friend class Texture;
    public:
        Image();
        Image(uint32_t w, uint32_t h, const Color& col = aGL::Colors::White) : Image() { create(w, h, col); }
        Image(const char* filename);
        Image(const Image& oth);
        Image& operator=(const Image& oth); 
        ~Image();

        void loadFromFile(const char* filename);
        void saveToFile(const char* filename);
        void create(uint32_t w, uint32_t h, const Color& col = aGL::Colors::White);

        const Color* getPixels() const;
        Color getPixel(unsigned int x, unsigned int y) const;
        void setPixel(unsigned int x, unsigned int y, const Color& color);

        uint32_t getW() const;
        uint32_t getH() const;

        bool isCreated() const;
    };
}

#endif /* ABSTRACTGL_AIMAGE_HPP */
