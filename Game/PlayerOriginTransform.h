#pragma once
#include "GameContents.h"

USING_GAME_SYSTEMS
USING_MY_MATH;

class PlayerOriginTransform : public Script
{
public:
	enum class Type
	{
		Ground,
		ZeroGravity
	};

public:
	void SetType(Type type) noexcept;
	const Vector3& GetSaveRotation() const noexcept { return m_saveRotation; }

public:
	Vector3 m_Position;
	Vector3 m_Rotation;
	Quaternion m_QtRotation;

private:
	virtual void Start() override;
	virtual void Update() override;
	virtual void End() override;

private:
	SharedPtr<Transform> m_transform;
	Type m_type;
	Vector3 m_saveRotation;
	bool m_isStart = false;
public:
	PlayerOriginTransform() : Script(400), m_type(Type::Ground) {}
};

