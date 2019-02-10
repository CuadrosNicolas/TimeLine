
#include "joueur.h"
using namespace std;

/// Fonction retournant un joueur humain comprenant l'initialisation de son pseudo
joueur_t* entrerJoueur()
{
    std::string pseudo="";
    int choixType = 0;
    joueurType_t joueurType=HUMAIN;
    cout << "Entrez on pseudo : ";
    cin>>pseudo;
    while(choixType <=0 || choixType>4)
    {

    cout << "Choisissez son type : \n";
    cout << "\t(1) HUMAIN\n";
    cout << "\t(2) Ordinateur facile\n";
    cout << "\t(3) Ordinateur Moyen\n";
    cout << "\t(4) Ordinateur Difficile\n";
    cout << "Votre choix : ";
    cin>>choixType;
        switch(choixType)
        {
        case 2:
            joueurType=IA_FACILE;
            break;
        case 3:
            joueurType=IA_MOYEN;
            break;
        case 4:
            joueurType=IA_DIFFICILE;
            break;
        default:
            break;
        }

    }
    return initJoueur(pseudo,joueurType);
}

/// Fonction permettant d'initialiser un joueur qui peut etre humain ou IA
joueur_t* initJoueur(std::string nom,joueurType_t joueurType)
{
    joueur_t* out = new joueur_t;
    out->pseudo = nom;
    out->frise = mainVide();
    out->joueurType = joueurType;

    return out;
}

/// Affiche un joueur initialité
void afficherJoueur(joueur_t* joueur)
{
    cout <<"nom : "<< joueur->pseudo<<endl;
    cout << "TYPE : ";
    if(joueur->joueurType == HUMAIN)
    {
        cout << "HUMAIN\n";
    }
    else
    {
        switch(joueur->joueurType)
        {
        case IA_FACILE:
            cout << "Ordinateur Facile\n";
            break;
        case IA_MOYEN:
            cout << "Ordinateur Moyen\n";
            break;
        case IA_DIFFICILE:
            cout << "Ordinateur Difficile\n";
            break;
        default:
            break;
        }
    }
    afficherMain(joueur->frise);
}

/// Retourne le nombre de cartes dans une catégorie
int getNbCarte( joueur_t* joueur,string categ)
{
    int out = joueur->frise.classeurDeCategorie[categ];
    return out;
}

///Initialise un cycle vde
cycleJoueur_t initCycle()
{
    return cycleJoueur_t{nullptr,nullptr,nullptr,0};
}

bool setCategorieForPlayer(cycleJoueur_t& cycle,const categorieList_t& categorieList)
{
    linkedListJoueur_t* temp = cycle.premier;
    do
    {
        for(int i =0;i<categorieList.size();i++)
        temp->joueur->frise.classeurDeCategorie[categorieList[i]] = 0;
        temp = temp->next;
    }
    while(temp!=cycle.premier);
    return true;
}
///Insert un joueur dans un cycle et augmente le nombre de joueurs du cycle
bool insertJoueur(cycleJoueur_t& cycle,joueur_t* joueur)
{
    if(cycle.premier == nullptr)
    {
        cycle.premier = new linkedListJoueur_t{joueur,nullptr};
        cycle.premier->next = cycle.premier;
        cycle.actuel = cycle.premier;
        cycle.nombreJoueur=1;
        cycle.initialPremier = cycle.premier;
        return true;
    }
    else
    {
        linkedListJoueur_t* temp = cycle.premier;
        while(temp->next != cycle.premier)
        temp = temp->next;
        temp->next = new linkedListJoueur_t{joueur,cycle.premier};
        cycle.nombreJoueur++;
        return true;
    }
    return false;
}
/// Supprime un joueur dans un cycle et décrémente le nombre de joueurs du cycle
bool suppJoueur(cycleJoueur_t& cycle, int indice)
{
    if(indice==1)
    {
        linkedListJoueur_t* temp = cycle.premier;
        cycle.initialPremier = temp->next;
        linkedListJoueur_t* tempJoueurSupp = cycle.premier;
        while(temp->next != cycle.premier)
        temp = temp->next;
        temp->next = cycle.premier->next;
        delete tempJoueurSupp;
        cycle.nombreJoueur--;
        cycle.premier = temp->next;
        return true;
    }
    else if (indice> 1 &&indice<=cycle.nombreJoueur){
        int compt=1;
        linkedListJoueur_t* temp = cycle.premier;
        linkedListJoueur_t* tempJoueurSupp;
        while(compt+1 < indice){
            temp = temp->next;
            compt++;
        }
        tempJoueurSupp =temp->next;
        temp->next = temp->next->next;
        delete tempJoueurSupp;
        cycle.nombreJoueur--;
        return true;
    }
    else
    {
        return false;
    }

}

