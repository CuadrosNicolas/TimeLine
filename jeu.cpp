
#include "jeu.h"
#define GENERAL "general"
using namespace std;

/// On créer une partie vide
partie_t partieVide()
{
    return partie_t{pile_vide(),initCycle(),maxCarte,10};
}

/// On affiche une partie
void afficherPartie(const partie_t& partie)
{
    cout << "----------PARTIE ACTUEL-------------"<<endl<< endl;
    afficherCycleJoueur(partie.cycleJoueur);
    cout << "\n ParamËtre de la partie : \n";
    switch(partie.partiType)
    {
        case pileVide:
        cout << "\tPileVide : la partie se finit quand la pile de carte est vide\n";
        break;

        case maxCarte:
        cout <<"\tmaxCarte :la partie se finit quand un joueur a le maximum de carte\n";
        cout <<"\tmaximum de carte : "<< partie.maxCarteValue<<"\n";
        break;
    }
    cout << "------------------------------------";
    cout << "\n";

}
///lance le tour d'un joueur
interval_t tourJoueur(joueur_t* joueur,carte_t* carteEnJeu,partie_t& partie)
{
     int date = 0;
    afficherJoueur(joueur);

    cout << "\ncarte en jeu : "<<endl;
    afficherAnonyme(carteEnJeu);
    cout <<endl;
    cout << "\nentrer une date : ";


    if(joueur->joueurType == HUMAIN)
    {
        date = tourHumain();
    }
    else
    {
        date = tourIA(joueur,carteEnJeu,partie);
    }
    cout << date << endl;
    interval_t interval = identifyInterval(joueur->frise,date,carteEnJeu);
    if(!interval.valid)
    {
        IntervalEnsembleAdd(partie.currentBadInterval,convertIntervalToDate(interval));

    }
    else
    {
          joueur->frise_chronologique.push_back(carteEnJeu);
    }
    return interval;
}
/// On affiche le joueur qui doit jouer ainsi que sa carte
int tourHumain()
{

    int out = 0;
    cin >> out;
    return out;

}
/// Fonction qui fait jouer une IA
int tourIA(joueur_t* joueur,carte_t* carteEnJeu,partie_t& partie)
{
    unsigned int waitTime=0;
    int date=0;
    IntervalEnsemble_t ie;


    ie = loadEnsembleFromMain(joueur->frise);

    sleep(waitTime);
    ie = extractBadIntervalFrom(ie,partie.currentBadInterval);
    sleep(waitTime);
    date = getAnswer(ie,static_cast<int>(joueur->joueurType),carteEnJeu->date);
    return date;
}

/// Afficher la frise d'un joueur
void menuAfficherFrise(const partie_t& partie)
{
    int choix = 1;
    while(choix != 0)
    {
        afficherCycleJoueur(partie.cycleJoueur);
        cout << "Entrer le numero du joueur a afficher la frise ou 0 pour quitter\n votre choix : ";
        cin >> choix;
        if(choix == 0)
            break;
        else
        {
            joueur_t* temp = getJoueurByNum(partie.cycleJoueur,choix);
            if(temp != nullptr)
            {
                cout << "Frise de : "<<temp->pseudo<<endl<<endl;
                afficherOrdreChrono(temp);
            }
            else
            {
                  cout << "entrer un choix valide ! "<<endl;
            }
            system("PAUSE");
            system("cls");
        }

    }
}
/// Deroulement de la partie
void lancerPartie(partie_t partie)
{

    system("cls");
    bool finDuJeu = false;
    interval_t reponse;
    carte_t* carteEnJeu = getSommet(partie.pileCarte);
    unsigned int tour=1;
    initIntervalEnsemble(partie.currentBadInterval);

    while(!finDuJeu)
    {
        joueur_t* joueurActuel = partie.cycleJoueur.premier->joueur;
        do
        {
            cout << "TOUR NUMERO : "<<tour<<endl<<"\n";
            if(partie.partiType==maxCarte)
            cout << "MAXIMUM DE CARTES : "<<partie.maxCarteValue<<endl<<endl;
            else
            cout << "\n";
            reponse= tourJoueur(joueurActuel,carteEnJeu,partie);
            if(reponse.valid) // si réponse valide
            {
                setCycleActuel(partie.cycleJoueur);
                if(getNbCarte(joueurActuel,GENERAL) >= partie.maxCarteValue && partie.partiType == maxCarte) // si fin du jeu
                {
                    finDuJeu = true;
                }
            }
            else // Si réponse fausse
            {
                cout << "FAUX !\nAu joueur Suivant" <<endl;
                system("PAUSE");
                system("cls");
                joueurActuel = cycleNext(partie.cycleJoueur);
            }

        }while(joueurActuel != partie.cycleJoueur.premier->joueur); // c'est au tour des joueurs suivants pour cette meme carte
        clearIntervalEnsemble(partie.currentBadInterval);
        initIntervalEnsemble(partie.currentBadInterval);
        if(!reponse.valid)
        {
            cout << "Dommage ! La carte etait: \n";
        }
        else
        {
            cout << "Bravo ! la carte etait :\n" << endl;
        }
        afficherCarte(*carteEnJeu);
        if(finDuJeu)
        {
            cout << "\nBravo !, vous avez gagne ! \n"<<endl;
        }

        depiler(partie.pileCarte);
        if(estVide(partie.pileCarte))
        {
            cout << "***La pile de carte est vide !***\n";
            cout << "***    La partie est finie    ***\n";
            finDuJeu = true;
        }
        else if(finDuJeu)
        {
            cout << "***Le maximum de carte a ete atteint!***\n"<< endl;
            break;
        }
        else
        {
            carteEnJeu = getSommet(partie.pileCarte);
            tour++;
        }
        system("PAUSE");
        system("cls");
    }
    setInitialCycle(partie.cycleJoueur);
    system("cls");
    menuClassement(partie);
    system("cls");
    menuAfficherFrise(partie);
    reInitCycle(partie.cycleJoueur);
}

