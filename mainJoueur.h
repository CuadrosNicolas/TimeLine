
#ifndef mainJoueur_hpp
#define mainJoueur_hpp
#include <stdio.h>
#include "carte.h"
#include <vector>
#include <map>

///permet gérer le nombre de carte par le catégorie
///La directive de préprocesseur "GENERAL" définit dans "jeu.cpp" permet d'accéder au nombre de carte total
typedef   std::map<std::string, int> classeurDeCategorie_t;

/// Déclarartion d'un élément de l main
struct mainJoueurNoeud_t {
    carte_t* carte;
    mainJoueurNoeud_t* next;

};

/// Déclaration d'une main comportant des éléments de type mainJoueurNoueud_t
struct mainJoueur_t
{
    int nbCarte;
    mainJoueurNoeud_t* carteJoueur;
    classeurDeCategorie_t classeurDeCategorie;

};

/// Déclarartion d'une main vide
mainJoueur_t mainVide();

/// Inséré une carte dans une main
bool insertCarte(carte_t* carte,mainJoueur_t& mainJoueur);

/// Afficher les cartes d'une main
void afficherMain(const mainJoueur_t& mainJoueur);

/// Déclarattion d'une énumération comportant différents intervalles
enum intervalType_t{pasDeBorne,beforeMin,afterMax,between};

struct interval_t{
    mainJoueurNoeud_t* borneMin;
    mainJoueurNoeud_t* borneMax;

    intervalType_t intervalType;
    bool valid;

};

/// Affiche un interval
void afficherInterval(interval_t interval);

/// Identifie l'interval d'une carte dans une main
interval_t identifyInterval(mainJoueur_t& mainJoueur,int date,carte_t* carte);

///renvoit la borne gauche d'un intervalle
int intervalGetMin(const interval_t& i);
///renvoit la borne droite d'un intervalle
int intervalGetMax(const interval_t& i);



/// Compare deux intervals
int compareInterval(interval_t i1,interval_t i2);


/// Vide une main
void viderMain(mainJoueur_t& mainJoueur);
#endif/* mainJoueur_hpp */
