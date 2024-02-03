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
	schlange.setzen(groeße);

}

void Spielfeld::setSchlange(Schlange s)	
{
	schlange = s;
}

void Spielfeld::setFrucht(Frucht f)
{
	frucht = f;
}

bool Spielfeld::fruchtIstAufZulässigemFeld()			// gibt zurück, ob Frucht auf einem zulässigem Feld ist
{
	// Frucht ist außerhalb des Spielfeldes:
	if (0 >= frucht.getFruchtFeld().getX() || frucht.getFruchtFeld().getX() >= groeße-1 || 0 >= frucht.getFruchtFeld().getY() || frucht.getFruchtFeld().getY() >= groeße - 1)
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

void Spielfeld::posÜberprüfen(Feld schlangeFeld, Feld fruchtFeld)		// Überprüft Position des Schlangenkopfes
{
	if (felderIdentisch(schlangeFeld, fruchtFeld))		// erhöht den score, speichert ein + für eine gegessene Frucht in einer Datei
	{													// und setzt fruchtgegessen auf true, wenn die Frucht gegessen wird
		if (ausgabe.getSpielmodus() == 1)				// setzt für spielergesteuerten Modus Frucht neu, wenn Frucht gegessen wird
			frucht.setzen(groeße);
		statistik.addScore();
		ausgabe.getDatei().spielVerlaufSpeichern('+');
		fruchtGegessen = true;
	}
	else												// verhindert, dass der Körper immer länger wird
	{
		fruchtGegessen = false;
	}

	// Überprüft, ob Schlange außerhalb vom Spielfeld ist
	if (schlangeFeld.getX() == 0 || schlangeFeld.getY() == 0 || schlangeFeld.getX() == groeße - 1 || schlangeFeld.getY() == groeße - 1)
	{
		statistik.setGameover(true);
	}

	// Kontrolle, ob Kopf mit Körper kollidiert
	for (int i = 1; i < schlange.getlaengeSchlange(); i++)
	{
		if (felderIdentisch(schlange.getFelder()[i], schlange.getKopf()))
			statistik.setGameover(true);
	}

}

bool Spielfeld::felderIdentisch(Feld erstesFeld, Feld zweitesFeld)				// Überprüft, ob zwei Felder identisch sind
{
	return erstesFeld.getX() == zweitesFeld.getX() && erstesFeld.getY() == zweitesFeld.getY();
}

void Spielfeld::bewegen(char eingabeChar, int spielmodus)				// wird für beide Modi verwendet
{
	Feld neuesSchlangenFeld;

	if (spielmodus == 1)
		neuesSchlangenFeld = schlangenKopfNachEingabe(eingabeChar);		// positioniert Schlange auf eingegebenes Feld ( für Spielmodus 1)
	else
	{
		ausgabe.pauseConsole();
		neuesSchlangenFeld = posBerechnen();							// positioniert Schlange auf berechnetem Feld (für Spielmodus 2)
	}
	if (fruchtGegessen)													// wenn Frucht gegessen wird, wächst die Schlange,
	{																	// sonst bewegt sie sich
		schlange.wachsen(neuesSchlangenFeld);
	}
	else
		schlange.bewegen(neuesSchlangenFeld);

	posÜberprüfen(schlange.getKopf(), frucht.getFruchtFeld());			// Schlangenkopfposition wird überprüft

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

void Spielfeld::setzeFruchtAufZufälligesFeld() // braucht man, weil sonst in Run die Kopie einer Frucht gesetzt wird, 
// und nicht die eigentliche Frucht
{
	frucht.setzen(groeße);
}

// Modus 2:

Feld Spielfeld::posBerechnen()	// Berechnet neue Position des Schlangenkopfes, je nach dem wo die Frucht platziert wurde
{
	int xPosFrucht = frucht.getFruchtFeld().getX();
	int yPosFrucht = frucht.getFruchtFeld().getY();
	int xPosSchlange = schlange.getKopf().getX();
	int yPosSchlange = schlange.getKopf().getY();



	if (zufallsZahlGenerieren() < 8)		// führt zu Falschverhalten der Schlange
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
	  //übereinstimmen, passiert in dieser if else Schleife nichts
	}

	else								// Wenn Schlange Falscheingabe durchführt
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

	return zufallsZahl; // Eine Zahl zwischen 1 und 10 wird generiert und zurückgegeben
}

void Spielfeld::setzeFruchtAufFeld(Feld feld) 
{
	frucht.setFrucht(feld);

		int xPos = feld.getX();
		int yPos = feld.getY();

		if (fruchtIstAufZulässigemFeld())
		{
			char charXPos = '0' + xPos;			// wandelt x- und y- Koordinate in char um, welches dann in der Spielverlaufs
			char charYPos = '0' + yPos;			// Datei gespeichert werden kann

			ausgabe.getDatei().spielVerlaufSpeichern(charXPos);
			ausgabe.getDatei().spielVerlaufSpeichern(charYPos);

		}

}






