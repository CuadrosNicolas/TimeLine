

#ifndef joueur_hpp
#define joueur_hpp
#include <stdio.h>
#include <iostream>
#include "mainJoueur.h"
#include "iamanager.h"
#include <vector>

/// Enumération d'un type de joueur comportant un humain ou des IA de différents niveaux
enum joueurType_t{HUMAIN=0,IA_FACILE=1,IA_MOYEN=2,IA_DIFFICILE=3};

/// Déclarartion d'une structure joueur comportant pseudo, frise , type
/// Et un vecteur chronologique
struct joueur_t{
    std::string pseudo;
    mainJoueur_t frise;
    joueurType_t joueurType;
    std::vector<carte_t*> frise_chronologique;///Vector contenant les cartes du joueur dans l'ordre de leurs arrivés
};

/// Liste de joueurs
struct linkedListJoueur_t
{
    joueur_t* joueur;
    linkedListJoueur_t* next;
};
/// Structure définissant le classement d'une liste de joueurs
struct classemenList_t
{
    ///list de chainée de joueur dans l'ordre croissant de leurs classement
    linkedListJoueur_t* first;
    ///nombre de joueur dans le classement
    unsigned int nbJoueur;
    ///chaine de caractère correspondant à la catégorie sur la quelle se base le classement
    std::string categorie;
};
/// Structure définissant un cycle de joueurs
struct cycleJoueur_t
{
    ///pointeur vers le premier élement du cycle
    linkedListJoueur_t* premier;
    ///élément du cycle sur le quel on se situe actuellement
    linkedListJoueur_t* actuel;
    ///premier élément du cycle à l'initialisation
    ///nombre de joueur
    linkedListJoueur_t* initialPremier;
    unsigned int nombreJoueur;
};

/// Affiche un joueur particulier
void afficherJoueur(joueur_t* joueur);

/// Initialise un joueur avec son pseudo, son type
joueur_t* initJoueur(std::string nom,joueurType_t joueurType);
/// Entre un joueur initialisé
joueur_t* entrerJoueur();
/// Réccupère le nombre de cartes d'une certaine catégorie dans la main d'un joueur
int getNbCarte(joueur_t* joueur,std::string categ);
/// Renvoie oui si le joueur à gagner, non sinon
bool joueurGagner (joueur_t* joueur, int maxCartes);

/// Vide la main d'un joueur et nettoye sa frise chronologique
void viderJoueur(joueur_t& joueur);

/// Initialise un cycle de joueurs
cycleJoueur_t initCycle();
///Insert un joueur dans un cycle
bool insertJoueur(cycleJoueur_t& cycle,joueur_t* joueur);
///initialise les différentes catégories pour un joueur (pour les futurs classement)
bool setCategorieForPlayer(cycleJoueur_t& cycle,const categorieList_t& categorieList);
bool suppJoueur (cycleJoueur_t& cycle, int indice); // supprime un joueur d'un cycle
joueur_t* getJoueurByNum(const cycleJoueur_t& cycle,int indice); // renvoie un joueur à partir de son indice
///change la valeur d'actuel en tant que le premier d'un cycle
void setCycleActuel(cycleJoueur_t& cycle);
///reinitialise le sens d'un cycle
void setInitialCycle(cycleJoueur_t& cycle);
///avance l'actuel d'un cycle à son suivant
joueur_t* cycleNext(cycleJoueur_t& cycle);
///affiche un cycle de joueur
void afficherCycleJoueur(const cycleJoueur_t& cycle);
///reinitilise un cycle de joueur
void reInitCycle(cycleJoueur_t& cycle);
///vide un cycle de joueur
void viderCycle(cycleJoueur_t& cycle);
///CLASSEMENT
classemenList_t classementVide();
///construit un classement à partie de la catégorie choisit
classemenList_t makeClassement(const cycleJoueur_t& cycle,std::string categ);
///insert un joueur dans un classement en fonction de son classement
bool insertJoueurByStat(classemenList_t& classement,joueur_t* joueur,std::string categ);
///affiche un classement
void afficherClassement(const classemenList_t& classement);

/// ANIMATION FRISE
void afficherOrdreChrono (joueur_t* joueur);
#endif /* joueur_hpp */
