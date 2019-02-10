
#include "mainJoueur.h"
using namespace std;
/// Déclaration d'une main vide
mainJoueur_t mainVide()
{

    mainJoueur_t temp = mainJoueur_t{0,nullptr};
    temp.classeurDeCategorie["general"] = 0;
    return temp;
}
///insert une carte dans une main
bool insertCarte(carte_t* carte,mainJoueur_t& mainJoueur)
{
    mainJoueurNoeud_t* mainJoueurNoeud = mainJoueur.carteJoueur;
    ///si la main est vide
    if( mainJoueurNoeud == nullptr)
    {
        mainJoueurNoeud = new mainJoueurNoeud_t{carte,nullptr};
        mainJoueur.carteJoueur = mainJoueurNoeud;

        mainJoueur.nbCarte++;
        mainJoueur.classeurDeCategorie[carte->categorie]++;
        mainJoueur.classeurDeCategorie["general"]++;


        return true;
    }
    else{
        ///Si la carte a une date inférieur à la première de la main
        mainJoueurNoeud_t* temp = mainJoueurNoeud;
        if (compareCarte(carte, temp->carte)==1)
        {
            mainJoueurNoeud_t* temp_2=new mainJoueurNoeud_t{mainJoueurNoeud->carte,mainJoueurNoeud->next}; // declaration nouvelle carte
            mainJoueurNoeud->carte = carte; // ta carte devient premiËre
            mainJoueurNoeud->next = temp_2;   // celle que t'avais devient 2

            mainJoueur.nbCarte++;
            mainJoueur.classeurDeCategorie[carte->categorie]++;
            mainJoueur.classeurDeCategorie["general"]++;

            return true;
        }
        else
        {
            while(temp!=nullptr)
            {
                ///Si on est à la fin de la main
                ///On insert la carte à la fin
                if(temp->next==nullptr)
                {
                    temp->next = new mainJoueurNoeud_t;
                    temp = temp->next;
                    temp->carte = carte;
                    temp->next = nullptr;


                    ///On augmente le nombre de carte de la main
                    mainJoueur.nbCarte++;
                    mainJoueur.classeurDeCategorie[carte->categorie]++;
                    mainJoueur.classeurDeCategorie["general"]++;

                    return true;
                }
                ///Si la carte se situe entre 2 cartes de la main
                else if(compareCarte(carte, temp->next->carte)==1)
                {
                    mainJoueurNoeud_t* temp_2 = new mainJoueurNoeud_t{carte,temp->next};
                    temp->next = temp_2;

                    mainJoueur.nbCarte++;
                    mainJoueur.classeurDeCategorie[carte->categorie]++;
                    mainJoueur.classeurDeCategorie["general"]++;

                    return true;
                }
                ///Sinon on avance dans la main
                else
                temp = temp->next;
            }
        }





    }
    return false;
}

/// Identifie si l'interval correspondant à la date
///entré par le joueur est le bon intervalle
///Si oui on renvoit un interval valide
///Sinn on en renvoit un invalide
interval_t identifyInterval(mainJoueur_t& mainJoueur,int date,carte_t* carte)
{
    interval_t interval;
    mainJoueurNoeud_t* mainJoueurNoeud = mainJoueur.carteJoueur;

    if( mainJoueurNoeud == nullptr)
    {
        interval.intervalType = pasDeBorne;
        interval.borneMin = mainJoueurNoeud;
    }
    else{

        mainJoueurNoeud_t* temp = mainJoueurNoeud;
        if (temp->carte->date >= date)
        {
            interval.intervalType = beforeMin;
            interval.borneMin = temp;
        }
        else
        {
            while(temp!=nullptr) // identifie les intervalles d'une main par rapport à la carte
            {
                if(temp->next==nullptr)
                {
                    interval.intervalType = afterMax;
                    interval.borneMax = temp;

                    break;
                }
                else if(temp->next->carte->date>=date)
                {
                    interval.intervalType = between;
                    interval.borneMax = temp->next;
                    interval.borneMin = temp;
                    break;
                }
                else
                temp = temp->next;
            }
        }

    }

    mainJoueurNoeud_t* temp;
    switch(interval.intervalType)
    {
        case pasDeBorne:
        interval.valid =true;
        mainJoueur.carteJoueur = new mainJoueurNoeud_t{carte,nullptr};
        break;
        case beforeMin:
        if(carte->date <= interval.borneMin->carte->date)
        {
            interval.valid =true;
            temp = new mainJoueurNoeud_t{carte,mainJoueurNoeud};
            mainJoueur.carteJoueur = temp;
        }
        else
        {
            interval.valid =false;
        }
        break;
        case afterMax:
        if(carte->date >= interval.borneMax->carte->date)
        {
            interval.valid =true;
            interval.borneMax->next = new mainJoueurNoeud_t{carte,nullptr};
        }
        else
        {
            interval.valid =false;
        }
        break;
        case between:
        if(carte->date >= interval.borneMin->carte->date && carte->date <= interval.borneMax->carte->date)
        {
            interval.valid =true;
            temp = new mainJoueurNoeud_t{carte,interval.borneMax};
            interval.borneMin->next = temp;
        }
        else
        {
            interval.valid =false;
        }
        break;
        default:
        break;
    }
    if(interval.valid)
    {
        mainJoueur.nbCarte++;
        mainJoueur.classeurDeCategorie[carte->categorie]++;
        mainJoueur.classeurDeCategorie["general"]++;
    }
    return interval;
}

void afficherInterval(interval_t interval)
{
    cout << "INTERVAL :\n";
    switch(interval.intervalType)
    {
        case pasDeBorne:
        cout << "Pas de borne"<<endl;
        break;
        case beforeMin:
        cout << "Avant : "<<interval.borneMin->carte->date<<endl;
        break;
        case afterMax:
        cout << "Apres : "<<interval.borneMax->carte->date<<endl;
        break;
        case between:
        cout << "Entre : "<<interval.borneMin->carte->date <<" et " << interval.borneMax->carte->date<<endl;
        break;


    }
}

void afficherMain(const mainJoueur_t& mainJoueur)
{
    cout << "nombre de carte : "<<mainJoueur.nbCarte<<endl;
    mainJoueurNoeud_t* temp = mainJoueur.carteJoueur;
    while(temp != nullptr)
    {
        afficherCarte(*temp->carte);
        temp = temp->next;
    }
}
int intervalGetMin(const interval_t& i)
{
    if(i.borneMin!=nullptr)
    return i.borneMin->carte->date;
    else
    return 0;
}

int intervalGetMax(const interval_t& i)
{
    if(i.borneMax!=nullptr)
    return i.borneMax->carte->date;
    else
    return 0;
}

/// Vide la main d'un joueur
void viderMain(mainJoueur_t& mainJoueur)
{
    mainJoueurNoeud_t* temp = mainJoueur.carteJoueur;
    while(temp != nullptr)
    {
        if(temp->next == nullptr)
        {
            delete temp;
            temp = nullptr;
        }
        else
        {
            mainJoueurNoeud_t* ancien = temp;
            temp = temp->next;
            delete ancien;
        }
    }
    mainJoueur = mainVide();
}
