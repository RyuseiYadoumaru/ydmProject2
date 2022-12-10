#pragma once
#include "GameContents.h"
#include "PlayerActionState.h"

class PlayerMoveAir : public PlayerActionState
{
public:
	PLAYER_ACTION_STATE;

public:
	virtual void EnterState() override;
	virtual void ExitState() override;
	virtual void Update() override;

private:
	void AirMoveMent();

private:

	uInt32 m_counter = 0;
	uInt32 m_hitStopCounter = 0;
	uInt32 m_rotCounter = 0;

	// カメラコンポーネント
	SharedPtr<GAME_SYSTEMS::Camera> m_camera = nullptr;

	MY_MATH::Quaternion m_startAxis;
	MY_MATH::Quaternion m_endAxis;

	MY_MATH::Vector3 m_moveVector;
	MY_MATH::Vector3 m_saveEuler;

	bool m_isRotation = false;

};

