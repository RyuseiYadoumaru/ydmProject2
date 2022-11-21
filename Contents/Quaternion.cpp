//*****************************************************************************
//* @file   Quaternion.cpp
//* @brief  クオータニオンクラス
//* @note   オブジェクトの回転指定を管理する
//* 
//* @author YadoumaruRyusei
//* @date   July 2022
//*****************************************************************************
#include <DirectXMath.h>
#include "Quaternion.h"
#include "macro.h"
#include "Matrix4x4.h"

#if USE_DIRECTMATH
#define DIRECTMATH
#else
#define NOT_DIRECTMATH
#endif // USE_DIRECTMATH

//整理
myMath::Quaternion myMath::Quaternion::CreateQuaternion(myMath::Matrix4x4& matrix)
{
	ALIGN16 DirectX::XMMATRIX mtx;
	ALIGN16 DirectX::XMVECTOR qt;
	mtx = matrix.GetXMMatrix();
	qt = DirectX::XMQuaternionRotationMatrix(mtx);

	myMath::Quaternion outQt;
	outQt.Set(qt);

	return outQt;
}


myMath::Quaternion myMath::Quaternion::Multiply(const Quaternion& qt1, const Quaternion& qt2)
{
	Quaternion outQt;

#ifdef DIRECTMATH

	ALIGN16 DirectX::XMVECTOR qtVec1;
	ALIGN16 DirectX::XMVECTOR qtVec2;
	ALIGN16 DirectX::XMVECTOR outQtVec;

	qtVec1 = XMLoadFloat4(&qt1);
	qtVec2 = XMLoadFloat4(&qt2);

	outQtVec = DirectX::XMQuaternionMultiply(qtVec1, qtVec2);

	outQt.Set(outQtVec);

	return outQt;

#else

	outQt.x = qt1.w * qt2.x - qt1.z * qt2.y + qt1.y * qt2.z + qt1.x * qt2.w;
	outQt.y = qt1.z * qt2.x + qt1.w * qt2.y - qt1.x * qt2.z + qt1.y * qt2.w;
	outQt.z = -qt1.y * qt2.x + qt1.x * qt2.y + qt1.w * qt2.z + qt1.z * qt2.w;
	outQt.w = -qt1.x * qt2.x - qt1.y * qt2.y - qt1.z * qt2.z + qt1.w * qt2.w;

#endif 

	return outQt;

}

myMath::Quaternion myMath::Quaternion::Slerp(const Quaternion& startQt, const Quaternion& endQt, Float32 t)
{
	Quaternion outQt;

	ALIGN16 DirectX::XMVECTOR infromqt;
	ALIGN16 DirectX::XMVECTOR intoqt;
	ALIGN16 DirectX::XMVECTOR qt;

	infromqt = DirectX::XMLoadFloat4(&startQt);
	intoqt = DirectX::XMLoadFloat4(&endQt);
	qt = DirectX::XMQuaternionSlerp(infromqt, intoqt, t);

	outQt.Set(qt);
	return outQt;
}

void myMath::Quaternion::CreateRotationAxis(Vector4& axis, Float32 angle)
{
	DirectX::XMVECTOR outQt;
	DirectX::XMVECTOR axisVec;

	/****	軸保存	****/
	m_axis = axis;

	/****	クォータニオン生成	****/
	axisVec = DirectX::XMLoadFloat4(&axis);
	Float32 radian = angle * DirectX::XM_PI / 180.0f;
	outQt = DirectX::XMQuaternionRotationAxis(axisVec, radian);

	DirectX::XMStoreFloat4(this, outQt);
}

void myMath::Quaternion::Normalize()
{
	ALIGN16 DirectX::XMVECTOR qtVec;
	ALIGN16 DirectX::XMVECTOR outQtVec;

	qtVec = this->GetXMVector();
	outQtVec = DirectX::XMQuaternionNormalize(qtVec);
	this->Set(outQtVec);
}


