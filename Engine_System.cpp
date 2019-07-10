/*  
  Copyright Affonso Amendola 2019

  Fofonso's SDL Engine

  This is part of my SDL Game/Software Engine,

  Distributed under GPLv3, use it to your hearts content,
  just remember the number one rule:

  Be Excellent to Each Other.
*/

#include "Engine_System.hpp"
#include "Engine.hpp"

/*
	TODO:
	Add base engine system functionalities
	Pointer list to other subsystems loaded?
*/

//Base initialization of engine system base class,
//basically only constructs an engine system with a pointer to its parent engine.
Engine_System::Engine_System(Engine * parent_engine)
						:	m_parent_engine(parent_engine)
{}