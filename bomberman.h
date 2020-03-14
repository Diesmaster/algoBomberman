// Definitie van klasse Bomberman.

#ifndef BombermanHVar  // om te voorkomen dat dit .h bestand meerdere keren
#define BombermanHVar  // wordt ge-include 

#include <vector>   // voor vector
#include <utility>  // voor pair
using namespace std;

const int MaxDimensie = 20;
  // maximaal aantal rijen = maximaal aantal kolommen van het bord
const char Leeg = '-';
const char Krat = '+';
const char Muur = 'x';
const char Speler = 'o';

class Bomberman
{
  public:
    // Default constructor.
    Bomberman ();

    // Destructor.
    ~Bomberman ();

    // Lees een bord in vanuit een door de gebruiker opgegeven
    // tekstbestand.
    // Ga ervanuit dat de waardes van het aantal rijen en het aantal kolommen
    // bovenin het tekstbestand kloppen met de regels daaronder.
    // Controleer wel of het bestand te openen is, en controleer bij inlezen
    // ook of het een geldig bord is (met allemaal geldige karakters
    // en 1 Bomberman).
    // Retourneer:
    //   true: als het bestand te openen was en er inderdaad een geldig bord
    //     is ingelezen.
    //   false: anders
    bool leesin (const char *invoernaam);

    // Return: waarde van membervariabele nrrijen
    int getnrrijen ();

    // Return: waarde van membervariabele nrkolommen
    int getnrkolommen ();

    // Return: de inhoud van het vakje (rij,kolom)
    //   Bij een geldige positie op het bord moet dat dus Leeg, Krat, Muur
    //   of Speler zijn.
    char getvakje (int rij, int kolom);

    // Geen setters voor nrrijen en nrkolommen, omdat die variabelen slechts
    // gezet kunnen worden bij het inlezen van een bord.
    // Geen setter voor vakjes, omdat die slechts worden ingelezen,
    // of veranderen door het plaatsen van een bom.

    // Druk het hele bord af op het scherm.
    void drukaf ();

    // Controleer of het huidige bord een eindstand is, dat wil zeggen:
    // of er nog bereikbare kratten op het bord staan.
    bool eindstand ();

    // Plaats een bom op positie (rij,kolom) en laat hem daar ontploffen.
    // Controleer tevoren nog wel of positie (rij,kolom) op het bord ligt,
    // en of Bomberman daar kan komen.
    // Post:
    // * als er daadwerkelijk een bom geplaatst kon worden, is daar een bom
    //     ontploft, en zijn daardoor (eventueel) kratten weggeblazen;
    //     in dat geval staat Bomberman op die positie
    // * anders is het bord onveranderd
    void plaatsbom (int rij, int kolom);

    // Bepaal de niet-equivalente zetten die mogelijk zijn op het huidige bord.
    // Bij keuze tussen verschillende, equivalente zetten maakt het niet uit
    // welke van deze equivalente zetten gekozen wordt.
    // Ook de volgorde van de niet-equivalente zetten maakt niet uit.
    // Retourneer:
    // * een vector met deze zetten. Elke zet is een pair (rij,kolom)
    //   waar een bom geplaatst kan worden.
    vector <pair <int,int> > bepaalnietequivalentezetten ();

    // Gebruik brute force om, uitgaande van het huidige bord, het minimale
    // aantal benodigde bommen te bepalen om het bord leeg te maken van
    // bereikbare kratten.
    // Het aantal borden dat we hierbij bekijken retourneren we in parameter
    // aantalstanden.
    // De positie voor de eerste bom in de minimale reeks bommen retourneren
    // we in parameters optrij en optkolom.
    // Retourneer:
    // * minimaal aantal bommen dat nodig is om het het bord leeg te maken
    //   van bereikbare kratten.
    // Pre:
    // * aantalstanden = 0
    // Post:
    // * het bord is onveranderd, d.w.z.: er zijn geen kratten definitief
    //   weggeblazen.
    int aantalbommen (int &aantalstanden, int &optrij, int &optkolom);

    // Bepaal, uitgaande van het huidige bord, het maximale aantal kratten
    // dat met een enkele bom kan worden wegblazen.
    // Een positie voor de bom waarmee dit aantal kratten wordt bereikt
    // retourneren we in parameters goederij en goedekolom.
    // Retourneer:
    // * maximaal aantal kratten dat met een enkele bom kan worden
    //   weggeblazen.
    // Post:
    // * het bord is onveranderd, d.w.z.: er zijn geen kratten definitief
    //   weggeblazen.
    int aantalkrattengretig (int &goederij, int &goedekolom);

    // Bepaal, uitgaande van het huidige bord, het aantal bommen om het bord
    // leeg te maken van bereikbare kratten, door herhaaldelijk een gretige
    // zet te doen.
    // De eerste positie waar dan een bom gelegd zou worden, retourneren
    // we in de parameters goederij en goedekolom.
    // Retourneer:
    // * het aantal bommen dat Bomberman op deze manier nodig heeft
    //   om het bord leeg te maken van bereikbare kratten.
    // Post:
    // * het bord is onveranderd, d.w.z.: er zijn geen kratten definitief
    //   weggeblazen.
    int aantalbommengretig (int &goederij, int &goedekolom);

  private:

    // een of andere representatie van het bord

    int  nrrijen,     // aantal rijen van (eigenlijke) bord
         nrkolommen;  // aantal kolommen van (eigenlijke) bord

};

#endif

