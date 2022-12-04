#pragma once
#include "GameContents.h"

class PlayerMovement;

class PlayerActionCamera : public GAME_SYSTEMS::Script
{
public:
	// �n�ʂ̃J����
	const Float32& GetHorizontalAngle() const noexcept { return m_horizontalAngle; }
	bool IsReset() const noexcept { return m_isReset; }

	// �X�e�[�g�}�V��
	GAME_SYSTEMS::StateMachine& GetStateMachine() noexcept { return m_stateMachine; }

	// �J�����A�N�V����
	const MY_MATH::Vector3& GetLookAt() const noexcept { return m_camera->m_lookAt; }

private:
	constexpr static  Float32 m_limitVerticalAngle = 90.0f;

private:
	// �X�e�[�g�}�V��
	GAME_SYSTEMS::StateMachine m_stateMachine;

	// �v���C���[
	GAME_SYSTEMS::GameObjectPtr m_trackingPlayer = nullptr;

	// �R���|�[�l���g
	SharedPtr<PlayerMovement> m_playerMovement = nullptr;
	SharedPtr<GAME_SYSTEMS::Transform> m_focusTransform = nullptr;
	SharedPtr <GAME_SYSTEMS::Camera> m_camera = nullptr;

	// �A���O��
	MY_MATH::Vector3 m_lookAtOffset;
	Float32 m_heightOffset = 200.0f;
	Float32 m_horizontalRadius = 300.0f;
	Float32 m_verticalRadius = 100.0f;
	Float32 m_horizontalAngle = 0.0f;
	Float32 m_verticalAngle = 0.0f;

	// �J�����A�N�V����
	Float32 m_movevSensitivity = 8.0f;

	// �J�������Z�b�g
	bool m_isReset = false;
	Float32 m_resetTargetAngle = 0.0f;
	Float32 m_resetStartAngle = 0.0f;
	Float32 m_resetTime = 0.25f;
	Float32 m_totalDeltaTime = 0.0f;

private:
	void FocusObject();

private:
	virtual void Start() override;
	virtual void Update() override;
	virtual void End() override;
};
