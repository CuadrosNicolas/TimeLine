
#include "carte.h"
using namespace std;
categorieList_t categorieReference;

/// On réccupère le fichier et on le convertit en cartes
carte_t getCarteFromString(string s)
{
    carte_t out;
    int date;
    date = -1;
    string nom;
    string categorie;

    string temp="";
    int compt=0;

    for(unsigned int i=0; i<s.size(); i++)
    {
        if(s[i]!= '\t')
        {

            temp.push_back(s[i]);
        }
        else
        {
            compt++;
            if (compt==1)
            {
                istringstream convert(temp);
                convert >> date;
                temp="";
            }
            else if (compt==2)
            {
                nom=temp;
                temp="";
            }
            else if(compt==3)
            break;
        }
    }
    categorie=temp;

    out.nom=nom;
    out.date = date;
    out.categorie=categorie;


    return out;
}

/// On affiche les cartes avec tutes les informations
void afficherCarte(carte_t carte)
{
    cout << carte.nom << " ("<<carte.categorie<<") : " << carte.date<<endl;
}

///On afficher les cartes à l'exception des dates
void afficherAnonyme (carte_t* carte)
{
    cout << carte->nom << " ("<<carte->categorie<<") : ???" <<endl;
}

///On compare les dates de deux cartes différentes
int compareCarte(carte_t* carteA, carte_t* carteB)
{
    if(carteB->date>carteA->date)
    return 1;
    else if(carteB->date<carteA->date)
    return -1;
    else
    return 0;
}
