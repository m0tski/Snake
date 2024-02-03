/************************************
* Programmename: spielfeld.cpp
* Autor: tki, sbr
* Datum: 14.12.2023
* ***********************************
* Zweck: Implementiert Spielfeldmethoden
* *****************************************/

#pragma once
#include <iostream>
#include "snake.h"
#include <random>
using namespace std;


Spielfeld::Spielfeld()
{
									// Beim Initialisieren des Spielfeldes wird eine Schlange gesetzt
	schlange.setzen(groe�e);

}

void Spielfeld::setSchlange(Schlange s)	
{
	schlange = s;
}

void Spielfeld::setFrucht(Frucht f)
{
	frucht = f;
}

bool Spielfeld::fruchtIstAufZul�ssigemFeld()			// gibt zur�ck, ob Frucht auf einem zul�ssigem Feld ist
{
	// Frucht ist au�erhalb des Spielfeldes:
	if (0 >= frucht.getFruchtFeld().getX() || frucht.getFruchtFeld().getX() >= groe�e-1 || 0 >= frucht.getFruchtFeld().getY() || frucht.getFruchtFeld().getY() >= groe�e - 1)
		return false;

	// Frucht und Schlange sind auf dem selben Feld
	for (int i = 0; i < schlange.getlaengeSchlange(); i++)
	{
		if (felderIdentisch(schlange.getFelder()[i], frucht.getFruchtFeld()))
		{
			return false;
		}
	}

	return true;

}

void Spielfeld::pos�berpr�fen(Feld schlangeFeld, Feld fruchtFeld)		// �berpr�ft Position des Schlangenkopfes
{
	if (felderIdentisch(schlangeFeld, fruchtFeld))		// erh�ht den score, speichert ein + f�r eine gegessene Frucht in einer Datei
	{													// und setzt fruchtgegessen auf true, wenn die Frucht gegessen wird
		if (ausgabe.getSpielmodus() == 1)				// setzt f�r spielergesteuerten Modus Frucht neu, wenn Frucht gegessen wird
			frucht.setzen(groe�e);
		statistik.addScore();
		ausgabe.getDatei().spielVerlaufSpeichern('+');
		fruchtGegessen = true;
	}
	else												// verhindert, dass der K�rper immer l�nger wird
	{
		fruchtGegessen = false;
	}

	// �berpr�ft, ob Schlange au�erhalb vom Spielfeld ist
	if (schlangeFeld.getX() == 0 || schlangeFeld.getY() == 0 || schlangeFeld.getX() == groe�e - 1 || schlangeFeld.getY() == groe�e - 1)
	{
		statistik.setGameover(true);
	}

	// Kontrolle, ob Kopf mit K�rper kollidiert
	for (int i = 1; i < schlange.getlaengeSchlange(); i++)
	{
		if (felderIdentisch(schlange.getFelder()[i], schlange.getKopf()))
			statistik.setGameover(true);
	}

}

bool Spielfeld::felderIdentisch(Feld erstesFeld, Feld zweitesFeld)				// �berpr�ft, ob zwei Felder identisch sind
{
	return erstesFeld.getX() == zweitesFeld.getX() && erstesFeld.getY() == zweitesFeld.getY();
}

void Spielfeld::bewegen(char eingabeChar, int spielmodus)				// wird f�r beide Modi verwendet
{
	Feld neuesSchlangenFeld;

	if (spielmodus == 1)
		neuesSchlangenFeld = schlangenKopfNachEingabe(eingabeChar);		// positioniert Schlange auf eingegebenes Feld ( f�r Spielmodus 1)
	else
	{
		ausgabe.pauseConsole();
		neuesSchlangenFeld = posBerechnen();							// positioniert Schlange auf berechnetem Feld (f�r Spielmodus 2)
	}
	if (fruchtGegessen)													// wenn Frucht gegessen wird, w�chst die Schlange,
	{																	// sonst bewegt sie sich
		schlange.wachsen(neuesSchlangenFeld);
	}
	else
		schlange.bewegen(neuesSchlangenFeld);

	pos�berpr�fen(schlange.getKopf(), frucht.getFruchtFeld());			// Schlangenkopfposition wird �berpr�ft

}

void Spielfeld::setzeGameOverAuf(bool gameOver)
{
	statistik.setGameover(gameOver);
}


// Modus 1:

