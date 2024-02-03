/************************************
* Programmename: datei.cpp
* Autor: tki, sbr
* Datum: 14.12.2023
* ***********************************
* Zweck: Implementiert Dateimethoden
* *****************************************/

#pragma once
#include <iostream>
#include "snake.h"
#include <fstream>

using namespace std;


void Datei::nameSpeichern(string name)   // speichert Name in Datei 'Highscores'
{
	ofstream dat_aus("Highscores", ios::app); // Datei Highscores wird geöffnet, aber nicht überschrieben	
	dat_aus << name<<"\t\t\t";
	dat_aus.close();
}

void Datei::scoreSpeichern(int score) // speichert Score in Datei 'Highscores'
{
	ofstream dat_aus("Highscores", ios::app);
	dat_aus << score;
	dat_aus.close();
}

void Datei::highscoreÜberschreiben(string name,int score)   
{
    ifstream dat_ein("Highscores");     // öffnet Datei zum Lesen
    ofstream temp_aus("Highscores_temp");      // öffnet eine temporäre Datei

    string gespeicherteName;  
    int gespeicherteScore;
    bool nameGefunden = false;

    // durchläuft Originaldatei
    while (dat_ein >> gespeicherteName >> gespeicherteScore)
    {
        if (gespeicherteName == name)      // vergleicht die gelesenen Namen mit neuem Namen
        {
            nameGefunden = true;

            if (gespeicherteScore < score) // überprüft, ob alter score kleiner ist als neuer score
            {
                temp_aus << name << "\t\t\t" << score << endl;      // überschreibt alten score in temporären Datei
            }
            else
            {
                temp_aus << gespeicherteName << "\t\t\t" << gespeicherteScore << endl; // behält alten score bei
            }
        }
        else // kopiert vorhandene Daten aus gelesener Datei
        {
            temp_aus << gespeicherteName << "\t\t\t" << gespeicherteScore << endl;
        }
    }

    dat_ein.close();
    temp_aus.close();

    if (!nameGefunden)
    {
        // Der Name wurde nicht gefunden, also wird ein neuer Name hinzugefügt
        temp_aus.open("Highscores_temp", ios::app);
        temp_aus << name << "\t\t\t" << score << endl;
        temp_aus.close();
    }

    // Kopiert die aktualisierten Daten zurück in die ursprüngliche Datei
    ifstream temp_ein("Highscores_temp");
    ofstream dat_aus("Highscores");

    while (temp_ein >> gespeicherteName >> gespeicherteScore)
    {
        dat_aus << gespeicherteName << "\t\t\t" << gespeicherteScore << endl;
    }

    temp_ein.close();
    dat_aus.close();
}

void Datei::highscoreAusgeben(string name)      // gibt highscore des Spielers aus
{
	ifstream dat_ein("Highscores");

	string gespeicherteName;
	int gespeicherteScore;

	while (dat_ein >> gespeicherteName >> gespeicherteScore) 
	{
		if (gespeicherteName == name) 
		{
			cout << gespeicherteScore << endl;
			break;
		}
	}

	dat_ein.close();
}

void Datei::alleHighscoresAusgeben()            // gibt eine aktualisierte Highscoreliste aus
{
	ifstream dat_ein("Highscores");

	string gespeicherteName;
	int gespeicherteScore;
	while (dat_ein >> gespeicherteName>>gespeicherteScore)
		cout << gespeicherteName<<"\t" << gespeicherteScore << "\n";
	dat_ein.close();
}

void Datei::spielVerlaufSpeichern(char speichern)
{
	ofstream dat_aus("Spielverlauf", ios::app); // Datei Spielverlauf wird geöffnet,aber nicht überschrieben
	dat_aus << speichern << endl;
	dat_aus.close();
}

void Datei::spielVerlaufLeeren()
{
	ofstream dat_aus("Spielverlauf"); // Datei Spielverlauf wird geöffnet und überschrieben
	dat_aus.close();
}

void Datei::spielVerlaufAusgeben()
{
    ifstream dat_ein("Spielverlauf");
    string inhalt;

    // Liest den gesamten Inhalt der Datei in einen String
    while (dat_ein >> inhalt)
    {
        cout << inhalt << " ";
    }

    dat_ein.close();
}
