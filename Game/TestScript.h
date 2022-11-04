#pragma once
#include "Script.h"


class TestScript : public gameSystems::Script
{
public:
	SCRIPT_CLASS;

private:
	virtual void Start() override;
	virtual void Update() override;
	virtual void End() override;
};
