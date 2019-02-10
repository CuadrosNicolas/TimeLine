#include "pileCarte.h"
using namespace std;
/// FONCTIONS DE LA PILE
pileCarte_t pile_vide()
{
    return pileCarte_t{nullptr};
}

bool estVide(pileCarte_t& pileCarte)
{
    if(pileCarte.sommet==nullptr)
    return true;
    else
    return false;
}

bool empiler(pileCarte_t& p,carte_t carte)
{
    if(!estVide(p))
    {
        pileCarteNoeud_t* temp = new pileCarteNoeud_t{carte,p.sommet};
        p.sommet = temp;
    }
    else
    {
        p.sommet = new pileCarteNoeud_t{carte,nullptr};
    }
    p.nbCarte++;
    return true;
}

void viderPile(pileCarte_t& p)
{
    pileCarteNoeud_t* temp = p.sommet;
    while(temp != nullptr)
    {
        pileCarteNoeud_t* tempSupp = temp;
        temp=temp->next;
        delete tempSupp;
    }
    p.sommet = nullptr;
}

bool depiler(pileCarte_t& p)
{

    if(!estVide(p))
    {
        pileCarteNoeud_t* temp = p.sommet;
        p.sommet = temp->next;
        p.nbCarte--;
    }
    return true;
}

///Retourne le sommet d'une pile
carte_t* getSommet(const pileCarte_t& p)
{
    return &(p.sommet->carte);
}


/// Remplit une pile à partir de notre fichier de cartes et les mélange
categorieList_t chargerPile(pileCarte_t& pile,std::string fichier)
{
    viderPile(pile);
    ifstream stream(fichier);
    string line="";
    std::vector<carte_t> paquetCarte;
    categorieList_t categorieReference;
    ///à la lecture du fichier, la première ligne est "corrompu" en contenant
    /// des caractères inconnus, pour esquiver ce bug, on lit cette ligne dans le vide
    ///en attendant une autre solution
    getline(stream,line);
    while(getline(stream,line))
    {
        paquetCarte.push_back(getCarteFromString(line));
        if(!isCategorieExist(categorieReference,paquetCarte[paquetCarte.size()-1].categorie))
        categorieReference.push_back(paquetCarte[paquetCarte.size()-1].categorie);
        line="";
    }
    pile = pile_vide();
    paquetCarte = melangerCarte(paquetCarte,100);
    for(unsigned int i =0;i<paquetCarte.size();i++)
    {
        empiler(pile,paquetCarte[i]);
    }
    cout << "Nombre de cartes chargees : " << pile.nbCarte << endl;
    return categorieReference;

}

///Fonctions permettant le mélange des cartes
void swapElement(std::vector<carte_t>& vec,int a,int b)
{
    carte_t temp = vec[a];
    vec[a]=vec[b];
    vec[b] = temp;
}

vector<carte_t> melangerCarte(vector<carte_t> paquet,int number)
{
    initRandom();
    size_t maxSize = paquet.size();
    for(int i = 0;i<number;i++)
    swapElement(paquet,randomNumber(maxSize),randomNumber(maxSize));
    return paquet;

}

void initRandom()
{
    srand(time(NULL));
}
int randomNumber(int max)
{
    if(max > 0){
    return rand()%max;
    }
    return 0;
}

/// Retoure vrai si une catégorie existe
bool isCategorieExist(const categorieList_t& categorieList,const string& categorie)
{
    for(unsigned int i =0; i<categorieList.size(); i++)
    {
        if(categorieList[i]==categorie)
        {
            return true;
        }
    }
    return false;
}
