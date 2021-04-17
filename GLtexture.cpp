#include "GLtexture.h"

#define STBI_ASSERT(expr)
#define STBI_NO_BMP
#define STBI_NO_FAILURE_STRINGS
#define STBI_NO_GIF
#define STBI_NO_HDR
#define STBI_NO_PIC
#define STBI_NO_PNM
#define STBI_NO_PSD
#define STBI_NO_STDIO
#define STBI_NO_TGA
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#if defined(_MSC_VER)
GLtexture::GLtexture(GLuint textureID, HGLOBAL resource, DWORD resourceSize)
	: image(nullptr), loaded(false), resourceData(LockResource(resource)), resourceSize(resourceSize), textureID(textureID)
{
}

GLtexture::GLtexture(GLuint textureID, HMODULE hModule, HRSRC resourceInfo)
	: GLtexture(textureID, LoadResource(hModule, resourceInfo), SizeofResource(hModule, resourceInfo))
{
}
#endif

void GLtexture::Load()
{
	if (loaded) {
		return;
	}

	if (!image) {
		throw std::runtime_error("Image has not read yet");
	}

	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, std::get<1>(*image), std::get<2>(*image), GL_RGB, GL_UNSIGNED_BYTE, std::get<0>(*image));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	stbi_image_free(std::get<0>(*image));

	image = nullptr;
	loaded = true;
}

#if defined(_MSC_VER)
GLtexture::GLtexture(GLuint textureID, HMODULE hModule, int resourceID, LPCTSTR resourceType)
	: GLtexture(textureID, hModule, FindResource(hModule, MAKEINTRESOURCE(resourceID), resourceType))
{
}
#else
GLtexture::GLtexture(GLuint textureID, const std::string &imageFilePath)
	: image(nullptr), imageFilePath(imageFilePath), loaded(false), textureID(textureID)
{
}
#endif

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
#if defined(_MSC_VER)
	auto img = stbi_load_from_memory(static_cast<stbi_uc *>(resourceData), static_cast<int>(resourceSize), &w, &h, &c, 0);
#else
	auto ifs = std::ifstream(imageFilePath.c_str(), std::ios::in | std::ios::binary);
	if (!ifs)
		throw std::runtime_error(imageFilePath);
	ifs.seekg(0, std::ios_base::end);
	auto size = ifs.tellg();
	auto data = new stbi_uc[size];
	ifs.seekg(0, std::ios_base::beg);
	ifs.read(reinterpret_cast<char *>(data), size);
	auto img = stbi_load_from_memory(data, static_cast<int>(size), &w, &h, &c, 0);
	delete[] data;
	ifs.close();
#endif
	if (!img) {
		throw std::runtime_error("Can't decompress image from resource");
	}

	image = std::make_shared<std::tuple<void*, int, int>>(img, w, h);
}
