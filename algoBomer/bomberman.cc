// Implementatie van klasse Bomberman.

#include <iostream>
#include <fstream>   // om in te lezen
#include <ctime> 
#include "standaard.h"
#include "bomberman.h"

//*************************************************************************

using namespace std;

const int MuurKans = 18;  // 18% kans op een muur
const int KratKans = 32;  // 32% kans op een krat

//*************************************************************************

bool Bomberman::leesin (const char *invoernaam)
{
	ifstream leesIn;
	leesIn.open(invoernaam);
	//cout << invoernaam << endl;
	
	int p = 0; //loopt door array
	int q = 0; //loopt door array
	char car; // leest letters in

	leesIn >> nrrijen; //leest eerste getal in
	leesIn >> nrkolommen; //leest tweede getal in

	car = leesIn.get(); //getsrid of the last endl

	while (! leesIn.eof()) {
		car = leesIn.get();
		if (car == '\n') {
			p++;
			q = 0;
		}
		else {
			bord[p][q] = car;
			q++;
		}
	}//while
	//cout << endl;
	return true;
}  // leesin

//*************************************************************************

int Bomberman::getnrrijen ()
{
  return nrrijen;

}

//*************************************************************************

int Bomberman::getnrkolommen ()
{
  return nrkolommen;

}

//*************************************************************************

char Bomberman::getvakje (int rij, int kolom)
{
	switch (bord[rij][kolom]) { //omdat je returned
	case ('o'): //heb je geen break nodig
		return 'o';
	case ('-'):
		return '-';
	case('x'):
		return 'x';
	case('+'):
		return '+';
	}
return '-';
}  // getvakje

//*************************************************************************

void Bomberman::CopierArray(char copiedBord[MaxDimensie + 1][MaxDimensie + 1], char copieBord[MaxDimensie + 1][MaxDimensie + 1]) {
	for (int p = 0; p <= (nrrijen); p++) { //loopt door 
		for (int q = 0; q <= (nrkolommen); q++) { //de array
			copieBord[p][q] = copiedBord[p][q]; //copieerd de waardes
		}
	}
}

//*************************************************************************

void Bomberman::drukaf()
{
	for (int p = 0; p < nrrijen; p++) { //loopt door de array
		for (int q = 0; q < nrkolommen; q++) { //print de wardes
			cout << bord[p][q] << " "; //uit
		}
		cout << endl;
	}
}  // drukaf



//*************************************************************************

bool Bomberman::checkLegaleZet(int x, int y) {
	if (bord[y][x] == 'x' || bord[y][x] == '+') { //je mag natuurlijk
		return false; //alleen op lege plekken zetten
	} //of op jezelf
	return true;
}

void Bomberman::plaatsbom(int bomkolom, int bomrij)
{
	if (checkLegaleZet(bomkolom, bomrij) == true) {
		int p = 1;
		/*loop alle vier de richtignen uit vanaf de bom
		totdat je een muur of een krat tegen komt, of het uiteinde van het bord berijkt
		als het een krat is haal die dan weg*/
		while (bord[bomrij + p][bomkolom] != '+' && bord[bomrij + p][bomkolom] != 'x' && (bomrij + p) <= nrrijen) {
			p++;
		}
		if (bord[bomrij + p][bomkolom] == '+') {
			bord[bomrij + p][bomkolom] = '-';
		}
		p = -1;
		while (bord[bomrij + p][bomkolom] != '+' && bord[bomrij + p][bomkolom] != 'x' && (bomrij + p) >= 0 ) {
			p--;
		}
		if (bord[bomrij + p][bomkolom] == '+') {
			bord[bomrij + p][bomkolom] = '-';
		}
		p = 1;
		while (bord[bomrij][bomkolom + p] != '+' && bord[bomrij][bomkolom + p] != 'x' && (bomkolom + p) <= nrkolommen) {
			p++;
		}
		if (bord[bomrij][bomkolom + p] == '+') {
			bord[bomrij][bomkolom + p] = '-';
		}
		p = -1;
		while (bord[bomrij][bomkolom + p] != '+' && bord[bomrij][bomkolom + p] != 'x' && (bomkolom + p) >= 0 ) {
			p--;
		}
		if (bord[bomrij][bomkolom + p] == '+') {
			bord[bomrij][bomkolom + p] = '-';
		}
	}
}  // plaatsbom

