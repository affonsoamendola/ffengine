#pragma once

class Engine;

class Engine_System
{
public:
	Engine * m_parent_engine;

	Engine_System(Engine * parent_engine);

	void update();
};