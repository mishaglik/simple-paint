#ifndef GIF_GIF_HPP
#define GIF_GIF_HPP

#include <bits/types/FILE.h>
#include <cstddef>
#include <cstdint>

class GIF
{
public:
    GIF();
    GIF(const char* filename);
    GIF(const void* data, std::size_t size);

    void loadFromFile(const char* filename);
    void loadFromMem (const void* data, size_t size);

    ~GIF();

    GIF(const GIF&) = delete;
    GIF& operator= (const GIF&) = delete;

    size_t getW() const;
    size_t getH() const;

    int getFrameDuration() const;
private:
    const void* data_ = nullptr;
    size_t size;
    bool ownData_;

#pragma pack(1)

    struct ColorTriplet
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;
    };

    struct Header
    {
        char sign[3];
        char vers[3];
        uint16_t width;
        uint16_t height;
        uint8_t flags;
        uint8_t backgroudColorIndex;
        uint8_t pixelAspectRatio;

        constexpr bool    globalColorTable() const { return (flags & 0x80) >> 7; } 
        constexpr uint8_t colorResolution()  const { return ((flags & 0x70) >> 4) + 1; } 
        constexpr bool    sortFlag()         const { return (flags & 0x08) >> 3; } 
        constexpr size_t  GCTSize()          const { return 1ull << ((flags & 0x07) + 1); } 

        ColorTriplet GCT[];
    };

    struct ImageDesc
    {
        uint8_t ImgSeparator;
        uint16_t x;
        uint16_t y;
        uint16_t w;
        uint16_t h;
        uint8_t flags;

        constexpr bool    localColorTable() const { return (flags & 0x80) >> 7; } 
        constexpr uint8_t interlance()      const { return (flags & 0x40) >> 6; } 
        constexpr bool    sortFlag()        const { return (flags & 0x20) >> 5; } 
        constexpr size_t  LCTSize()          const { return 1ull << ((flags & 0x07) + 1); } 
    };

    static constexpr const char GIF_SIGNATURE[3] = {'G', 'I', 'F'};
    static constexpr const char GIF_VERSION[3]   = {'8', '9', 'a'};
    static const char GIF_IMAGE_DESC = ',';
    static const char GIF_EXTEN_DESC = '!';

#pragma pack(0)

    size_t w_, h_;

};

#endif /* GIF_GIF_HPP */
