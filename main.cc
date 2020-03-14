// Hoofdprogramma voor oplossing voor eerste programmeeropdracht Algoritmiek,
// voorjaar 2020: Bomberman.
//
// Biedt de gebruiker een menustructuur om
// * een Bombermanbord in te lezen, en daarop het spel te spelen,
//   waarbij de gebruiker steeds o.a.
//   - een bom kan plaatsen
//   - kan vragen om de niet-equivalente zetten
//   - kan vragen hoeveel bommen minimaal nodig zijn om het bord leeg
//     te maken van bereikbare kratten
//   - kan vragen naar het maximale aantal kratten dat met 1 bom
//     weggeblazen kan worden
//   - kan vragen hoeveel bommen bij een gretige strategie nodig zouden
//     zijn om het bord leeg te maken van bereikbare kratten
// * experimenten te doen
//
// Naam 1 (studentnummer), Naam 2 (studentnummer)

#include <iostream>
#include <ctime>  // voor clock() en clock_t
#include "standaard.h"
#include "bomberman.h"
using namespace std;
const int MaxBestandsNaamLengte = 30; // maximale lengte van een bestandsnaam

//*************************************************************************

// Controleer of het huidige bord van b1 gelijk is aan een bord
// in een invoerbestand.
void controleerbord (Bomberman *b1)
{ Bomberman *b2;
  char invoernaam[MaxBestandsNaamLengte+1],
       kar1, kar2;
  int nrrijen, nrkolommen,
      nrspelers,   // aantal spelers op bord van b1
      rij, kolom;
  bool OK,   // geen verschillen tussen de borden
       OK2;  // geen ernstige verschillen tussen de borden

  b2 = new Bomberman ();
  cout << endl;
  cout << "Geef de naam van het tekstbestand met het controlebord: ";
  cin >> invoernaam;
  if (b2 -> leesin (invoernaam))  // inlezen gelukt
  { nrrijen = b1 -> getnrrijen ();
    nrkolommen = b1 -> getnrkolommen ();

    if ((nrrijen == b2->getnrrijen()) && (nrkolommen == b2->getnrkolommen()))
      // zelfde dimensies; loop nu alle vakjes af
    { OK = true;
      OK2 = true;
      nrspelers = 0;
      for (rij=1;OK2 && rij<=nrrijen;rij++)
        for (kolom=1;OK2 && kolom<=nrkolommen;kolom++)
        { kar1 = b1 -> getvakje (rij, kolom);
          kar2 = b2 -> getvakje (rij, kolom);
          if (kar1!=kar2)  // oei, niet hetzelfde
          { cout << endl;
            cout << "bord[" << rij << "][" << kolom << "] = " << kar1
                 << ", terwijl controlebord[" << rij << "][" << kolom
                 << "] = " << kar2 << endl;
            OK = false;

              // als enige veschil de positie van de speler is,
              // is dat minder ernstig:
            if ((kar1==Speler && kar2==Leeg) || (kar1==Leeg && kar2==Speler))
              cout << "De speler staat dus op een andere plaats." << endl;
            else  // andere, ernstigere fout
              OK2 = false;

          }  // kar1!=kar2
          
          if (kar1==Speler)
            nrspelers ++;

        }  // for kolom

      if (nrspelers!=1)
      { cout << endl;
        cout << "Het berekende bord bevat " << nrspelers << " spelers.";
        OK2 = false;
      }

      if (OK2)  // hoogstens verkeerde positie van speler
      { cout << endl;
        if (OK)
          cout << "Het berekende bord is in orde." << endl;
        else
          cout << "Afgezien daarvan is het berekende bord in orde." << endl;
      }
        
    }  // zelfde dimensies
    else
    { cout << endl;
      cout << "Het controlebord heeft niet dezelfde dimensies." << endl;
    }

  }  // inlezen gelukt

  delete b2;  // netjes opruimen

}  // controleerbord

//*************************************************************************

