#include "PluginTextures.h"

std::map<std::string, RwTexture*> PluginTextures::Textures;

RwTexture* PluginTextures::GetTexture(std::string texture) {
	if (Textures.contains(texture) && Textures[texture])
		return Textures[texture];

	Textures[texture] = loadTextureFromFile(std::string(GetPath() + "\\textures\\" + texture + ".png").c_str());

    return Textures[texture];
};

RwTexture* PluginTextures::loadTextureFromFile(const char* filename) {
    RwImage* image = RtPNGImageRead(filename);

    RwInt32 width, height, depth, flags;
    RwImageFindRasterFormat(image, 4, &width, &height, &depth, &flags);

    RwRaster* raster = RwRasterCreate(width, height, depth, flags);

    RwRasterSetFromImage(raster, image);

    RwImageDestroy(image);

    return RwTextureCreate(raster);
};
