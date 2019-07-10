#include <iostream>

#include "Engine.hpp"

using namespace std;

//Main class, called on game start.
int main()
{
	//Creates engine.
	Engine engine;

	//While running, update engine and engine cascades updating every subsystem, 
	//final part of Engine.update() calls Render() which draws everything to screen.
	while(engine.m_is_running)
	{
		engine.update();
	}

	//If here, m_is_running stopped being true, so left the game.
	cout << "Quitting..." << endl;

	return 0;
}