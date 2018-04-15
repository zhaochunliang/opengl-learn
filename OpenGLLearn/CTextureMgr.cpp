#include "CTextureMgr.h"

std::map<const char*, CTexture*> CTextureMgr::mCachedTextures;

CTexture* CTextureMgr::CreateTexture(const char* fileName, bool invertY /* = true */, GLenum wrapMode/* = GL_CLAMP_TO_EDGE */)
{
	CTexture * pTexture = NULL;
	if (mCachedTextures.find(fileName) != mCachedTextures.end())
	{
		pTexture = mCachedTextures[fileName];
	}
	else
	{
		pTexture = new CTexture;
		pTexture->init(fileName, invertY, wrapMode);
		mCachedTextures.insert(std::make_pair<const char*, CTexture*>(fileName, pTexture));
	}
	return pTexture;
}

void CTextureMgr::ClearCachedTextures()
{
	for (std::map<const char*, CTexture*>::iterator it = mCachedTextures.begin(); it != mCachedTextures.end(); ++it)
	{
		if (it->second)
		{
			delete it->second;
			it->second = NULL;
		}
	}
	mCachedTextures.clear();
}