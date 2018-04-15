#include "CParticalSystem.h"
#include "Util.h"

CPartical::CPartical(CCamera& camera, int viewPortWidth, int viewPortHeight)
: CSpriteImage(camera)
{
	mLiftTime      = 4.0f + 2.0f * randf();
	mExistTime     = 0.0f;
	mInitedPos.x   = viewPortWidth  * srandf();
	mInitedPos.y   = viewPortHeight / -2.0f + 20.0f * randf();
	mCurPos        = mInitedPos;
}

CPartical::~CPartical()
{

}

void CPartical::Update(float deltaTime)
{
	static float speed = 10.0f;
	mCurPos.y  += speed * deltaTime;
	mExistTime += deltaTime;
	if (mExistTime > mLiftTime)
	{
		mExistTime    = 0.0f;
		mCurPos       = mInitedPos;
	}
	mTranslatePos = mCurPos;
}

CParticalSystem::CParticalSystem(CCamera& camera)
: mCamera(camera)
, mPTexture(NULL)
{

}

CParticalSystem::~CParticalSystem()
{
	releaseReourses();
}

void CParticalSystem::Init(int viewPortWidth, int viewPortHeight, int count)
{
	releaseReourses();
	CParticleTexture* pTexture = new CParticleTexture();
	pTexture->init(128,128);
	mPTexture = pTexture;
	for (int idx = 0; idx < count; ++idx)
	{
		CPartical* pPartical = new CPartical(mCamera, viewPortWidth, viewPortHeight);
		pPartical->Init(NULL);
		pPartical->mPTexture = mPTexture;
		pPartical->SetRect(0.0f, 0.0f, 50.0f, 50.0f);
		mParticalVec.push_back(pPartical);
	}
}

void CParticalSystem::Update(float deltaTime)
{
	for (int idx= 0; idx < mParticalVec.size(); ++idx)
	{
		CPartical* pPartical = mParticalVec[idx];
		if (pPartical)
		{
			pPartical->Update(deltaTime);
		}
	}
}

void CParticalSystem::Draw()
{
	for (int idx= 0; idx < mParticalVec.size(); ++idx)
	{
		CPartical* pPartical = mParticalVec[idx];
		if (pPartical)
		{
			pPartical->Draw();
		}
	}
}

void CParticalSystem::releaseReourses()
{
	if (mPTexture != NULL)
	{
		delete mPTexture;
		mPTexture = NULL;
	}
	for (int idx= 0; idx < mParticalVec.size(); ++idx)
	{
		CPartical* pPartical = mParticalVec[idx];
		if (pPartical)
		{
			delete pPartical;
			pPartical = NULL;
		}
	}
	mParticalVec.clear();
}