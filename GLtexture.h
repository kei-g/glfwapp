#pragma once

class GLtexture
{
private:
	// 画像データ
	std::shared_ptr<std::tuple<void*, int, int>> image;

#if defined(_MSC_VER)
	// 読み込み済み
	bool loaded;

	// リソースID
	int resourceID;

	// リソースデータ
	LPVOID resourceData;

	// リソースデータサイズ
	DWORD resourceSize;
#else
	// 画像ファイルパス
	const std::string imageFilePath;

	// 読み込み済み
	bool loaded;
#endif

	// テクスチャID
	GLuint textureID;

private:
#if defined(_MSC_VER)
	// コンストラクタ
	GLtexture(GLuint textureID, HGLOBAL resource, DWORD resourceSize);

	// コンストラクタ
	GLtexture(GLuint textureID, HMODULE hModule, HRSRC resourceInfo);
#endif

	// テクスチャへ画像データを読み込む
	void Load();

public:
#if defined(_MSC_VER)
	// コンストラクタ
	GLtexture(GLuint textureID, HMODULE hModule, int resourceID, LPCTSTR resourceType);
#else
	// コンストラクタ
	GLtexture(GLuint textureID, const std::string &imageFilePath);
#endif

	// デストラクタ
	virtual ~GLtexture();

	// このテクスチャを使う
	void Bind();

	// リソースから画像データを読み込む
	void Read();

#if defined(_MSC_VER)
	// テクスチャを生成する
	template<size_t N>
	static void Generate(std::vector<GLtexture> *textures, HMODULE hModule, const int(&resourceIDs)[N], LPCTSTR resourceType)
	{
		GLuint textureIDs[N] = { 0 };
		glGenTextures(N, textureIDs);
		textures->clear();
		textures->reserve(N);
		for (auto i = size_t(); i < N; i++) {
			textures->emplace_back(textureIDs[i], hModule, resourceIDs[i], resourceType);
		}
	}
#else
	template<size_t N>
	static void Generate(std::vector<GLtexture> *textures, const std::string (&filenames)[N])
	{
		GLuint textureIDs[N] = { 0 };
		glGenTextures(N, textureIDs);
		textures->clear();
		textures->reserve(N);
		for (auto i = size_t(); i < N; i++)
			textures->emplace_back(textureIDs[i], filenames[i]);
	}
#endif
};
