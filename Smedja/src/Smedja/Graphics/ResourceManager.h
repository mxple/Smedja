#pragma once
#include "Smedja/Graphics/Texture.h"

namespace Smedja {

// ResourceManager class responsible for pointing sprites to the correct texture
// atlas and managing texcoords of each sprite.
class ResourceManager {
public:
    ResourceManager();
    ~ResourceManager();

    // reloads texture atlases, points sprites to the correct texture atlas, and
    // passes data to gpu
    void reload();

    void addTexture(const std::string &name, const std::string &path);

    const std::shared_ptr<Texture> &texture() const;

private:
    struct Rect {
        int x;
        int y;
        int width;
        int height;
        bool rotated;
    };

    std::shared_ptr<Texture> m_textureAtlas;


};

} // namespace Smedja


/*

    Rectangle packer:
    Takes in a list of rectangle structs that represent a sprite.


*/