//*************************************************************************

vector <pair <int, int> > Bomberman::bepaalnietequivalentezetten()
{
	vector <pair <int, int> > zetten; //vector met alle zetten
	vector <pair <int, int> > kisten = waarzijndekisten(); //vector met all kisten
	int waardenvelt[MaxDimensie + 1][MaxDimensie + 1]; //het veld waar waardes in worden opgeslagen
	waardenveltCreatie(kisten, waardenvelt); //waarden veld wordt gevult
	krijgUniek(kisten, waardenvelt); //waardevelt maakt alle unieke zetten een 7
	zetten = krijgUniekeZetten(waardenvelt); //haalt alle posisites van 7ens eruit en maakt er een zet van
	//cout << "pad: " << bepaalPad(2,1,bord) << endl;
		for (int i = 0; i < int(zetten.size()); i++) { // loopt door alle zetten heen
			if (bepaalPad(zetten[i].second, zetten[i].first, bord) == false) { //hier wordt gekeken of de plek haalbaar is
				zetten.erase(zetten.begin() + i); //zo wordt de i omgezet naar een itarator. Deze moet je namelijk gebruiken om het element
				//te verwijderen
				i--; //dan schrijft de grote van de vector namelijk met 1 naar beneden
			}
		}
	return zetten;
}  // bepaalnietequivalentezetten

bool Bomberman::bepaalPad(int x, int y, char cloneBord[MaxDimensie + 1][MaxDimensie + 1]) {
	char copieBord[MaxDimensie + 1][MaxDimensie + 1];
	CopierArray(cloneBord, copieBord);
	if (copieBord[y][x] == 'o') { //als je bij de bomberman bent
		return true; //dan ben je klaar
	}
	copieBord[y][x] = 'A'; //markeerd dat deze plek is geweest
	for (int p = -1; p < 2; p++) { //checkt of er boven of onder plek is
		if ( ((y + p) > -1) && ((y + p) <= nrrijen) ) { //als er plek is
			if (copieBord[y + p][x] == '-') { //loop naar die plek
				if (bepaalPad((x), (y + p), copieBord) == true) { //roep jezelf als als je op die weg
					return true; //ergens bomberman tegen komt dan return je true
				}
			}
			else if (copieBord[y + p][x] == 'o') {
				return true;
			}
		}
	}
	for (int q = -1; q < 2; q++) { //hier doe je het zelfde maar dan 
		if ( ((x + q) > -1) && ((x + q) <= nrkolommen) ) { //voor de zijkanten
			if (copieBord[y][x + q] == '-') { // is er plek loop daar heen
				if (bepaalPad((x + q), (y), copieBord) == true) { //check of dat pad je bij bomberman brengt
					return true; //zo ja return true
				}
			}else if (copieBord[y][x+q] == 'o') {
				return true;
			}
		}
	}
	return false; //dit gebeurt alleen als je alle mogelijkheden hebt gehad, dan is er dus geen weg
}

vector <pair <int, int> > Bomberman::krijgUniekeZetten(int waardenvelt[MaxDimensie + 1][MaxDimensie + 1]) {
	vector < pair <int, int> > zetten;
	
	for (int p = 0; p < nrrijen; p++){ //loop door array
		for (int q = 0; q < nrkolommen; q++) { 
			if (waardenvelt[p][q] == 7) { //zoek de 7vens
				pair <int, int> zet = make_pair(p, q); //maak van die positie een pair
				zetten.push_back(zet); //maak een lijst van die pairs
			}
		}
	}

	return zetten; //return de lijst
}


//*************************************************************************
vector <pair <int, int> > Bomberman::waarzijndekisten() 
{
	vector < pair <int, int> > kisten; //lijst met kisten
	for (int p = 0; p < nrrijen; p++) { //loop door array
		for (int q = 0; q < nrkolommen; q++) { 
			if (bord[p][q] == '+') { //zoek de kisten
				pair <int, int> kist = make_pair(p, q); //maak van die positie een pair
				kisten.push_back(kist); //voeg die positie toe aan dat pair
			}
		}
	}
	return kisten; //return de lijst
}

