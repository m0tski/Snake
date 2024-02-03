/************************************
* Programmename: statistik.cpp
* Autor: tki, sbr
* Datum: 14.12.2023
* ***********************************
* Zweck: Implementiert Statistikmethoden
* *****************************************/

#pragma once
#include <iostream>
#include "snake.h"
using namespace std;

void Spielstatistik::setGameover(bool g)			// setzt Gameover auf beliebigen bool Wert
{
	gameover = g;
}


void Spielstatistik::addScore()						// erhöht score um 1
{
	score = score + 1; 
}