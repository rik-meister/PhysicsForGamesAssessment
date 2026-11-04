#pragma once

#include "World.h"

class DemoWorld : public World
{
public:
	bool bUseScreenWrap = true;

private:
	std::weak_ptr<PhysObject> TestPhysObject;

protected:
	virtual void OnInit() override;
	virtual void OnTick() override;
	virtual void OnTickFixed() override;
};