//*************************************************************************
void Bomberman::waardenveltCreatie(vector <pair<int, int>> kisten,
	int waardenvelt[MaxDimensie + 1][MaxDimensie + 1]) {
	for (int p = 0; p < (MaxDimensie + 1); p++) { //loop door de array
		for (int q = 0; q < (MaxDimensie + 1); q++) {
			if ((p < nrrijen) && (q < nrkolommen)) {
				waardenvelt[p][q] = 0; //zo weet je dat het een lege plek is.
			}
			else {
				waardenvelt[p][q] = -1; //zo weet je dat het velt eigenlijk is opgehouden
			}//ifelse
		}//for
	}//for
	for (int i = 0; i < int(kisten.size()); i++) { //loop door all ekisten heen
		waardenvelt[kisten[i].first][kisten[i].second] = 5;//5 is kist
		loopdoorvelden( waardenvelt, kisten[i], 1, true); //geef alle velde +1 per bom die ze raakt
		loopdoorvelden( waardenvelt, kisten[i], 1, false);
		loopdoorvelden( waardenvelt, kisten[i], -1, true);
		loopdoorvelden( waardenvelt, kisten[i], -1, false); //het maximum is dus 4
	}//for
}


//*************************************************************************
void Bomberman::krijgUniek(vector <pair<int, int>> kisten,
	 int waardenvelt[MaxDimensie + 1][MaxDimensie + 1]) {
	//fix eerst de nummers 3 en 4 want die zijn altijd uniek. bedenk daarna hoe je de 1en aan gaat pakken.
	//de tweetjes worden een ding.-
	fixVierenDrie(waardenvelt);
	for (int i = 0; i < int(kisten.size()); i++) {
		fixEen(kisten[i], waardenvelt);
	}//for
	for (int i = 0; i < int(kisten.size()); i++) {
		fixTwee(kisten[i], waardenvelt);
	}//for
}

//*************************************************************************
void Bomberman::fixVierenDrie(int waardenvelt[MaxDimensie + 1][MaxDimensie + 1]) {
	for (int p = 0; p < nrrijen; p++) {
		for (int q = 0; q < nrkolommen; q++) {
			if ((waardenvelt[p][q] == 3) || (waardenvelt[p][q] == 4)) {
				waardenvelt[p][q] = 7;//7 staat voor uniek
			}
		}
	}
}

//*************************************************************************
bool Bomberman::loopDoorVar(int x, int y, int waardenvelt[MaxDimensie + 1][MaxDimensie + 1], 
	bool horizontaal, int stap, int var, bool eenGezien) {

	if (horizontaal == true) { 
		int p = x + stap;
		while (((waardenvelt[y][p] != 5) && (waardenvelt[y][p] != 6)) && (p <= nrkolommen) && (p >= 0)) {
			if (waardenvelt[y][p] == var) { //als het velt de var is
				if (bepaalPad(p, y, bord) == true) { //moet berijkbaar zijn
					if (eenGezien == false) { 
						waardenvelt[y][p] = 7; //als uniek dan 7
						eenGezien = true;
					}
					else {
						waardenvelt[y][p] = 9; //9 means that it is not unique
					}//else
				}else {
					waardenvelt[y][p] = 9; //9 means that it is not unique
				}
			}
			p = p + stap;
		}
	}else {
		int p = y + stap; 
		while ((waardenvelt[p][x] != 5) && (waardenvelt[p][x] != 6) && (p <= nrrijen) && (p >= 0)) {
			if (waardenvelt[p][x] == var) { 
 				if (bepaalPad(x, p, bord) == true) { //als pad berijkbaar is
					if (eenGezien == false) { 
						waardenvelt[p][x] = 7; //uniek
						eenGezien = true;
					}
					else {
						waardenvelt[p][x] = 9; //9 betekend dat het niet uniek is
					}//elase
				}else {
					waardenvelt[p][x] = 9; //niet uniek
				}
			}
			p = p + stap;
		}
	}
	return eenGezien;
}

//*************************************************************************

