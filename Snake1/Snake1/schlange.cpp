/************************************
* Programmename: schlange.cpp
* Autor: tki, sbr
* Datum: 14.12.2023
* ***********************************
* Zweck: Implementiert Schlangenmethoden
* *****************************************/

#pragma once
#include <iostream>
#include "snake.h"
#include <random>
using namespace std;


void Schlange::setzen(int Groe�e)
{
	srand(clock());
	int xPos = rand() % (Groe�e - 2) + 1;		// Schlange wird auf Zufallsposition verwiesen
	int yPos = rand() % (Groe�e - 2) + 1;

	Feld feld(xPos, yPos);
	felder = new Feld[1];					// legt Array an Felder der Gr��e 1 an
	felder[0] = feld;

}

void Schlange::wachsen(Feld kopf)
{
	laengeSchlange++;		// L�nge der Schlange erh�ht sich


	Feld* neueFelder;							// Pointer auf neues Felder Array
	neueFelder = new Feld[laengeSchlange];		// Felderl�nge mit neuer Gr��e anlegen

	neueFelder[0] = kopf;						// Kopf bekommt neues Feld

	for (int i = 1; i < laengeSchlange; i++)
	{
		neueFelder[i] = felder[i - 1];				// K�rper in neues Array kopieren
	}

	delete[] felder;			// l�scht alte felder/ gibt Speicherplatz frei

	felder = neueFelder;		//�berschreibt altes Array
}

void Schlange::bewegen(Feld neuesFeld)				// Schlange bewegt sich in Richtung des neuen Feldes
{
	for (int i = laengeSchlange-1; i>0; i--)		// Z�hlt von Hinten durch
	{
		felder[i] = felder[i - 1];					// Jedes Schlangenglied wird auf das Feld vom berherigen verwiesen
	}

	felder[0] = neuesFeld;							// Schlangenkopf wird auf neues Feld platziert
}