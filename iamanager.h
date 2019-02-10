#ifndef IAMANAGER_H
#define IAMANAGER_H
#include "mainJoueur.h"
#include "joueur.h"
#include "pileCarte.h"
#include <math.h>
#include <unistd.h>


///structure permettant de manipuler des intervalles de date
enum croisementType_t{AUCUN,CONTIENT,CROISEMENT};
struct intervalDate_t
{
    intervalType_t type;
    int min;
    int max;
    bool valid;
};
///converti un interval en un intervalDate
intervalDate_t convertIntervalToDate(interval_t i1);

///fait la somme de 2 intervalles si ils se croisent
intervalDate_t sommeInterval(const intervalDate_t& i1,const intervalDate_t& i2);

///renvoit si 2 intervalles se croisent (et si oui, comment ils se croisent)
croisementType_t estCroises(const intervalDate_t& i1,const intervalDate_t& i2);

///compare la taille entre 2 intervalles
int compareInterval(const intervalDate_t& i1,const intervalDate_t& i2);  //i1 et i2 ne doivent pas se croiser

///renvoit une valeurs appartenant à un intervalle i
int getMid(const intervalDate_t& i);

//renvoit 1 si i1 plus grand que i2
//renvoit -1 si i2 plus grand que i1 ou que i1 == i2 en taille
int compareSizeInterval(const intervalDate_t& i1,const intervalDate_t& i2);
//renvoit la taille de l'intervalle
int intervalSize(const intervalDate_t& i);

///affiche un intervalDate
void afficherIntervalDate(const intervalDate_t& i);
///structure permettant un ensemble d'interval de date
struct IntervalEnsemble_t
{
    std::vector<intervalDate_t> Between;
    intervalDate_t Left;//Borne invalidant des intervals à gauche
    intervalDate_t Right;//borne invalidant des intervals à droite
};
///initialise un ensemble de date vide
void initIntervalEnsemble(IntervalEnsemble_t& bI);
///rajoute un intervalle à un ensemble
void IntervalEnsembleAdd(IntervalEnsemble_t& bI,intervalDate_t i);
///affiche un ensemble de date
void afficherIntervalEnsemble(const IntervalEnsemble_t& bI);
///vide un ensemble de date
void clearIntervalEnsemble(IntervalEnsemble_t& bI);
///charge une mainJoueur sous la forme d'un ensemble de date
IntervalEnsemble_t loadEnsembleFromMain(const mainJoueur_t& mainJoueur);
///retire des intervalles invalides d'un ensemble d'interval
///ne laissant que des intervalles probables
IntervalEnsemble_t extractBadIntervalFrom(const IntervalEnsemble_t mayBeGood,const IntervalEnsemble_t& badInterval);
///renvoit l'indice dans un vector d'intervalDate qui correspond à la réponse
int getGoodIndice(std::vector<intervalDate_t> reponseVec,int reponse);
///renvoit un entier(correspondant à une date) en fonction d'un interval de date probable
///du niveau de l'IA
///ainsi que le la réponse attendu
int getAnswer(IntervalEnsemble_t INTERVAL,unsigned int ia_level,int reponse);
#endif // IAMANAGER_H
