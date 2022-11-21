#include "Vector3.h"

myMath::Vector3 myMath::Vector3::Larp(const Vector3& startVec3, const Vector3& endVec3, Float32 t)
{
	Vector3 outVec;

	outVec.x = startVec3.x * t + endVec3.x * (1.0f - t);
	outVec.y = startVec3.y * t + endVec3.y * (1.0f - t);
	outVec.z = startVec3.z * t + endVec3.z * (1.0f - t);

    return outVec;
}
