
#ifndef pileCarte_hpp
#define pileCarte_hpp
#include <stdio.h>
#include "carte.h"
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <fstream>

/// Element de la pile de type carte
struct pileCarteNoeud_t{
    carte_t carte;
    pileCarteNoeud_t* next;
};

///Pile de cartes
struct pileCarte_t
{
    pileCarteNoeud_t* sommet;
    int nbCarte;

};
///renvoit une pile vide
pileCarte_t pile_vide();

///renvoit si oui ou non une pile est vide
bool estVide(pileCarte_t& pileCarte);

///empile une carte sur le haut d'une pile p
bool empiler(pileCarte_t& p,carte_t carte);

///vide une pile en effacant son contenu
void viderPile(pileCarte_t& pile);

///depile le premier élément d'une pile p
bool depiler(pileCarte_t& p);

///renvoit la carte au sommet d'une pile
carte_t* getSommet(const pileCarte_t& p);

///charge une pile avec le contenu d'un fichier
///renvoit une liste des différentes catégorie scontenu dans la pile
categorieList_t chargerPile(pileCarte_t& pile,std::string fichier);


///fonction utilse à la manipulation d'une pile
///echange 2 éléments d'un vector
void swapElement(std::vector<carte_t>& vec,int a,int b);

///melange un vector de carte
///randomNumber : nombre d'échange effectué lors du mélange
std::vector<carte_t> melangerCarte(std::vector<carte_t> paquet,int randomNumber);

///renvoit un nombre aléatoire comprit entre 0 et max-1;
int randomNumber(int max);

///initialise les valeurs aléatoires
void initRandom();


///Renvoit si une catégorie existe dans une categorie liste
bool isCategorieExist(const categorieList_t& categorieList,const std::string& categorie);
#endif /* pileCarte_hpp */
