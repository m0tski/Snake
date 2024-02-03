/************************************
* Programmename: feld.cpp
* Autor: tki, sbr
* Datum: 14.12.2023
* ***********************************
* Zweck: Implementiert Feldmethoden
* *****************************************/

#pragma once
#include <iostream>
#include "snake.h"

using namespace std;


Feld::Feld(int xx, int yy)
{
	x = xx;					// Erstellt ein Feld mit zugewiesenen x- und y-Koordinaten
	y = yy;
}