/// Vide la main d'un joueur et nettoye sa frise
void viderJoueur(joueur_t& joueur)
{
    viderMain(joueur.frise);
    joueur.frise_chronologique.clear();
}

/// Retourne un joueur à partir de son indice
joueur_t* getJoueurByNum(const cycleJoueur_t& cycle,int indice)
{
    int av = 1;
    linkedListJoueur_t* temp = cycle.premier;
    while(av++ != indice)
        temp = temp->next;
    return temp->joueur;
}
void setCycleActuel(cycleJoueur_t& cycle)
{
    cycle.premier = cycle.actuel;
}

joueur_t* cycleNext(cycleJoueur_t& cycle)
{
    cycle.actuel = cycle.actuel->next;
    return cycle.actuel->joueur;
}

/// Affiche un cycle
void afficherCycleJoueur(const cycleJoueur_t& cycle)
{
    if(cycle.nombreJoueur == 0)
    {
        cout << "Aucun Joueur"<<endl;
    }
    else
    {
        cout <<"Nombre de joueur : "<<cycle.nombreJoueur<<endl;


        linkedListJoueur_t* temp = cycle.premier;
        int compt=1;
        do
        {
            cout << "(" <<compt<<") "<<temp->joueur->pseudo<<endl;
            compt++;
            temp = temp->next;
        }
        while(temp!=cycle.premier);

    }
}
/// vide les joueurs d'un cycle
void reInitCycle(cycleJoueur_t& cycle)
{
         linkedListJoueur_t* temp = cycle.premier;
        do
        {
            viderJoueur(*temp->joueur);
            temp = temp->next;
        }
        while(temp!=cycle.premier);
}
void setInitialCycle(cycleJoueur_t& cycle)
{
    cycle.premier = cycle.initialPremier;
    cycle.actuel = cycle.premier;
}

void viderCycle(cycleJoueur_t& cycle)
{
        linkedListJoueur_t* temp = cycle.premier;
        linkedListJoueur_t* ancien;
        for(int i =0;i<cycle.nombreJoueur;i++)
        {
            viderJoueur(*temp->joueur);
            ancien = temp;
            temp = temp->next;
            delete ancien;
        }
}
classemenList_t classementVide()
{
    return classemenList_t{nullptr,0};
}

classemenList_t makeClassement(const cycleJoueur_t& cycle,std::string categ)
{
    classemenList_t classement = classementVide();
    classement.categorie = categ;
    linkedListJoueur_t* temp = cycle.premier;
    if(temp != nullptr)
    {
        do
        {
            insertJoueurByStat(classement,temp->joueur,categ);
            temp = temp->next;
        }
        while(temp != cycle.premier);
    }
    return classement;
}

/// Insert un joueur dans un classement par catégorie
bool insertJoueurByStat(classemenList_t& classement,joueur_t* joueur,std::string categ)
{
    linkedListJoueur_t* temp = classement.first;
    if(temp== nullptr)
    {
        classement.first = new linkedListJoueur_t{joueur,nullptr};
        classement.nbJoueur++;
        return true;
    }
    else
    {
        if(getNbCarte(temp->joueur,categ) <= getNbCarte(joueur,categ))
        {
            linkedListJoueur_t* temp_2 = new linkedListJoueur_t{joueur,temp};
            classement.first = temp_2;
            classement.nbJoueur++;
            return true;
        }
        else
        {
            while(temp != nullptr)
            {

                if(temp->next == nullptr)
                {
                    temp->next = new linkedListJoueur_t{joueur,nullptr};
                    classement.nbJoueur++;
                    return true;
                }
                else if(getNbCarte(temp->next->joueur,categ) <= getNbCarte(joueur,categ))
                {

                    linkedListJoueur_t* temp_2 = new linkedListJoueur_t{joueur,temp->next};
                    temp->next = temp_2;
                    classement.nbJoueur++;
                    return true;
                }
                else
                temp = temp->next;

            }
        }
    }
    return true;
}
/// On affiche le classement
void afficherClassement(const classemenList_t& classement)
{
    int compt = 1;
    linkedListJoueur_t* temp = classement.first;
    cout << "classement "<< classement.categorie<<" : \n";
    while(temp != nullptr)
    {
        cout << "(" << compt <<") " << temp->joueur->pseudo<< ", nombre de cartes : "<<getNbCarte(temp->joueur,classement.categorie)<<endl;
        temp = temp->next;
        compt++;
    }
}

/// On affiche la frise chronologique
void afficherOrdreChrono (joueur_t* joueur){
    mainJoueur_t mainChrono = mainVide();
    for (size_t i=0; i< joueur->frise_chronologique.size(); i++){
        insertCarte(joueur->frise_chronologique[i], mainChrono);
        cout << "Carte ajoutee : ";
        afficherCarte(*(joueur->frise_chronologique[i]));
        afficherMain(mainChrono);
        cout << "\n";
    }
}
