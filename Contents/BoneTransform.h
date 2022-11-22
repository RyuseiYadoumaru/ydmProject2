#pragma once
#include <DirectXMath.h>
#include "myMath.h"
#include "std.h"
#include "macro.h"

class BoneTransform
{
public:
	BoneTransform();
	BoneTransform(MY_MATH::Vector3 pos, MY_MATH::Quaternion rot);

public:
	const MY_MATH::Vector3& GetPosition() const noexcept { return m_position; }
	void SetPosition(MY_MATH::Vector3 pos) noexcept { m_position = pos; }

	const MY_MATH::Quaternion& GetRotation() const noexcept { return m_rotation; }
	void SetRotation(MY_MATH::Quaternion rot) noexcept { m_rotation = rot; }

	MY_MATH::Matrix4x4 GetMatrix() const;

public:
	static BoneTransform Lerp(const BoneTransform& trans1,
		const BoneTransform& trans2,
		Float32 rate);

private:
	MY_MATH::Vector3	m_position;
	MY_MATH::Quaternion m_rotation;
};

