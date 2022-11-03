#include "SkinManager.hpp"
#include "LogUtils/LogUtils.hpp"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#include <libXML/tinyxml2.h>
#pragma clang diagnostic pop

namespace aGL {
    SkinManager::SkinManager() : skins_(1, {}) {}
    SkinManager::~SkinManager() {}

    bool SkinManager::loadSkinset(const char* path)
    {
        mAssert(path);
        
        std::string dir = path;
        if(dir.back() == '/') dir.pop_back();

        std::string xmlPath = dir + "/skin.xml";
        tinyxml2::XMLDocument doc;
        if(doc.LoadFile(xmlPath.c_str()) != 0)
        {
            mError << "SkinManager: Error opening file" << mlg::endl;
            return false;
        }

        tinyxml2::XMLElement* root = doc.RootElement();
        tinyxml2::XMLElement* node = root->FirstChildElement();

        while(node != nullptr)
        {
            if(!strcmp(node->Name(), "_default"))
            {
                tinyxml2::XMLElement* fontNode = node->FirstChildElement("font");
                if(fontNode)
                {
                    if(fontNode->GetText()[0] != '/')
                    {
                        fontname_ = dir;
                        fontname_ += '/';
                    }
                    fontname_ += fontNode->GetText();
                }
                node = node->NextSiblingElement();
                continue;
            }

            if(TexId id = findTextureId(node->Name(), true))
            {
                skins_[id].texture.loadFromFile(node->FirstChildElement("image")->Attribute("src"));
            }
            else {
                mInfo << "New element: " << node->Name() << mlg::endl;
                if(node->FirstChildElement("image"))
                {
                    mInfo << "  has image element" << mlg::endl;
                    std::string imagePath = dir + '/';
                    imagePath += node->FirstChildElement("image")->Attribute("src");
                    skins_.push_back({Texture(imagePath.c_str()), node->Name()});
                }
            }
            node = node->NextSiblingElement();
        }
        return true;
    }
    
    const Texture& SkinManager::operator[](TexId id) const
    {
        if(id == IgnoreTexture) return skins_[0].texture;
        return skins_[id].texture;
    }
    
    TexId SkinManager::findTextureId(const char* entity, bool silent) const
    {
        if(!entity) return NoTexture;
        for(size_t i = 1; i < skins_.size(); ++i)
        {
            if(skins_[i].name == entity)
            {
                return i;
            }
        }
        if(!silent)
            mInfo << "Asked for texture :\"" << entity <<"\" -- " << mlg::ConsoleLogger::CoStyle::Red << "not found" << mlg::endl;
        return NoTexture;
    }
    
    const char* SkinManager::getFont()
    {
        return fontname_.c_str();
    }
}
