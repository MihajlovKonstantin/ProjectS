#include "Pch.h"
#include "Interface.h"
#include "LibList.h"

Math::Matrix Interface::GetMatrix()
{
	return Math::Matrix();
}

KdTexture* Interface::GetTexture()
{
	return nullptr;
}

Math::Rectangle Interface::GetRectangle()
{
	return Math::Rectangle();
}

void Interface::SetTexture(KdTexture* texture)
{
}

void Interface::SetScroll(DirectX::XMFLOAT2* scroll)
{
}

void Interface::Update()
{
}

void Interface::Release()
{
}
