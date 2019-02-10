#ifndef carte_hpp
#define carte_hpp
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>

///type de donnée contenant les différentes catégories existantes pour les cartes
typedef std::vector<std::string> categorieList_t;
struct carte_t
{
    std::string nom;
    int date;
    std::string categorie;
};

///charge une carte à partir d'une chaine de caractère
carte_t getCarteFromString(std::string s);

///affiche une carte
void afficherCarte(carte_t carte);

///affiche une carte sans afficher sa date
void afficherAnonyme (carte_t* carte);

///compare la date entre 2 carte
///renvoit 1 si carteB > carteA
///renvoit -1 si carteB < carteA
///renvoit 0 si carteB==carteA
int compareCarte(carte_t* carteA, carte_t* carteB );
#endif /* carte_hpp */
