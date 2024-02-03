/************************************
* Programmename: ausgabe.cpp
* Autor: tki, sbr
* Datum: 14.12.2023
* ***********************************
* Zweck: Implementiert Ausgabemethoden
* *****************************************/

#pragma once
#include <iostream>
#include "snake.h"


using namespace std;


void Ausgabe::clearConsole()
{
	system("cls");											// leert die Konsole
}

void Ausgabe::intro()
{
	
	cout << "\nWillkommen zu SNAKE!\n";

	while (!spielstart)
	{
		int eingabe;

		cout << "\nMENU:\n(1) Spielregeln\n(2) Spielstart\n\n\n\n(3) Beenden\n";
		cin >> eingabe;

		switch (eingabe)
		{
		case 1:												// Spielregeln
			clearConsole();
			cout << "\nSpielmodus 1: Mensch";
			cout << "\n1. Ziel des Spiels ist die Schlange so lang wie moeglich wachsen zu lassen.";
			cout << "\n2. Die Schlange verlaengert sich, wenn Futter gefressen wird.";
			cout << "\n3. Der Spieler kontrolliert die Schlange ueber 'w' 'a' 's' und 'd'.";
			cout << "\n4. Beim Beruehren von Rand oder Koerper ist das Spiel vorbei.";

			cout << "\n\nSpielmodus 2: Computer";
			cout << "\n1. Der Computer steuert die Schlange.";
			cout << "\n2. Der Spieler platziert eine Frucht mit Angabe von x- und y-Koordinaten.";
			cout << "\n3. Nach dem Platzieren bewegt sich die Schlange zur Frucht und frisst diese.";
			cout << "\n4. Nach dem Fressen verlaengert sich die Schlange und der Spieler platziert eine neue Frucht.";
			cout << "\n5. Beim Beruehren von Rand oder Koerper ist das Spiel vorbei.\n\n";
			pauseConsole();
			clearConsole();

			break;
		case 2:									
			clearConsole();
			cout << "\nGeben Sie Ihren Namen ein: ";
			cin >> name;
			clearConsole();

			spielstart = true;								// spielstart wird auf true gesetzt, um aus der while-Schleife zu kommen
			eingabe = 0;									// setzt für zukünftiges Spielen Eingabe zurück;


			while (true)
			{
				int mode;
				cout << "\nWaehlen Sie ihren Spielmodus aus:\n1) Mensch\n2) Computer \n";
				cin >> mode;
				if (mode == 1 || mode == 2)
				{
					spielmodus = mode;						// Spielmodus wird festgelegt
					clearConsole();
					break;									// Schleifenabbruch

				}
				else										// fängt Falscheingabe ab
				{
					clearConsole();
					cout << "Geben Sie eine passende Zahl ein!\n";
				}
			}

			break;
		case 3: 
			exit(0);										// Beendet das Spiel
			break;
		default:											//fängt Falscheingabe ab
			clearConsole();
			cout << "\nWaehlen Sie eine der Moeglichkeiten aus!\n";
		}
	}
	
}

void Ausgabe::nutzerSchlangeÄndern()						// liest Eingabe (w, a, s, d) zum kontrollieren der Schlange aus
{															// und speichert diese		

	while (true)
	{
		cout << "Lenken Sie die Schlange ('O' Zeichen) mittels w, a, s, d: ";
		cin >> eingabeChar;
		if (eingabeChar == 'w' || eingabeChar == 's' || eingabeChar == 'a' || eingabeChar == 'd')
		{
			datei.spielVerlaufSpeichern(eingabeChar);		// speichert eingegebenen Char in Datei ab
			break;
		}
		else
			cout << "Geben Sie einen der 4 Buchstaben ein!\n";		// fängt Falscheingabe ab 
	}
}

Feld Ausgabe::nutzerFruchtÄndernLassen(int groeße)			// liest Eingabe und platziert an abgefragte Koordinaten ein Feld
{
	cout << "Wo wollen sie Ihre Frucht platzieren ? \n";
	cout << "Geben Sie 2 zulaessige Zahlen zwischen 1 und 10 ein.\n";

		int xPos, yPos;
		cin >> xPos >> yPos;
		Feld eingabeFeld(xPos, yPos);

		return eingabeFeld;									// legt x- und y-Positionen des Feldes (Frucht) fest
}

