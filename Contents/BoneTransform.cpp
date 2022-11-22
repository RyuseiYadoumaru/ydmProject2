#include "BoneTransform.h"
#include "dx11mathutil.h"

BoneTransform::BoneTransform()
{
	m_position = MY_MATH::Vector3(0.0f, 0.0f, 0.0f);
	m_rotation = MY_MATH::Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
}

BoneTransform::BoneTransform(MY_MATH::Vector3 pos, MY_MATH::Quaternion rot)
{
	m_position = pos;
	m_rotation = rot;
}


MY_MATH::Matrix4x4 BoneTransform::GetMatrix() const
{
	MY_MATH::Matrix4x4 translateMat = MY_MATH::Matrix4x4::CreateTranslationMatrix(m_position);
	MY_MATH::Matrix4x4 rotMat = MY_MATH::Matrix4x4::CreateMatrixFromQuaternion(m_rotation);
	MY_MATH::Matrix4x4 result = MY_MATH::Matrix4x4::MatrixMultiply(rotMat, translateMat);
	return result;
}

BoneTransform BoneTransform::Lerp(const BoneTransform& trans1,
	const BoneTransform& trans2,
	Float32 rate)
{
	BoneTransform result;

	// É|ÉWÉVÉáÉìÇÃï‚ä‘ÇãÅÇﬂÇÈ
	result.m_position = MY_MATH::Vector3::Larp(trans1.m_position, trans2.m_position, rate);

	// âÒì]ÇÃï‚ä‘ÇãÅÇﬂÇÈ
	result.m_rotation = MY_MATH::Quaternion::Slerp(trans1.m_rotation, trans2.m_rotation, rate);

	return result;
}