void Bomberman::loopDoorTweeSchuin(int x, int y, int waardenvelt[MaxDimensie + 1][MaxDimensie + 1],
	bool horizontaal, int stap) {

	if (horizontaal == true) {
		int p = x + stap; //wordt gebruikt om plek in array te meten
		int t = stap; //wordt gebruikt om afstand te meten
		while (((waardenvelt[y][p] != 5) && (waardenvelt[y][p] != 6)) && (p <= nrkolommen) && (p >= 0)) { //vind twee
			if (waardenvelt[y][p] == 2) { //als je twee vind
				waardenvelt[y][p] = 7; //maak 7
				bepaalSpiegelbeeld(p, y, waardenvelt, horizontaal, t); //zoek spiegelbeeld
			}
			p = p + stap; //verschuif plek in array
			t = t + stap; //afstand moet groter
		}
	}
	else {
		int p = y + stap; //wordt gebruitk om plek in array te weten
		int t = stap; //wordt bruikt om stap te menten
		while ((waardenvelt[p][x] != 5) && (waardenvelt[p][x] != 6) && (p <= nrrijen) && (p >= 0)) { //als gevonden
			if (waardenvelt[p][x] == 2) { 
				waardenvelt[p][x] = 7; //maak uniek
				bepaalSpiegelbeeld( x, p, waardenvelt, horizontaal, t); //zoek spiegelbeeld
			}
			p = p + stap; //verschuif plek in array
			t = t + stap; //afstand moet groter
		}
	}
}

//*************************************************************************

void Bomberman::bepaalSpiegelbeeld(int xBom, int yBom, int waardenvelt[MaxDimensie + 1][MaxDimensie + 1],
	bool horizontaal, int t) {
	int s = 0; //tweede teller voor de afstand
	if (horizontaal == true) { //hier betekend dat het tegeovergestelde
		int p = yBom + 1; //ybom is waar de bom is gelegd
		
		while ((waardenvelt[p][xBom] != 6) && (waardenvelt[p][xBom] != 5) &&(p <= nrrijen) && (p >= 0)) { //vind het andere krat
			s++;//afstand wordt groter
			p++; 
		}//while
		if (waardenvelt[p][xBom] == 5) {//als je het krat vind
			checkBlokade(xBom, p, t, s, horizontaal, waardenvelt); //check of het berijkbaar is in rechte lijnen
		}
		p = yBom - 1; //check het zelfde 
		s = 0; //maar dan voor de andere kant
		while ((waardenvelt[p][xBom] != 6) && (waardenvelt[p][xBom] != 5) && (p <= nrrijen) && (p >= 0)) {
			s--;
			p--;
		}//while
		if (waardenvelt[p][xBom] == 5) {
			checkBlokade(xBom, p, t, s, horizontaal, waardenvelt);
		}
	}else { //het zelfde maar dan voor als de eerste lijn horizonaal is. 
		int p = xBom + 1; //dan is het krat wat we moeten vinden namelijk vertiaal
		s = 0; //afstand
		while ((waardenvelt[yBom][p] != 6) && (waardenvelt[yBom][p] != 5) && (p <= nrkolommen) && (p >= 0)) { //zoek krat
			s++; //afstand groeit
			p++; //stappen groeien
		}//while
		if (waardenvelt[yBom][p] == 5) {
			checkBlokade(p, yBom, t, s, horizontaal, waardenvelt); //check of het berijkbaar is
		}
		p = xBom - 1; //beginpunt 
		s = 0; // afstand
		while ((waardenvelt[yBom][p] != 6) && (waardenvelt[yBom][p] != 5)  && (p <= nrkolommen) && (p >= 0)) { //het zelfde maar dan voor de 
			s--; //andere kant
			p--;
		}//while
		if (waardenvelt[yBom][p] == 5) { //als je het krat vind
			checkBlokade(p, yBom, t, s, horizontaal, waardenvelt); //check de blokade
		}
	}//ifelse
}

//*************************************************************************

