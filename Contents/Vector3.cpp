#include "Vector3.h"

myMath::Vector3 myMath::Vector3::Larp(const Vector3& startVec3, const Vector3& endVec3, Float32 t)
{
	Vector3 outVec;

	outVec.x = endVec3.x * t + startVec3.x * (1.0f - t);
	outVec.y = endVec3.y * t + startVec3.y * (1.0f - t);
	outVec.z = endVec3.z * t + startVec3.z * (1.0f - t);

    return outVec;
}
