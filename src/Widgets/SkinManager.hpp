#ifndef WIDGETS_SKINMANAGER_HPP
#define WIDGETS_SKINMANAGER_HPP

#include "AbstractGL/ATexture.hpp"
#include "Vector/Vector.hpp"
#include <cstddef>
#include <string>

namespace aGL {
    using TexId = std::size_t;

    class SkinManager
    {
    public:
        SkinManager();
        ~SkinManager();

        SkinManager(const SkinManager&) = delete;
        SkinManager& operator=(const SkinManager&) = delete;

        bool loadSkinset(const char* path);
        
        const Texture& operator[](TexId id) const;
        const Texture& operator[](TexId id) {return skins_[id].texture;}

        const Texture& getTexture(TexId id) const {return skins_[id].texture;}
        
        TexId findTextureId(const char* entity) const;
        const char* getFont();

    private:
        struct Skin{
            Texture texture;
            std::string name;
        };

        mvc::Vector<Skin> skins_;
        std::string fontname_;
    };
}

#endif /* WIDGETS_SKINMANAGER_HPP */
