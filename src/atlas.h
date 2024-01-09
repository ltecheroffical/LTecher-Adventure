#include <memory>

#include <raylib.h>

#pragma once


/*
* Stores a texture atlas and can be cropped
*/
class AtlasTexture
{

public:
    AtlasTexture()  = default;
    ~AtlasTexture() = default;

    /*
    * Creates a instance of `AtlasTexture` from a `Texture2D`
    * 
    * @param texture The `Texture2D` to create the atlas from
    * 
    * @returns An instance of `AtlasTexture`
    */
    static std::unique_ptr<AtlasTexture> create(const Texture *texture);

    /*
    * Gets a region of the image in the atlas
    * 
    * @param region The region of the image to get
    * 
    * @returns A copy of the image at that region as `Texture2D`
    */
    std::shared_ptr<Texture> get_region(Rectangle region);
    /*
    * Gets a region of the image in the atlas
    * 
    * @param region The region of the image to get
    * 
    * @returns A copy of the image at that region as `Image`
    */
    std::shared_ptr<Image> get_region_image(Rectangle region);

private:
    std::unique_ptr<Texture> atlas_image;
};
