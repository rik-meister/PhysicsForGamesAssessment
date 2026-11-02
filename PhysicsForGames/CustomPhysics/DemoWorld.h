#pragma once

#include "World.h"

class DemoWorld : public World
{
protected:
	virtual void OnTick() override;
	virtual void OnTickFixed() override;
};