///menu permettant de rentrer un nouveau joueur dans une partie
void menuEntrerJoueur(partie_t& partie)
{
    system("cls");
    insertJoueur(partie.cycleJoueur,entrerJoueur());
}

/// Menu permettant de changer les parametres d'une partie
void changementParametres (partie_t& partie){

    system("PAUSE");
    system("cls");

    int a=-1;
    int nbCartes=0;
    cout << "Choisissez le parametre mettant fin a la partie : " << endl;
    cout << "[1] Le nombre de cartes \n" ;
    cout << "[2] La pile est vide \n" ;
    cout << "Votre choix : ";
    cin >> a;

    if (a==1){
        cout << " Vous avez choisit de gagner en fonction du nombre de cartes" << endl;
        cout << " Entrez le nombre de cartes pour gagner :";
        cin >> nbCartes;
        partie.maxCarteValue = nbCartes;
        partie.partiType = maxCarte;
    }else if (a ==2){
        cout << "Vous avez choisit de gagner lorsque la pile est vide " << endl;
        partie.partiType = pileVide;
    }
}
/// Supprime un joueur a partir de son indice
void menuSupprimerJoueur(partie_t& partie)
{
    int choix = 1;
    bool temp = false;
    while(choix != 0)
    {
        afficherCycleJoueur(partie.cycleJoueur);
        cout << "Entrer le numero du joueur a supprimer ou 0 pour quitter\n votre choix : ";
        cin >> choix;
        if(choix == 0)
            break;
        else
        {
            temp = suppJoueur(partie.cycleJoueur,choix);
            if(!temp)
            {
                cout << "entrer un choix valide ! "<<endl;
            }
            else{
                cout << "le joueur a bien ete supprime ! "<<endl;
            }
            system("PAUSE");
            system("cls");
        }

    }
}
/// Fonction permettant de choisir le type de classement voulu
void menuClassement(const partie_t& partie)
{
    unsigned int choix=1;
    string categ = GENERAL;
    while(choix!=0)
    {
        classemenList_t classement = makeClassement(partie.cycleJoueur,categ);
        afficherClassement(classement);
        cout << "\n\n";
        cout << "[0] continuer"<<endl;
        cout << "****ou Choississez le type de classement : ****"<<endl;
        cout << "[1] general\n";
        for(unsigned int i = 0;i<partie.categorieVector.size();i++)
        cout << "["<<i+2<<"] "<<partie.categorieVector[i]<<endl;
        cout << "Votre choix :";
        cin >> choix;
        if(choix == 1)
        {
            categ = GENERAL;
        }
        else if(choix >=2 && choix <partie.categorieVector.size()+2)
        {
            categ = partie.categorieVector[choix-2];
        }
        else if(choix==0)
        {
            break;
        }
        else
        {
            cout << "\n";
            cout << "<<<Entrez un choix valide>>>\n";
        }
        system("PAUSE");
        system("cls");
    }
}

/// On affiche le menu du jeu
void menuJeu(partie_t& partie)
{
    int choix=1;
    while(choix!=5)
    {
        cout << "****BIENVENUE DANS TIMELINE****"<<endl;
        afficherPartie(partie);
        cout << "Choix disponible : \n";
        cout << "[1] Lancer la partie\n";
        cout << "[2] Modifier les parametres\n";
        cout << "[3] Ajouter un joueur\n";
        cout << "[4] Supprimer un joueur\n";
        cout << "[5] QUITTER\n";
        cout << "Votre choix :";
        cin >> choix;
        switch(choix)
        {
            case 1:
            if(partie.cycleJoueur.nombreJoueur ==0)
            {
                cout << "Il n'y a aucun joueur dans la partie !\nVeullez en rajouter\n\n";
            }
            else
            {
                partie.categorieVector = chargerPile(partie.pileCarte,partie.fichierString);
                setCategorieForPlayer(partie.cycleJoueur,partie.categorieVector);
                lancerPartie(partie);

            }
            break;
            case 2:
            changementParametres(partie);
            break;
            case 3:
            menuEntrerJoueur(partie);
            break;
            case 4:
                menuSupprimerJoueur(partie);
            break;
            case 5:
                //on quitte
            break;

            default:
                choix = 1;
            cout << "\n";
            cout << "<<<Entrez un choix valide>>>\n";
            break;
        }
        system("cls");
    }
    cout << "Bye bye !\n";
    viderPile(partie.pileCarte);
    viderCycle(partie.cycleJoueur);
}
///menu permettant de choisir un fichier de carte
void choixFichier(partie_t& partie)
{
    bool continu = true;
    while(continu)
    {
        cout << "Choisissez votre fichier de carte(fichier a choisir de preference 'data.txt') : ";
        cin >> partie.fichierString;
        continu = (!testFichier(partie.fichierString));
        if(continu)
        {
            cout << "Entrez un nom de fichier valide ! "<<endl;
        }
    }
    system("cls");
}
///permet de tester si un fichier est valide
bool testFichier(std::string fichier)
{
    ifstream stream(fichier);
        if(stream)
        {
            stream.close();
            return true;
        }
        else
        {
            stream.close();
            return false;
        }
}
/// Déroulement du jeu
void launchGame()
{
    partie_t partie = partieVide();
    choixFichier(partie);
    partie.cycleJoueur = initCycle();
    menuJeu(partie);
}
