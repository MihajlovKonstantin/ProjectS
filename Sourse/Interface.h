#pragma once
#include "Pch.h"
#include "LibList.h"
class Interface
{
public:
	virtual Math::Matrix GetMatrix();
	virtual KdTexture* GetTexture();
	virtual Math::Rectangle GetRectangle();

	virtual void SetTexture(KdTexture* texture) ;
	virtual void SetScroll(DirectX::XMFLOAT2* scroll) ;

	virtual void Update();
	virtual void Release();
	virtual ~Interface() = default;
};

