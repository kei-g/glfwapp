#include "GLtexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLtexture::GLtexture(GLuint textureID, HGLOBAL resource, DWORD resourceSize)
	: loaded(false), resourceData(LockResource(resource)), resourceSize(resourceSize), textureID(textureID)
{
}

GLtexture::GLtexture(GLuint textureID, HMODULE hModule, HRSRC resourceInfo)
	: GLtexture(textureID, LoadResource(hModule, resourceInfo), SizeofResource(hModule, resourceInfo))
{
}

GLtexture::GLtexture(GLuint textureID, HMODULE hModule, int resourceID, LPCTSTR resourceType)
	: GLtexture(textureID, hModule, FindResource(hModule, MAKEINTRESOURCE(resourceID), resourceType))
{
}

GLtexture::~GLtexture()
{
	glDeleteTextures(1, &textureID);
}

void GLtexture::Bind()
{
	if (loaded) {
		glBindTexture(GL_TEXTURE_2D, textureID);
	}
	else {
		stbi_set_flip_vertically_on_load(1);

		auto w = 0, h = 0, c = 0;
		auto img = stbi_load_from_memory(static_cast<stbi_uc *>(resourceData), static_cast<int>(resourceSize), &w, &h, &c, 0);
		if (!img) {
			throw std::exception("Can't decompress image from resource");
		}

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		stbi_image_free(img);

		loaded = true;
	}
}
