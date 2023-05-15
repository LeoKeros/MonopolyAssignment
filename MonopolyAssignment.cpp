// MonopolyAssignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Definitions.h"
#include "CMonopoly.h"

int main()
{
	CMonopoly game;

	//If fail, output message
	if (game.LoadFiles())
	{
		game.Play();
	}
	else
	{
		game.Output(FAILED_TO_LOAD);
	}

	system("pause");
}