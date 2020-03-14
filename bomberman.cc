// Implementatie van klasse Mastermind.

#include <iostream>
#include <fstream>   // om in te lezen
#include "standaard.h"
#include "bomberman.h"

using namespace std;

//*************************************************************************

Bomberman::Bomberman ()
{
  // TODO: implementeer deze functie

}  // default constructor

//*************************************************************************

Bomberman::~Bomberman ()
{
  // TODO: implementeer zo nodig deze functie

}  // destructor

//*************************************************************************

bool Bomberman::leesin (const char *invoernaam)
{
  // TODO: implementeer deze functie

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
  // TODO: implementeer deze functie

  return Leeg;

}  // getvakje

//*************************************************************************

void Bomberman::drukaf ()
{
  // TODO: implementeer deze functie

}  // drukaf

//*************************************************************************

bool Bomberman::eindstand ()
{
  // TODO: implementeer deze functie

  return false;

}  // eindstand

//*************************************************************************

void Bomberman::plaatsbom (int bomrij, int bomkolom)
{
  // TODO: implementeer deze functie

}  // plaatsbom

//*************************************************************************

vector <pair <int,int> > Bomberman::bepaalnietequivalentezetten ()
{ vector <pair <int,int> > zetten;

  // TODO: implementeer deze functie

  return zetten;

}  // bepaalnietequivalentezetten

//*************************************************************************

int Bomberman::aantalbommen (int &aantalstanden, int &optrij, int &optkolom)
{
  // TODO: implementeer deze functie

  return 0;

}  // aantalbommen

//*************************************************************************

int Bomberman::aantalkrattengretig (int &goederij, int &goedekolom)
{
  // TODO: implementeer deze functie

  return 0;

}  // aantalkrattengretig

//*************************************************************************

int Bomberman::aantalbommengretig (int &goederij, int &goedekolom)
{
  // TODO: implementeer deze functie

  return 0;

}  // aantalbommengretig

//*************************************************************************
