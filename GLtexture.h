#pragma once

class GLtexture
{
private:
	// 読み込み済み
	bool loaded;

	// リソースID
	int resourceID;

	// リソースデータ
	LPVOID resourceData;

	// リソースデータサイズ
	DWORD resourceSize;

	// テクスチャID
	GLuint textureID;

private:
	// コンストラクタ
	GLtexture(GLuint textureID, HGLOBAL resource, DWORD resourceSize);

	// コンストラクタ
	GLtexture(GLuint textureID, HMODULE hModule, HRSRC resourceInfo);

public:
	// コンストラクタ
	GLtexture(GLuint textureID, HMODULE hModule, int resourceID, LPCTSTR resourceType);

	// デストラクタ
	virtual ~GLtexture();

	// このテクスチャを使う
	void Bind();

	// テクスチャを生成する
	template<size_t N>
	static std::vector<GLtexture> Generate(HMODULE hModule, const int(&resourceIDs)[N], LPCTSTR resourceType)
	{
		GLuint textureIDs[N];
		glGenTextures(N, textureIDs);

		auto textures = std::vector<GLtexture>();
		textures.reserve(N);
		for (auto i = size_t(); i < N; i++) {
			textures.emplace_back(textureIDs[i], hModule, resourceIDs[i], resourceType);
		}
		return textures;
	}
};
