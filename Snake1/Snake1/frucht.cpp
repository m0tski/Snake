/************************************
* Programmename: frucht.cpp
* Autor: tki, sbr
* Datum: 14.12.2023
* ***********************************
* Zweck: Implementiert Fruchtmethoden
* *****************************************/

#pragma once
#include <iostream>
#include "snake.h"
#include <random>
using namespace std;


void Frucht::setzen(int Groeﬂe)
{
	srand(clock());
	int xPos = rand() % (Groeﬂe - 2) + 1;			// Frucht wird auf Zufallsposition verwiesen
	int yPos = rand() % (Groeﬂe - 2) + 1;


	Feld feld(xPos, yPos);
	feldFrucht = feld;


}

void Frucht::fruchtAufEingabe(Feld f)
{
	feldFrucht = f;
}