bool Bomberman::checkBlokade(int xkist, int ykist, int t, int s, bool horizontaal,
	int waardenvelt[MaxDimensie + 1][MaxDimensie + 1]){
	if (horizontaal == false) { //check of het pad horizontaal is
		if (t > 0) { //check of t positief of negatief is
			for (int p = 1; p <= t; p++) { //loop t
				if ((waardenvelt[ykist - p][xkist] == 6) || (waardenvelt[ykist - p][xkist] == 5)) {
					return false; //als je een muur of kist tegen komt voordat t 0 is dan gaat het fout
				}
			}
		}else { //als t kleiner is dan nul doe je het zelfde maar dan omgekeerd
			for (int p = -1; p >= t; p--) {
				if ((waardenvelt[ykist - p][xkist] == 6) || (waardenvelt[ykist - p][xkist] == 5)) {
					return false;
				}
			}
		}
		if (s > 0) { //de laaste stap maar dan voor s
			for (int p = 1; p < s; p++) {
				if ((waardenvelt[ykist - t][xkist - p] == 6) || (waardenvelt[ykist - t][xkist - p] == 5)) {
					return false;
				}
			}
		}else {
			for (int p = -1; p > s; p--) { //hier stop je 1 van te voren want anders eindig je op je kist
				if ((waardenvelt[ykist - t][xkist - p] == 6) || (waardenvelt[ykist - t][xkist - p] == 5)) {
					return false;
				}
			}
		}
		if (waardenvelt[ykist - t][xkist] == 2) {
			waardenvelt[ykist - t][xkist] = 9; //als daar een twee is wordt die nu niet uniek
		}
	}else { //het zelfe maar dan als het horizontaal is
		if (t > 0) {
			for (int p = 1; p <= t; p++) {
				if ((waardenvelt[ykist][xkist - p] == 6) || (waardenvelt[ykist][xkist - p] == 5)) {
					return false;
				}
			}
		}
		else {
			for (int p = -1; p >= t; p--) {
				if ((waardenvelt[ykist][xkist - p] == 6) || (waardenvelt[ykist][xkist - p] == 5)) {
					return false;
				}
			}
		}
		if (s > 0) {
			for (int p = 1; p < s; p++) {
				if ((waardenvelt[ykist - p][xkist - t] == 6) || (waardenvelt[ykist - p][xkist - t] == 5)) {
					return false;
				}
			}
		}
		else {
			for (int p = -1; p > s; p--) {
				if ((waardenvelt[ykist - p][xkist - t] == 6) || (waardenvelt[ykist - p][xkist - t] == 5)) {
					return false;
				}
			}
		}
		if (waardenvelt[ykist][xkist - t] == 2) {
			waardenvelt[ykist][xkist - t] = 9;
		}
	}
	return true;
}

//*************************************************************************
void Bomberman::fixTwee(pair<int, int> kist, int waardenvelt[MaxDimensie + 1][MaxDimensie + 1]) {
	int y = kist.first; 
	int x = kist.second; 
	loopDoorTwee(x, y, waardenvelt, true, 1); //loopt alle vier de rijen bij twee af
	loopDoorTwee(x, y, waardenvelt, true, -1);
	loopDoorTwee(x, y, waardenvelt, false, 1);
	loopDoorTwee(x, y, waardenvelt, false, -1);
}

//*************************************************************************

void Bomberman::loopDoorTwee(int x, int y, int waardenvelt[MaxDimensie + 1][MaxDimensie + 1],
	bool horizontaal, int stap) {
	bool opEenRij = opEenRijFun(x, y, waardenvelt, stap, horizontaal);
	if (opEenRij == true) { //checked of het op een rij staat
		bool eenGezien = false; //maakt dus de keuze of het schuin lopen moet gebeuren
		loopDoorVar(x, y, waardenvelt, true, 1, 2, eenGezien); //of het recht
		loopDoorVar(x, y, waardenvelt, true, -1, 2, eenGezien);
		loopDoorVar(x, y, waardenvelt, false, 1, 2, eenGezien);
		loopDoorVar(x, y, waardenvelt, false, -1, 2, eenGezien);
	}else {
		loopDoorTweeSchuin(x, y, waardenvelt, true, 1 );
		loopDoorTweeSchuin(x, y, waardenvelt, false, 1);
		loopDoorTweeSchuin(x, y, waardenvelt, true, -1);
		loopDoorTweeSchuin(x, y, waardenvelt, false, -1);
	}
}

