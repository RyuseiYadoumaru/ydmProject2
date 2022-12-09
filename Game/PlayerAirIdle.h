#pragma once
#include "GameContents.h"
#include "PlayerActionState.h"

class PlayerAirIdle : public PlayerActionState
{
public:
	PLAYER_ACTION_STATE;

public:
	virtual void EnterState() override;
	virtual void ExitState() override;
	virtual void Update() override;

private:
	// �n�ʈړ����󒆑ҋ@�p�����[�^
	MY_MATH::Vector3 m_startPosition;
	MY_MATH::Vector3 m_endPosition;
	bool m_isRiseUp = false;


	// �󒆈ړ����󒆑ҋ@�p�����[�^
	MY_MATH::Quaternion m_startQt;
	MY_MATH::Quaternion m_endQt;
	bool m_isIdling = false;

	uInt32 m_counter = 0;
};

