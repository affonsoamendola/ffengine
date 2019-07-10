#pragma once
/*  
  Copyright Affonso Amendola 2019

  Fofonso's SDL Engine

  This is part of my SDL Game/Software Engine,

  Distributed under GPLv3, use it to your hearts content,
  just remember the number one rule:

  Be Excellent to Each Other.
*/
class Engine;

//Base class for engine subsystems, everyone of them should inherit this.
class Engine_System
{
public:
	Engine * m_parent_engine;

	Engine_System(Engine * parent_engine);

	//Should this be virtual?
	void update();
};