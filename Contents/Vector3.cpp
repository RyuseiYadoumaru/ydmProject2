#include "Vector3.h"
#include "Vector4.h"


myMath::Vector3 myMath::Vector3::Cross(const Vector3& vec1, const Vector3& vec2)
{
	Vector3 ans;
	ans.x = vec1.y * vec2.z - vec1.z * vec2.y;
	ans.y = vec1.z * vec2.x - vec1.x * vec2.z;
	ans.z = vec1.x * vec2.y - vec1.y * vec2.x;
	return Vector3(ans.x, ans.y, ans.z);
}

myMath::Vector3 myMath::Vector3::Larp(const Vector3& startVec3, const Vector3& endVec3, Float32 t)
{
	Vector3 outVec;

	outVec.x = endVec3.x * t + startVec3.x * (1.0f - t);
	outVec.y = endVec3.y * t + startVec3.y * (1.0f - t);
	outVec.z = endVec3.z * t + startVec3.z * (1.0f - t);

    return outVec;
}

myMath::Vector3 myMath::Vector3::Normalize(const Vector3& vec3)
{
	ALIGN16 DirectX::XMVECTOR inv;
	ALIGN16 DirectX::XMVECTOR outv;

	Vector3 inVec = vec3;
	inv = DirectX::XMLoadFloat3(&inVec);
	outv = DirectX::XMVector3Normalize(inv);

	Vector3 out;
	out.Set(outv);
	return out;
}

myMath::Vector3& myMath::Vector3::operator=(const myMath::Vector4& vec4) noexcept
{
	Vector4 vector = vec4;
	x = vector.x;
	y = vector.y;
	z = vector.z;
	return *this;
}
