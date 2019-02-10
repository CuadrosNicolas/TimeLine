#ifndef jeu_hpp
#define jeu_hpp

#include <stdio.h>
#include "joueur.h"
#include "pileCarte.h"
#include <cstdlib>

/// Déclaration d'une partie
enum partiType_t{pileVide,maxCarte};
///structure décrivant une partie
///ses paramètres et ses joueurs
struct partie_t
{
    pileCarte_t pileCarte;
    cycleJoueur_t cycleJoueur;
    partiType_t partiType;
    int maxCarteValue;
    ///vector contenant les différentes catégories possibles dans une partie
    std::vector<std::string> categorieVector;
    IntervalEnsemble_t currentBadInterval;
    std::string fichierString;
};
/// On créer une partie vide
partie_t partieVide();
///permet de tester si un fichier est valide
bool testFichier(std::string fichier);
/// Fonctions permettant le fonctionnement du menu et de la partie
void afficherPartie(const partie_t& partie);
/// On affiche le joueur qui doit jouer ainsi que sa carte
int tourHumain();
/// Fonction qui fait jouer une IA
int tourIA(joueur_t* joueur,carte_t* carteEnJeu,partie_t& partie);
///menu permettant de choisir un fichier de carte
void choixFichier(partie_t& partie);
/// Deroulement de la partie
void lancerPartie(partie_t partie);
///menu permettant de rentrer un nouveau joueur dans une partie
void menuEntrerJoueur(partie_t& partie);
/// Menu permettant de changer les parametres d'une partie
void changementParametres (partie_t& partie);

/// On affiche le menu du jeu
void menuJeu(partie_t& partie);
/// Supprime un joueur a partir de son indice
void menuSupprimerJoueur(partie_t& partie);
/// Fonction permettant de choisir le type de classement voulu
void menuClassement(const partie_t& partie);
/// Afficher la frise d'un joueur
void menuAfficherFrise(const partie_t& partie);
///lance le tour d'un joueur
interval_t tourJoueur(joueur_t* joueur,carte_t* carteEnJeu,partie_t& partie);




/// Déroulement du jeu
void launchGame();
#endif /* jeu_hpp */
