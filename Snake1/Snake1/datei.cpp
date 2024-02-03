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
	ofstream dat_aus("Highscores", ios::app); // Datei Highscores wird ge�ffnet, aber nicht �berschrieben	
	dat_aus << name<<"\t\t\t";
	dat_aus.close();
}

void Datei::scoreSpeichern(int score) // speichert Score in Datei 'Highscores'
{
	ofstream dat_aus("Highscores", ios::app);
	dat_aus << score;
	dat_aus.close();
}

void Datei::highscore�berschreiben(string name,int score)   
{
    ifstream dat_ein("Highscores");     // �ffnet Datei zum Lesen
    ofstream temp_aus("Highscores_temp");      // �ffnet eine tempor�re Datei

    string gespeicherteName;  
    int gespeicherteScore;
    bool nameGefunden = false;

    // durchl�uft Originaldatei
    while (dat_ein >> gespeicherteName >> gespeicherteScore)
    {
        if (gespeicherteName == name)      // vergleicht die gelesenen Namen mit neuem Namen
        {
            nameGefunden = true;

            if (gespeicherteScore < score) // �berpr�ft, ob alter score kleiner ist als neuer score
            {
                temp_aus << name << "\t\t\t" << score << endl;      // �berschreibt alten score in tempor�ren Datei
            }
            else
            {
                temp_aus << gespeicherteName << "\t\t\t" << gespeicherteScore << endl; // beh�lt alten score bei
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
        // Der Name wurde nicht gefunden, also wird ein neuer Name hinzugef�gt
        temp_aus.open("Highscores_temp", ios::app);
        temp_aus << name << "\t\t\t" << score << endl;
        temp_aus.close();
    }

    // Kopiert die aktualisierten Daten zur�ck in die urspr�ngliche Datei
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
	ofstream dat_aus("Spielverlauf", ios::app); // Datei Spielverlauf wird ge�ffnet,aber nicht �berschrieben
	dat_aus << speichern << endl;
	dat_aus.close();
}

void Datei::spielVerlaufLeeren()
{
	ofstream dat_aus("Spielverlauf"); // Datei Spielverlauf wird ge�ffnet und �berschrieben
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