//*************************************************************************
bool Bomberman::opEenRijFun(int x, int y, int waardenvelt[MaxDimensie + 1][MaxDimensie + 1], int stap, bool horizontaal) {
	int p; 
	if (horizontaal == true) { //cheked of de kisten op 1 rij zitten
		p = x + stap;
		while (p <= nrkolommen && p >= 0) { //loopt door de rij
			if (waardenvelt[y][p] == 5) { //als kist is gevonden
				return true; //return true
			}else if (waardenvelt[y][p] == 6) { //als je een muur vind
				return false; //dan is het ommogelijk voor ze om of 1 rij te zitten
			}
			p = p + stap;
		}
		return false; //als je niks vind zit er in ieder geval geen kist
	}else {
		p = y + stap; //dito
		while (p <= nrrijen && p >= 0) { 
			if (waardenvelt[p][x] == 5) { 
				return true; 
			}
			else if (waardenvelt[p][x] == 6) {
				return false;
			}
			p = p + stap;
		}
		return false;
	}
}

//*************************************************************************
void Bomberman::fixEen(pair<int, int> kist, int waardenvelt[MaxDimensie + 1][MaxDimensie + 1]) {
	int y = kist.first;
	int x = kist.second;

	//maak dit apparte functie
	bool eenGezien = false;
	eenGezien = loopDoorVar(x, y, waardenvelt, true, 1, 1, eenGezien); //loop door alle 4 rijen
	eenGezien = loopDoorVar(x, y, waardenvelt, true, -1, 1, eenGezien); //bepaal de unieke van 1
	eenGezien = loopDoorVar(x, y, waardenvelt, false, 1, 1, eenGezien); //dit kan er maar 1 zijn per kist
	eenGezien = loopDoorVar(x, y, waardenvelt, false, -1, 1, eenGezien); //vandaar dat eenGezien de functie stopt als hij true is.

}

//*************************************************************************

void Bomberman::loopdoorvelden( 
	int waardevelt[MaxDimensie + 1][MaxDimensie + 1], pair<int, int> kist,
	int looprichting, bool horizontaal) {

	int y = kist.first;
	int x = kist.second;
	int kleinerdan;
	int p;
	if (horizontaal == true) {
		p = x;
		kleinerdan = nrkolommen;
	}else {
		p = y;
		kleinerdan = nrrijen;
	}// ifelse

	for (p = p + looprichting; (p <= kleinerdan + 1) && (p >= 0); p = p + looprichting) { //loop door bord
		if (horizontaal == true) {
			if (bord[y][p] == '-' || bord[y][p] == 'o') { //als het leeg is dan mag daar een bom
				waardevelt[y][p]++; //dan moet het vakje dus ++ omdat die een kist kan oprijmen
			}else if(bord[y][p] == '+') { //als je een kist tegenkomt plaats je de kist
				waardevelt[y][p] = 5; //maar moet je ook weer weg
				return; //want daar stopt de mogelijkheid van de bom
			}else if(bord[y][p] == 'x'){ //als je een muur tegen komt
				waardevelt[y][p] = 6; //plaats de muur
				return; //ga dan weg
			}//ifelse
		}else {
			if (bord[p][x] == '-' || bord[p][x] == 'o') { //als het leeg is
				waardevelt[p][x]++; //++
			}else if (bord[p][x] == '+') { //als het kist is plaats kist
				waardevelt[p][x] = 5;
				return;
			}else if (bord[p][x] == 'x') { //als het muur is plaats muur
				waardevelt[p][x] = 6;
				return;
			}//elseif
		}//ifelse
	}//for
}

//*************************************************************************
int Bomberman::aantalbommen (int &aantalstanden, int &optrij, int &optkolom)
{
	if (actueleScore == 0) {
		highscore = 100; //houd vast wat de kleinste winnende aantal bommen is
	}
	if (actueleScore < highscore) { //als je meer bommen heb geplaatst dan het kleinste aantal bommen, dan hoef je de 
		char copieBord[MaxDimensie + 1][MaxDimensie + 1]; //functie niet verder te doen
		CopierArray(bord, copieBord); //copieer het bord

		if (eindstand() == true) { //als je wint
			highscore = actueleScore; //maak dan alle variable goed
			optkolom = tempkolom; //de laaste keer dat is gewonnen
			optrij = temprij; //is altijd die met het kleinste aantal bommen
		} //dus  je kan dat gewoon zo doen
		else { 
			aantalstanden++; //je checkt een extra stand
 			vector <pair <int, int> > zetten = bepaalnietequivalentezetten(); //krijg de niet equivalente zetten
			for (int i = 0; i < int(zetten.size()); i++) { //loop door die zetten
				plaatsbom(zetten[i].second, zetten[i].first); //plaats daar bommen op het bord
				actueleScore++; //actuele score moet hoger
				if (actueleScore == 1) {
					tempkolom = zetten[i].second; //als een orginele aka een start is 
					temprij = zetten[i].first; //dan moeten de variable gezet worden
				}
				aantalbommen(aantalstanden, optrij, optkolom); //haal de functie op
				CopierArray(copieBord, bord); //herstel het oude bord
				actueleScore--; //actuele score gaat een naar benenen omdat we een naar benden gaan in de boom
			}
		}
	}	
	return highscore;//return de laagste score
}  // aantalbommen