Feld Spielfeld::schlangenKopfNachEingabe(char z)			// Gibt Feld der Schlange in die angegebene Richtung (z = w, a, s, d) an
{
	Feld kopf = schlange.getKopf();			// Schlangekopf wird auf Feld zugewiesen

	switch (z)								// Schlangenkopf wird je nach Eingabe auf neues Feld verwiesen
	{
		// nach oben:
	case 'w':
		kopf.setX(kopf.getX() - 1);
		break;

		// nach links:
	case 'a':
		kopf.setY(kopf.getY() - 1);
		break;

		// nach unten:
	case 's':
		kopf.setX(kopf.getX() + 1);
		break;

		// nach rechts:
	case 'd':
		kopf.setY(kopf.getY() + 1);
		break;

	default: cout << "FEHLER"; // sollte nie vorkomen
	}

	return kopf; 
}

void Spielfeld::setzeFruchtAufZuf�lligesFeld() // braucht man, weil sonst in Run die Kopie einer Frucht gesetzt wird, 
// und nicht die eigentliche Frucht
{
	frucht.setzen(groe�e);
}

// Modus 2:

Feld Spielfeld::posBerechnen()	// Berechnet neue Position des Schlangenkopfes, je nach dem wo die Frucht platziert wurde
{
	int xPosFrucht = frucht.getFruchtFeld().getX();
	int yPosFrucht = frucht.getFruchtFeld().getY();
	int xPosSchlange = schlange.getKopf().getX();
	int yPosSchlange = schlange.getKopf().getY();



	if (zufallsZahlGenerieren() < 8)		// f�hrt zu Falschverhalten der Schlange
	{
		if (xPosFrucht != xPosSchlange)		// Passt X Koordinate des Schlangenkopfes in Richtung der Frucht an
		{
			if (xPosFrucht < xPosSchlange)
			{
				xPosSchlange = xPosSchlange - 1;
				schlange.getKopf().setX(xPosSchlange);


			}
			if (xPosFrucht > xPosSchlange)
			{
				xPosSchlange = xPosSchlange + 1;
				schlange.getKopf().setX(xPosSchlange);
			}
		}
		else
		{
			if (yPosFrucht != yPosSchlange)		// Passt Y Koordinate des Schlangekopfes in Richtung der Frucht an
			{
				if (yPosFrucht < yPosSchlange)
				{
					yPosSchlange = yPosSchlange - 1;
					schlange.getKopf().setY(yPosSchlange);
				}
				if (yPosFrucht > yPosSchlange)
				{
					yPosSchlange = yPosSchlange + 1;
					schlange.getKopf().setY(yPosSchlange);
				}
			}
		}// wenn x-und y-Koordinaten der Schlange mit den Koordinaten der Frucht
	  //�bereinstimmen, passiert in dieser if else Schleife nichts
	}

	else								// Wenn Schlange Falscheingabe durchf�hrt
	{
		if (xPosFrucht != xPosSchlange)
		{
			if (xPosFrucht < xPosSchlange)
			{
				xPosSchlange = xPosSchlange + 1;
				schlange.getKopf().setX(xPosSchlange);


			}
			if (xPosFrucht > xPosSchlange)
			{
				xPosSchlange = xPosSchlange - 1;
				schlange.getKopf().setX(xPosSchlange);
			}
		}
		else
		{
			if (yPosFrucht != yPosSchlange)
			{
				if (yPosFrucht < yPosSchlange)
				{
					yPosSchlange = yPosSchlange + 1;
					schlange.getKopf().setY(yPosSchlange);
				}
				if (yPosFrucht > yPosSchlange)
				{
					yPosSchlange = yPosSchlange - 1;
					schlange.getKopf().setY(yPosSchlange);
				}
			}
		}
	}

	Feld neuesSchlangenFeld;								// erstellt eine neues Schlangenfeld
	neuesSchlangenFeld.setX(xPosSchlange);
	neuesSchlangenFeld.setY(yPosSchlange);

	return neuesSchlangenFeld;
}

int Spielfeld::zufallsZahlGenerieren()
{
	srand(clock());
	int zufallsZahl= rand() % 10;

	return zufallsZahl; // Eine Zahl zwischen 1 und 10 wird generiert und zur�ckgegeben
}

void Spielfeld::setzeFruchtAufFeld(Feld feld) 
{
	frucht.setFrucht(feld);

		int xPos = feld.getX();
		int yPos = feld.getY();

		if (fruchtIstAufZul�ssigemFeld())
		{
			char charXPos = '0' + xPos;			// wandelt x- und y- Koordinate in char um, welches dann in der Spielverlaufs
			char charYPos = '0' + yPos;			// Datei gespeichert werden kann

			ausgabe.getDatei().spielVerlaufSpeichern(charXPos);
			ausgabe.getDatei().spielVerlaufSpeichern(charYPos);

		}

}