void Ausgabe::pauseConsole()
{
;
	system("pause");										// Benutzer kann mit beliebiger Tasteneingabe die Schlange vorwärtsbewegen

}

void Ausgabe::spielEnde(int punkte)
{
	clearConsole();

	datei.highscoreÜberschreiben(name,punkte);				// Highscore wird unter dem Namen gespeichert, bzw. überschrieben, falls er schon existiert und höher als der alte ist


	cout << "\nGAME OVER\n\n";
	cout << "Ihre Punkte diese Runde:   " << punkte<<"\n\n";

	cout << "Ihr Highscore : ";							
	datei.highscoreAusgeben(name);							// Gesamthighscore des eingegebenen Namens wird angezeigt

	cout << "\n\nHighscores:\n";
	datei.alleHighscoresAusgeben();							// Alle Highscores werden ausgegeben

	cout << "\nWollen Sie den Spielverlauf einsehen?\n1: Ja\t\t\t2: Nein\n";

	while (true)
	{
		int eingabe;
		cin >> eingabe;

		if (eingabe != 1 && eingabe != 2)
			cout << "\nGeben Sie eine der 2 Zahlen ein!\n";				// Falscheingabe wird abgefangen
		else
		{
			if (eingabe == 1)
				datei.spielVerlaufAusgeben();				// Spielverlauf wird angezeigt
			datei.spielVerlaufLeeren();						// Leert Datei
			break;
		}
	}
	cout << "\n\nWollen Sie nochmal spielen?\n1: Ja\t\t\t2: Beenden\n";

	while (true)
	{
		cin >> spielBeenden;

		if (spielBeenden != 1 && spielBeenden != 2)
			cout << "\nGeben Sie eine der 2 Zahlen ein!\n";
		else
			break;
	}

	clearConsole();
}

void Ausgabe::ausgeben(Schlange schlange, Frucht frucht)			// gibt Feld, Frucht und Schlange aus
{
	clearConsole();
	char charfeld[12][12];

	// Spielfeld wird initialisiert
	for (int i = 1; i < 11; i++)
	{
		for (int j = 1; j < 11; j++)
		{
			charfeld[i][j] = ' ';
		}
	}

	charfeld[frucht.getFruchtFeld().getX()][frucht.getFruchtFeld().getY()] = zeichenFrucht;	// wird von Rahmen überschrieben, wenn (0,0)
	// Für Spielmodus Computer relevant

// Rahmen wird gesetzt
	for (int i = 1; i < 11; i++)
	{
		charfeld[i][0] = zeichenVertikal;							// linke Seite
		charfeld[i][11] = zeichenVertikal;							// rechte Seite
		charfeld[0][i] = zeichenHorizontal;							// obere Seite
		charfeld[11][i] = zeichenHorizontal;						// untere Seite

	}
																	// Ecken:
	charfeld[0][0] = 218;											// links oben
	charfeld[11][11] = 217;											// rechts unten
	charfeld[11][0] = 192;											// links unten
	charfeld[0][11] = 191;											// rechts oben


	Feld* feld = schlange.getFelder();					// Zeiger auf Schlange, um auf die Position der Sschange zuzugreifen

	for (int i = 1; i < schlange.getlaengeSchlange(); i++)
	{
		charfeld[feld[i].getX()][feld[i].getY()] = zeichenSchlange;		// Setzt Zeichen auf jede Position des Schlangenkörpers
	}

	charfeld[schlange.getKopf().getX()][schlange.getKopf().getY()] = zeichenKopf; // Setzt Zeichen auf Schlangenkopf

	cout << 10 << "x" << 10 << " Feld:\n";


	for (int i = 0; i < 12; i++)							// gibt Feld mit Leerzeichen aus (um quadratische Form zu erreichen)
	{
		for (int j = 0; j < 12; j++)
		{
			cout << charfeld[i][j] << ' ';
		}
		cout << endl;
	}



}

void Ausgabe::nutzerFruchtPlatzieren()
{

}

