/************************************
* Programmename: run.cpp
* Autor: tki, sbr
* Datum: 14.12.2023
* ***********************************
* Zweck: Implementiert Runmethoden und legt den Spielablauf fest
* *****************************************/

#pragma once
#include <iostream>
#include "snake.h"
#include <fstream>
using namespace std;

Run::Run()
{

	while (true)
	{

		ausgabe.intro();						// ruft Menu auf

		platziereFrucht();					

		while (!spielfeld.getSpielstatistik().getGameover())
		{
			ausgabe.ausgeben(spielfeld.getSchlange(), spielfeld.getFrucht());	// gibt gesamtes Spielfeld aus

			if (ausgabe.getSpielmodus() == 1)
				ausgabe.nutzerSchlangeÄndern();							// fragt Richtung ab für Spielmodus 1

			spielfeld.bewegen(ausgabe.getEingabeChar(), ausgabe.getSpielmodus()); // für Spielmodus 2 ist der EingabeChar ein Leerzeichen und nur ein Platzhalter
																				  // Schange bewegt sich unabhängig vom Modus

			if (spielfeld.getfruchtGegessen())							// platziert Frucht, wenn sie gegessen wird
				platziereFrucht();

		}

		ausgabe.spielEnde(spielfeld.getSpielstatistik().getScore());


		spielfeldZurücksetzen();

	}
}


void Run::platziereFrucht()					// Spielmodus 1: Frucht wird solange neugesetzt, bis sie eine zulässige Pos hat
											// Spielmodus 2: Frucht wird vom Benutzer abgefragt, bis sie eine zulässige Pos hat
{
	if (ausgabe.getSpielmodus() == 2)										// Braucht man für Spielmodus 2, da
	{																		// Frucht noch nicht platziert wurde
		ausgabe.ausgeben(spielfeld.getSchlange(), spielfeld.getFrucht());
	}

	while (!spielfeld.fruchtIstAufZulässigemFeld())
	{
		if (ausgabe.getSpielmodus() == 1)
			spielfeld.setzeFruchtAufZufälligesFeld();

		if (ausgabe.getSpielmodus() == 2)
			spielfeld.setzeFruchtAufFeld(ausgabe.nutzerFruchtÄndernLassen(spielfeld.getGröße()));
	}
	
}



void Run::spielfeldZurücksetzen()								// setzt Variablen zurück, damit nochmal gespielt werden kann
{
	if (ausgabe.getspielBeenden() == 2)
	{
		ausgabe.setSpielmodus(0);
		ausgabe.setName("");
		ausgabe.setSpielstart(false);
	}

	Spielfeld spielfeldneu;										// neues Spielfeld wird erstellt und altes überschrieben
	spielfeld = spielfeldneu;

}

