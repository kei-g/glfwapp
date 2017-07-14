#include "GLtexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLtexture::GLtexture(GLuint textureID, HGLOBAL resource, DWORD resourceSize)
	: image(nullptr), loaded(false), resourceData(LockResource(resource)), resourceSize(resourceSize), textureID(textureID)
{
}

GLtexture::GLtexture(GLuint textureID, HMODULE hModule, HRSRC resourceInfo)
	: GLtexture(textureID, LoadResource(hModule, resourceInfo), SizeofResource(hModule, resourceInfo))
{
}

void GLtexture::Load()
{
	if (loaded) {
		return;
	}

	if (!image) {
		throw std::exception("Image has not read yet");
	}

	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, std::get<1>(*image), std::get<2>(*image), GL_RGB, GL_UNSIGNED_BYTE, std::get<0>(*image));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	stbi_image_free(std::get<0>(*image));

	image = nullptr;
	loaded = true;
}

GLtexture::GLtexture(GLuint textureID, HMODULE hModule, int resourceID, LPCTSTR resourceType)
	: GLtexture(textureID, hModule, FindResource(hModule, MAKEINTRESOURCE(resourceID), resourceType))
{
}

GLtexture::~GLtexture()
{
	if (image) {
		stbi_image_free(std::get<0>(*image));
	}
	glDeleteTextures(1, &textureID);
}

void GLtexture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, textureID);
	Load();
}

void GLtexture::Read()
{
	if (image || loaded) {
		return;
	}

	stbi_set_flip_vertically_on_load(1);

	auto w = 0, h = 0, c = 0;
	auto img = stbi_load_from_memory(static_cast<stbi_uc *>(resourceData), static_cast<int>(resourceSize), &w, &h, &c, 0);
	if (!img) {
		throw std::exception("Can't decompress image from resource");
	}

	image = std::make_shared<std::tuple<void*, int, int>>(img, w, h);
}
