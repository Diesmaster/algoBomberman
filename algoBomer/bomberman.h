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

	//deze functie loopt door het waardenvelt heen
	//en haalt alle 7'ens eruit. dit zijn namelijk de
	//unieke zetten.
	vector <pair <int, int> > krijgUniekeZetten(int waardenvelt[MaxDimensie + 1][MaxDimensie + 1]);

	//geeft aan waar de kisten staan voor een gegeven bord
	vector <pair <int, int> > waarzijndekisten();

	//deze functie creeerd het waardenvelt, dus met
	//de hoeveelheid kisten die opgeblazen worden in
	//elk vakje
	void waardenveltCreatie( vector <pair<int, int>> kisten,
		int waardenvelt[MaxDimensie + 1][MaxDimensie + 1]);

	//deze functie returned een vector met alle unieke zetten
	void krijgUniek( vector <pair<int, int>> kisten,
		int waardenvelt[MaxDimensie + 1][MaxDimensie + 1]);
	
	//deze functie zorgt dat alle unieke zetten met waarde 4 en 3 in het
	//waarden velt die uniek zijn worden geselecteerd
	void fixVierenDrie(int waardenvelt[MaxDimensie + 1][MaxDimensie + 1]);

	//deze functie zorgt dat alle unieke zetten met waarde 1 in het waardenvelt
	//worden geselecteerd
	void fixEen( pair<int, int> kist, int waardenvelt[MaxDimensie + 1][MaxDimensie + 1]);

	//deze functie loopt in een rechte lijn en vind alle waardes van waarde var
	//en haalt alle dubbele waardes die dus niet uniek zijn weg
	bool loopDoorVar(int x, int y, int waardenvelt[MaxDimensie + 1][MaxDimensie + 1],
		bool horizontaal, int stap, int var, bool eenGezien);

	//deze funtie loopt door de velden
	//en telt 1 op bij elk velt wat een kist kan raken
	void loopdoorvelden(
		int waardeBord[MaxDimensie + 1][MaxDimensie + 1], pair<int, int> kist,
		int looprichting, bool horizontaal);

	//deze functie zorgt dat alle unieke 2's een 7 krijgen en alle
	//niet unieke een 9 in het waarden velt
	void fixTwee(pair<int, int> kist, int waardenvelt[MaxDimensie + 1][MaxDimensie + 1]);

	//deze functie maakt de keuzen of het gaat om een 2 omdat twee kisten op de zelfde lijn staan
	//of omdat twee lijnen van 2 kisten elkaar ergens of het veld raken
	void loopDoorTwee(int x, int y, int waardenvelt[MaxDimensie + 1][MaxDimensie + 1],
		bool horizontaal, int stap);
	
	//deze functie zorgt dat de 2en die uniek zijn een 7 worden en de andere een 9 krijgen
	//als er twee kisten op de zelfde lijn staan
	bool opEenRijFun(int x, int y, int waardenvelt[MaxDimensie + 1][MaxDimensie + 1], int stap, bool horizontaal);

	//deze functie zorgt dat de 2en die uniek zijn een 7 worden en de andere een 9 krijgen
	//als de twee er staat omdat twee lijnen elkaar op dat punt raken
	void loopDoorTweeSchuin(int x, int y, int waardenvelt[MaxDimensie + 1][MaxDimensie + 1],
		bool horizontaal, int stap);
	//deze functie kijkt of er een spiegel 2 is het geval dat de kisten niet op de zelfde lijn zitten.
	//als dit het geval is krijgt die 2 een 9 omdat die niet uniek is.
	void bepaalSpiegelbeeld(int xBom, int yBom, int waardenvelt[MaxDimensie + 1][MaxDimensie + 1],
		bool horizontaal, int t);
	//als die twee inderdaad niet uniek is moet hij wel bij alle bij de kisten kunnen komen zonder dat er een muur tussen staat.
	//dat is waar de ze functie op let.
	bool checkBlokade(int xkist, int ykist, int t, int s, bool horizontaal,
		int waardenvelt[MaxDimensie + 1][MaxDimensie + 1]);

	//deze fucntie bepaald of er een pad van een punt naar de bomberman mogelijk is.
	bool bepaalPad(int x, int y, char cloneBord[MaxDimensie + 1][MaxDimensie + 1]);

	//deze functie geneerd een random bord, en is geimporteerd van
	//de site van algrotmiek
	void genereerrandombord(int dimensie);

	//deze functie schrijft het random bord weg in een file, en is geimporteerd van
	//de site van algrotmiek
	void schrijfbord(char tmpbord[MaxDimensie + 1][MaxDimensie + 1],
		int nrrijen, int nrkolommen);

	//deze functie checkt of de zet uberhaupt wel mag
	bool checkLegaleZet(int x, int y);

	//deze funcite doet het expiriment
	void doeExperiment();
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

	//deze functie copieerd twee arrays.
	void CopierArray(char copiedBord[MaxDimensie + 1][MaxDimensie + 1], char copieBord[MaxDimensie + 1][MaxDimensie + 1]);

  private:
    // een of andere representatie van het bord
	  char bord[MaxDimensie + 1][MaxDimensie + 1];
	  int highscore = 100; //de miste hoeveelheid bommen die nogdig is geweest tot nu toe om te winnen
	  int actueleScore = 0; //hoe diep de boom op dat moment
	  int temprij, tempkolom; //tijdelijke eerste input
	  int  nrrijen,     // aantal rijen van (eigenlijke) bord
         nrkolommen;  // aantal kolommen van (eigenlijke) bord

};

#endif

