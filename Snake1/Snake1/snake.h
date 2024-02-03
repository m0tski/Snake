/************************************
* Programmename: snake.h
* Autor: tki, sbr
* Datum: 14.12.2023
* ***********************************
* Zweck: Definiert die Klassen
* *****************************************/

#pragma once
#include <fstream>
using namespace std;

class Feld
{
private:
	int x = 0;
	int y = 0;

public:

	// Konstruktoren:
	Feld() {};							// Standardkonstruktor
	Feld(int xx, int yy);

	// Zugriffsfunktionen
	int getX() const { return x; }
	int getY() const { return y; }
	void setX(int xx) { x = xx; }
	void setY(int yy) { y = yy; }

};

class Schlange
{
private:

	Feld* felder;				// Pointer auf Felder im Speicherplatz
	int laengeSchlange = 1;

public:

	// Konstruktoren:
	Schlange() {};
	Schlange(int groeße) {};

	// Zugriffsfunktionen:
	Feld getKopf() const { return felder[0]; }
	void setKopf(Feld s) { felder[0] = s; }
	Feld* getFelder() const { return felder; }
	int getlaengeSchlange() const { return laengeSchlange; }

	// weitere Funktionen:
	void setzen(int Groeße);
	void wachsen(Feld neuesFeld);
	void bewegen(Feld neuesFeld);

};

class Frucht
{
private:
	Feld feldFrucht;
public:

	//Standardkonstruktor:
	Frucht() {};

	// Zugriffsfunktionen:
	Feld getFruchtFeld() const { return feldFrucht; }
	void setFrucht(Feld f) { feldFrucht = f; }

	// weitere Funktionen:
	void setzen(int groeße);
	void fruchtAufEingabe(Feld f);				

};

class Datei
{
public:
	Datei() {};
	void nameSpeichern(string name);
	void scoreSpeichern(int score);
	void highscoreAusgeben(string name);
	void alleHighscoresAusgeben();
	void highscoreÜberschreiben(string name,int score);

	void spielVerlaufSpeichern(char speichern);
	void spielVerlaufAusgeben();
	void spielVerlaufLeeren();

};

class Ausgabe
{
private:
	Datei datei;
	bool spielstart = false;
	int spielmodus = 0;
	string name;
	char eingabeChar =' ';		// Eingabe für Spielmodus 1 (w, a, s, d)
	int spielBeenden = 1;

	// Zeichen:
	char zeichenHorizontal = 196;
	char zeichenVertikal = 179;
	char zeichenSchlange = 254;
	char zeichenFrucht = '+';
	char zeichenKopf = 'O';

public:

	// Standardkonstruktor:
	Ausgabe() {};

	// Zugriffsfunktionen:
	int getSpielmodus() const{ return spielmodus; }
	void setSpielmodus(int m) { spielmodus = m; }
	void setName(string s) { name = s; }
	void setSpielstart(bool start) { spielstart = start; }
	char getEingabeChar() const { return eingabeChar; }
	int getspielBeenden() const { return spielBeenden; }
	string getName()const { return name; }
	Datei getDatei()const { return datei; }

	// weitere Funktionen:
	void ausgeben(Schlange schlange, Frucht frucht);					
	void intro();
	void clearConsole();
	void pauseConsole();
	void spielEnde(int highScore);

	// modus 1:
	void nutzerSchlangeÄndern();
	
	// modus 2:
	Feld nutzerFruchtÄndernLassen(int Groeße);
	void nutzerFruchtPlatzieren();

};

class Spielstatistik
{
private:
	bool gameover = false;
	int score = 0;

public:

	// Standardkonstruktor:
	Spielstatistik() {};

	// Zugriffsfunktionen:
	void setGameover(bool g);
	bool getGameover()const { return gameover; }
	int getScore() const { return score; }

	// weitere Funktionen:
	void addScore();

};

class Spielfeld
{
private:
	int groeße = 12;			// legt Spielfeldgröße fest (12 - 2(Rahmen) = 10)
	bool fruchtGegessen = false;
	Schlange schlange;			// Erstellt Schlangen-, Frucht-, Ausgabe- und Spielstatistikobjekte
	Frucht frucht;
	Ausgabe ausgabe;
	Spielstatistik statistik;

public:
	//Standardkonstruktor:
	Spielfeld();

	// Zugriffsfunktionen:
	void setSchlange(Schlange s);
	void setFrucht(Frucht f);
	int getGröße()const { return groeße; }
	bool getfruchtGegessen() const { return fruchtGegessen; }

	Spielstatistik getSpielstatistik()const { return statistik; }		// Ermöglichen Zugriff auf Kopien der Objekte
	Frucht getFrucht()const { return frucht; }
	Schlange getSchlange()const { return schlange; }
	Ausgabe getAusgabe()const { return ausgabe; }

	// weitere Funktionen:	
	bool felderIdentisch(Feld erstesFeld, Feld zweitesFeld);
	bool fruchtIstAufZulässigemFeld();
	void bewegen(char eingabeChar, int spielmodus);
	void setzeGameOverAuf(bool gameOver);
	void posÜberprüfen(Feld snake, Feld fruit);

	// Spielmodus 1:
	Feld schlangenKopfNachEingabe(char z);
	void setzeFruchtAufZufälligesFeld();

	//Spielmodus 2:
	int zufallsZahlGenerieren();
	Feld posBerechnen();
	void setzeFruchtAufFeld(Feld feld);

};

class Run
{
private:
	Spielfeld spielfeld;
	Ausgabe ausgabe;
	ofstream dat_aus;
public:

	// Standardkonstruktor:
	Run();

	// weitere Funktionen:
	void platziereFrucht();
	void spielfeldZurücksetzen();

};