//*************************************************************************

bool Bomberman::eindstand() { 
	for (int p = 0; p < nrrijen; p++) { //loop door array
		for (int q = 0; q < nrkolommen; q++) {
			if (bord[p][q] == '+') { //als je een kist vind
				if (bepaalPad(q, p, bord) == true){ //en hij is berijkbaar
					return false;//return false
				}
			}
		}
	}

	return true; //anders heb je gewonnen kerel
}

//*************************************************************************

int Bomberman::aantalkrattengretig (int &goederij, int &goedekolom)
{
	vector <pair <int, int> > kisten = waarzijndekisten(); //haal de kisten op
	int waardenvelt[MaxDimensie + 1][MaxDimensie + 1]; //maak het waarde 
	waardenveltCreatie(kisten, waardenvelt); //velt
	int maxBommen = 0; //maximale aantal bommen
	for (int p = 0; p < nrrijen; p++) { //loop door
		for (int q = 0; q < nrkolommen; q++) { //array
			if (bepaalPad(q, p, bord) == true) { //bepaal of het berijkbaar is
				if ((waardenvelt[p][q] > maxBommen) && !(waardenvelt[p][q] > 4)) { //zoek de hoogste aantal bommen wat je kan vinden
					maxBommen = waardenvelt[p][q]; //sla  
					goederij = p; //die
					goedekolom = q; //op
				}
			}
		}
	}

  return maxBommen; //return dat

}  // aantalkrattengretig

//*************************************************************************

int Bomberman::aantalbommengretig (int &goederij, int &goedekolom)
{
	if (actueleScore == 0) {
		highscore = 100;//restet
	}
	char copieBord[MaxDimensie + 1][MaxDimensie + 1]; //copieer
	CopierArray(bord, copieBord); //het bord

	if (eindstand() == true) { //bekijk of je wint
		highscore = actueleScore; //als dat zo is sla dan alle scores op
		goedekolom = tempkolom;
		goederij = temprij;
	}
	else {
		int x, y;
		aantalkrattengretig(y, x); //haal het meest opleverenede krat naar boven
			plaatsbom(x, y); //plaats daar een bom
			actueleScore++;
			if (actueleScore == 1) {
				tempkolom = x;
				temprij = y;
			}
		aantalbommengretig( goederij, goedekolom); //doe dit totdat je wint
		CopierArray(copieBord, bord); //reset het bord
		actueleScore--;
	}
  return highscore;
}  // aantalbommengretig


//*************************************************************************

// Schrijf het bord tmpbord met nrrijen rijen en nrkolommen kolommen
// naar een vast uitvoerbestand.
void Bomberman::schrijfbord(char tmpbord[MaxDimensie + 1][MaxDimensie + 1],
	int nrrijen, int nrkolommen)
{
	ofstream fuit;
	int rij, kolom;

	fuit.open("tmpbomberman.txt", ios::out);
	if (fuit.is_open())
	{
		fuit << nrrijen << " " << nrkolommen << endl;
		for (rij = 1; rij <= nrrijen; rij++)
		{
			for (kolom = 1; kolom <= nrkolommen; kolom++)
				fuit << tmpbord[rij][kolom];
			fuit << endl;
		}
		fuit.close();
	}
	else
		cout << "Bestand kon niet geopend worden." << endl;

}  // schrijfbord

//*************************************************************************
//deze functies zijn gecopieerd van de website
//*************************************************************************