// Speel het spel op bord van b1.
// Hierbij krijgt de gebruiker herhaaldelijk de keuze om op het bord
// * een bom te plaatsen op een door hem op te geven positie
//   (al dan niet met controle achteraf)
// * te vragen om een maximale rij van niet-equivalente zetten
// * te vragen om het minimale aantal benodigde bommen om het bord
//   leeg te maken van bereikbare kratten (en daarbij meteen een positie
//   voor een eerste bom te vragen)
// * te vragen om het maximale aantal kratten dat door een enkele
//   krat kan worden weggeblazen (en daarbij meteen een positie te vragen
//   om een bom te plaatsen die dat aantal bereikt)
// * te vragen om het aantal benodigde bommen om het bord leeg te maken
//   van bereikbare kratten door herhaaldelijk op gretige wijze (volgens
//   de vorige optie) bommen te plaatsen
//
// Na iedere geplaatste bom wordt het bord afgedrukt.
//
// Dit alles gaat door
// * totdat er een eindstand is bereikt (alle bereikbare kratten zijn weg)
// * of totdat de gebruiker aangeeft dat hij wil stoppen met het spel
void doespel (Bomberman *b1)
{ int nrrijen, nrkolommen,
      keuze,
      aantalstanden,    // aantal bekeken standen bij aanroep van aantalbommen
      minbommen,        // minimaal aantal bommen om het bord leeg te maken
                        // van bereikbare kratten
      maxkratten,       // maximaal aantal kratten dat met een enkele bom
                        // kan worden weggeblazen
      nrbommen,         // aantal bommen om het bord leeg te maken van
                        // bereikbare kratten door herhaaldelijk op gretige
                        // wijze een bom te plaatsen
      rij, kolom,
      optrij, optkolom,
      goederij, goedekolom;
  vector <pair <int,int> > zetten;
  size_t i;
  clock_t t1, t2;

  nrrijen = b1 -> getnrrijen ();
  nrkolommen = b1 -> getnrkolommen ();
  b1 -> drukaf ();

  keuze = 0;
  while (keuze!=7 && !b1->eindstand())
  {
    cout << endl;
    cout << "1. Een bom plaatsen" << endl;
    cout << "2. Een bom plaatsen met controle" << endl;
    cout << "3. Niet-equivalente zetten bepalen" << endl;
    cout << "4. Minimaal aantal bommen bepalen" << endl;
    cout << "5. Maximaal aantal kratten met 1 bom bepalen" << endl;
    cout << "6. Aantal bommen gretig bepalen" << endl;
    cout << "7. Stoppen met dit spel" << endl;
    cout << endl;
    cout << "Maak een keuze: ";
    cin >> keuze;
    switch (keuze)
    { case 1:
      case 2: cout << endl;
              cout << "Geef de rij voor de bom (1.." << nrrijen << "): ";
              cin >> rij;
              cout << "Geef de kolom voor de bom (1.." << nrkolommen << "): ";
              cin >> kolom;
              b1->plaatsbom (rij, kolom);
              b1->drukaf ();
              if (keuze==2)
                controleerbord (b1);
              break;
      case 3: zetten = b1 -> bepaalnietequivalentezetten ();
              cout << endl;
              cout << "Er zijn " << zetten.size()
                   << " niet-equivalente zetten:" << endl;
              for (i=0;i<zetten.size();i++)
                cout << "(" << zetten[i].first << "," << zetten[i].second
                     << ") ";
              cout << endl;
              break;
      case 4: aantalstanden = 0;
              t1 = clock ();
              minbommen = b1-> aantalbommen (aantalstanden, optrij, optkolom);
              t2 = clock ();
              cout << endl;
              cout << "Minimum aantal bommen = " << minbommen << endl;
              cout << "Eerste bom op positie (" << optrij << "," << optkolom
                   << ")" << endl;
              cout << "We hebben hiervoor " << aantalstanden
                   << " standen bekeken." << endl;
              cout << "Dit kostte " << (t2-t1) << " clock ticks, ofwel "
               << (((double)(t2-t1))/CLOCKS_PER_SEC) << " seconden." << endl;
              break;
      case 5: maxkratten = b1 -> aantalkrattengretig (goederij, goedekolom);
              cout << endl;
              cout << "Maximum aantal kratten = " << maxkratten << endl;
              cout << "Met bom op positie (" << goederij << "," << goedekolom
                   << ")" << endl;
              break;
      case 6: t1 = clock ();
              nrbommen = b1-> aantalbommengretig (goederij, goedekolom);
              t2 = clock ();
              cout << endl;
              cout << "Aantal bommen = " << nrbommen << endl;
              cout << "Eerste bom op positie (" << goederij << "," << goedekolom
                   << ")" << endl;
              cout << "Dit kostte " << (t2-t1) << " clock ticks, ofwel "
               << (((double)(t2-t1))/CLOCKS_PER_SEC) << " seconden." << endl;
              break;
      case 7: break;
      default: cout << endl;
               cout << "Voer een goede keuze in!" << endl;
    }  // switch

  }  // while

  if (b1->eindstand())
  { cout << endl;
    cout << "De huidige stand is een eindstand.\n";
  }

}  // doespel

//*************************************************************************

// Voert de experimenten uit zoals beschreven in de opdracht.
void doeexperimenten ()
{
  // TODO: implementeer deze functie

}  // doeexperimenten

//*************************************************************************

void hoofdmenu ()
{ Bomberman *b1;  // pointer, om makkeijk nieuwe objecten te kunnen maken
                  // en weer weg te gooien
  int keuze;
  char invoernaam[MaxBestandsNaamLengte+1];

  do
  {
    cout << endl;
    cout << "1. Een spel spelen" << endl;
    cout << "2. Experimenten doen" << endl;
    cout << "3. Stoppen" << endl;
    cout << endl;
    cout << "Maak een keuze: ";
    cin >> keuze;
    switch (keuze)
    { case 1: b1 = new Bomberman ();
              cout << "Geef de naam van het tekstbestand met het bord: ";
              cin >> invoernaam;
              if (b1 -> leesin (invoernaam))
                doespel (b1);
              delete b1;  // netjes opruimen
              break;
      case 2: doeexperimenten ();
              break;
      case 3: break;
      default: cout << endl;
               cout << "Voer een goede keuze in!" << endl;
    }

  } while (keuze!=3);

}  // hoofdmenu

//*************************************************************************
  
int main ()
{
  hoofdmenu ();

  return 0;

}
