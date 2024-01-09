#include <memory>

#include <raylib.h>

#include "atlas.h"

std::unique_ptr<AtlasTexture> AtlasTexture::create(const Texture2D *texture)
{
    auto atlas_texture = std::make_unique<AtlasTexture>();

    Texture texture_cpy = *texture;
    std::unique_ptr<Texture> texture_ptr;

    texture_ptr.reset(&texture_cpy);

    atlas_texture.get()->atlas_image = std::move(texture_ptr);

    return atlas_texture;
}