// Genereer een random Bombermanbord van dimensie rijen en dimensie
// kolommen, met de speler op een willekeurig leeg vakje.
// Elk vakje heeft MuurKans % kans om een muur te bevatten,
// en KratKans % kans om een krat te bevatten.
void Bomberman::genereerrandombord(int dimensie)
{
	int nrrijen, nrkolommen,
		aantalleeg,   // aantal lege vakjes op het bord
		rij, kolom,
		r,            // random getal
		leegteller;   // telt lege vakjes af, tot we het lege vakje hebben,
					  // waar de speler wordt geplaatst
	char tmpbord[MaxDimensie + 1][MaxDimensie + 1];

	if (integerinbereik("dimensie", dimensie, 1, MaxDimensie)
		&& integerinbereik("MuurKans", MuurKans, 0, 99)
		&& integerinbereik("KratKans", KratKans, 0, 99)
		&& integerinbereik("MuurKans + KratKans", MuurKans + KratKans, 0, 99))
		// dit is weliswaar de preconditie, maar we testen het voor de zekerheid
	{
		nrrijen = dimensie;
		nrkolommen = dimensie;
		do  // genereer een randombord, door voor elk vakje een random invulling
			// te bepalen.
		{
			aantalleeg = 0;
			for (rij = 1; rij <= nrrijen; rij++)
				for (kolom = 1; kolom <= nrkolommen; kolom++)
				{
					r = randomgetal(1, 100);
					if (r <= MuurKans)
						tmpbord[rij][kolom] = Muur;
					else
						if (r <= MuurKans + KratKans)
							tmpbord[rij][kolom] = Krat;
						else
						{
							tmpbord[rij][kolom] = Leeg;
							aantalleeg++;
						}
				}
		} while (aantalleeg == 0);  // met een positieve kans op een leeg vakje
			// (want MuurKans+KratKans<100) zal het een keer voorkomen dat
			// er minstens 1 leeg vakje is

		  // kies nu random een leeg vakje voor de speler
		r = randomgetal(1, aantalleeg);
		leegteller = 0;
		for (rij = 1; rij <= nrrijen && leegteller < r; rij++)
			for (kolom = 1; kolom <= nrkolommen && leegteller < r; kolom++)
			{
				if (tmpbord[rij][kolom] == Leeg)
				{
					leegteller++;
					if (leegteller == r)
						tmpbord[rij][kolom] = Speler;
				}
			}

		schrijfbord(tmpbord, nrrijen, nrkolommen);

	}  // bruikbare waardes

}  // genereerrandombord



void Bomberman::doeExperiment() {
	int gemiddeldeGretig = 0; //slaat gemiddelde gretig op
	int gemiddeldeBruteForce = 0; //slaat gemiddelde bruteforce op


	int x = 0; //houd de deminsies bij
	int bigStonks = 0; //houd bij hoe vaak het gelijk spel was tussen gretig en bruteforce
	bool tienMinuten = false; //houd bij of er al 10 minuten over iets is gedaan

	while ( tienMinuten == false) { //zolang er niet 10 minuten gedaan wordt over een bord
		for (int i = 0; i < 10; i++) { //maak 10 borden
			int t1 = clock(); //neem de tijd op
			genereerrandombord(x + 2); //geneer een bord
			leesin("tmpbomberman.txt"); //haal die op
			//drukaf(); dit is irritant
			int xg, yg; //x gretig, y gretig
			int ag = aantalbommengretig(xg, yg); //aantal gretig
			gemiddeldeGretig = gemiddeldeGretig + ag;
			int xb, yb, as; //xbruteforce, y bruteforce, aantal standen
			int abf = aantalbommen(as, xb, yb); //aantal bruteforce
			gemiddeldeBruteForce = gemiddeldeBruteForce + abf;
			if (abf == ag) {
				bigStonks++;
			}
			if(((clock() - t1) / CLOCKS_PER_SEC) > 600){
				tienMinuten = true;
			}
		}
		x++;
		cout << "voor d is: " << x << " :" << endl;
		cout << "het was gelijk voor: " << bigStonks << "/10 keer" << endl;
		cout << "gemiddelde gretig: " << (gemiddeldeGretig / 10) << endl <<"gemiddelde bruteforce: " << (gemiddeldeBruteForce / 10) << endl;
		bigStonks = 0;
	}
}