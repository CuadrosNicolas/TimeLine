#include "iamanager.h"
using namespace std;
///converti un interval en un intervalDate
intervalDate_t convertIntervalToDate(interval_t i1)
{
    intervalDate_t iOut;
    iOut.type = i1.intervalType;
    switch(i1.intervalType)
    {
    case pasDeBorne:
        break;
    case between:
        iOut.min = intervalGetMin(i1);
        iOut.max = intervalGetMax(i1);
        break;
    case beforeMin:
        iOut.min = intervalGetMin(i1);
        break;
    case afterMax:
        iOut.max = intervalGetMax(i1);
        break;
    default:
        break;
    }
    return iOut;
}

///fait la somme de 2 intervalles si ils se croisent
intervalDate_t sommeInterval(const intervalDate_t& i1,const intervalDate_t& i2)
{
    intervalDate_t out;
    ///Verifi si les 2 intervalles sont de type born� � gauche et � droite
    if(i1.type == between && i1.type == i2.type)
    {
        out.type = between;
        croisementType_t croisementType = estCroises(i1,i2);
            switch(croisementType)
            {

            case CONTIENT:
                if(compareSizeInterval(i1,i2)==1)//i1 contient i2
                {
                    out.max = i1.max;
                    out.min = i1.min;
                    out.valid = true;
                }
                else//i2 contient i1
                {
                    out.max = i2.max;
                    out.min = i2.min;
                    out.valid = true;
                }
                break;
            case CROISEMENT:

                 const intervalDate_t* intervalGauche;
                const intervalDate_t* intervalDroite;
                ///test afin de d�terminer l'intervalles le plus � gauche et � droite
                if(i1.max < i2.max)
                {
                    intervalDroite = &i2;
                    intervalGauche = &i1;
                }
                else
                {
                    intervalDroite = &i1;
                    intervalGauche = &i2;
                }
                 out.min = intervalGauche->min;
                 out.max = intervalDroite->max;
                 out.valid = true;
                break;
            case AUCUN:
                out.valid = false;
            }
        }
        else
            out.valid = false;

        return out;
}

///renvoit si 2 intervalles se croisent (et si oui, comment ils se croisent)
croisementType_t estCroises(const intervalDate_t& i1,const intervalDate_t& i2)
{
            const intervalDate_t* intervalGauche;
            const intervalDate_t* intervalDroite;
            if(i1.max < i2.max)
            {
                intervalDroite = &i2;
                intervalGauche = &i1;
            }
            else
            {
                intervalDroite = &i1;
                intervalGauche = &i2;
            }
    if(intervalGauche->max>=intervalDroite->min && intervalGauche->max <= intervalDroite->max )//verification que i1 croise bien i2
    {
        if(intervalDroite->min < intervalGauche->min)//intervalDroite contient  l'interval de gauche
        {
            return CONTIENT;
        }
        else//les intervalles se croisent
        {
            return CROISEMENT;//borneMin de gauche et borneMax de droite
        }
    }
    else
        return AUCUN;
}///Compare la taille de 2 intervalles
int compareInterval(const intervalDate_t& i1,const intervalDate_t& i2)  //i1 et i2 ne doivent pas se croiser
{
    if(estCroises(i1,i2)==AUCUN)
    {
        if(i1.min < i2.min)
            return -1;//i1 < i2
        else
            return 1;//i2<i1
    }
    else
    {
        return 0;//i1 croise i2
    }
}
///renvoit une valeurs appartenant � un intervalle i
int getMid(const intervalDate_t& i)
{
    if(i.type==between)
    return (i.max + i.min)/2;
    else if(i.type==afterMax)
    return i.max+1;
    else if(i.type==beforeMin)
    return i.min-1;
    return 0;
}

///renvoit 1 si i1 plus grand que i2
///renvoit -1 si i2 plus grand que i1 ou que i1 == i2 en taille
int compareSizeInterval(const intervalDate_t& i1,const intervalDate_t& i2)
{
    if(i1.type == i2.type && i1.type == between)
    {
    if(intervalSize(i1)>intervalSize(i2))
        return 1;
    else
        return -1;
    }
    else
        return 0;
}
///renvoit la taille de l'intervalle
int intervalSize(const intervalDate_t& i)
{
    if(i.type == between)
    return i.max - i.min;
    else
    return -1;
}

///affiche un intervalDate
void afficherIntervalDate(const intervalDate_t& i)
{
    switch (i.type)
    {
    case beforeMin:
        cout << i.min << "]";
        break;
    case afterMax:
        cout << "[" << i.max;
        break;
    case between:
        cout << "[" << i.min << "-" << i.max << "]";
        break;
    case pasDeBorne:
        break;
    }
}


///initialise un ensemble de date vide
void initIntervalEnsemble(IntervalEnsemble_t& bI)
{
    bI.Left.type = pasDeBorne;
    bI.Right.type = pasDeBorne;
}
///rajoute un intervalle � un ensemble
void IntervalEnsembleAdd(IntervalEnsemble_t& bI,intervalDate_t i)
{
    bool extendInvalidLeft = false;
    bool extendInvalidRight = false;
    switch(i.type)
    {
        case beforeMin:
            ///Cas born� � droite
            ///on v�rifie si il en existe un ou si le nouvelle intervalle contient l'ancien
            if(bI.Left.type == pasDeBorne || bI.Left.min < i.min)
            {
                bI.Left.min = i.min;
                bI.Left.type = i.type;
                bI.Left.valid = true;
            extendInvalidLeft = true;
            }
            break;
        case afterMax:
            ///Cas born� � gauche
            ///on v�rifie si il en existe un ou si le nouvelle intervalle contient l'ancien
            if(bI.Right.type == pasDeBorne || i.max < bI.Right.max)
            {
                bI.Right.max = i.max;
                bI.Right.type = i.type;
                bI.Right.valid = true;
                extendInvalidRight = true;
            }
            break;
        case between:
            ///cas born� � gauche et � droite
            ///on test si il n'est pas contenu dans les bornes de gauche et droite
            if(bI.Left.type != pasDeBorne && i.min < bI.Left.min)
            {
                if(i.max > bI.Left.min)
                {

                    bI.Left.min = i.max;
                    extendInvalidLeft = true;
                }
                else
                    break;
            }
            else if(bI.Right.type != pasDeBorne && i.max >bI.Right.max)
            {
                    if(i.min<bI.Right.max)
                    {
                        bI.Right.max = i.min;
                        extendInvalidRight = true;
                    }
                    else
                        break;
            }
            ///Sinon on parcours l'ensemble des intervalles centraux
            else if(bI.Between.size()>0)
            {
                for(size_t e = 0;e<bI.Between.size();e++)
                {
                    ///V�rifie si il ne croise pas un intervalle existant
                    int avancement = compareInterval(bI.Between[e],i);

                        if(avancement == 0)///si il y a croisement
                        {
                            bI.Between[e] = sommeInterval(bI.Between[e],i);
                            break;
                        }
                        else if(avancement == 1)///si l'interval est inf�rieur � celui de la liste
                        {
                            bI.Between.insert(bI.Between.begin()+e,i);
                            break;
                        }
                        if(e+1 >= bI.Between.size())
                        {
                            bI.Between.push_back(i);
                        }
                }
            }
            else///Si l'intervalle � rajouter doit se situer � la fin des intervalles interm�diaires
            {
                    bI.Between.push_back(i);
            }
            break;
        case pasDeBorne:
            break;
    }
    if(bI.Between.size()>0)
    {
            ///On v�rifie si l'agrandissement des bornes � gauche ou droite
            ///ne contiennnt pas des intervalles interm�diaires
            ///Sinon on les retire
            if(extendInvalidRight)
            {
                for(size_t e = 0;e<bI.Between.size();e++)
                {
                      if(bI.Between[e].min >= bI.Right.max)
                    {
                        bI.Between.erase(bI.Between.begin()+e);
                    }
                    else if(bI.Between[e].min < bI.Right.max && bI.Between[e].max > bI.Right.max)
                    {
                        bI.Left.max = bI.Between[e].min;
                        bI.Between.erase(bI.Between.begin()+e);
                    }
                }
            }
            if(extendInvalidLeft)
            {
                for(size_t e = 0;e<bI.Between.size();e++)
                {
                    if(bI.Between[e].max <= bI.Left.min)
                    {
                        bI.Between.erase(bI.Between.begin()+e);
                        e--;
                    }
                    else if(bI.Between[e].min < bI.Left.min && bI.Between[e].max > bI.Left.min)
                    {
                        bI.Left.min = bI.Between[e].max;
                        bI.Between.erase(bI.Between.begin()+e);
                        e--;
                    }
                }
            }

    }
}
///affiche un ensemble de date
void afficherIntervalEnsemble(const IntervalEnsemble_t& bI)
{
    afficherIntervalDate(bI.Left);
    for(size_t e =0;e<bI.Between.size();e++)
    {
        cout <<"__";
        afficherIntervalDate(bI.Between[e]);
    }
    cout << "__";
    afficherIntervalDate(bI.Right);
    cout << endl;
}
///vide un ensemble de date
void clearIntervalEnsemble(IntervalEnsemble_t& bI)
{
    bI.Left.valid = false;
    bI.Left.type = pasDeBorne;

    bI.Right.valid = false;
    bI.Right.type = pasDeBorne;

    bI.Between.clear();
}
///charge une mainJoueur sous la forme d'un ensemble de date
IntervalEnsemble_t loadEnsembleFromMain(const mainJoueur_t& mainJoueur)
{
    IntervalEnsemble_t IE;
    initIntervalEnsemble(IE);
    mainJoueurNoeud_t* temp = mainJoueur.carteJoueur;
    if(temp != nullptr)
    {
        IE.Left=intervalDate_t{beforeMin,temp->carte->date,0,true};
        while(temp->next != nullptr)
        {
            IE.Between.push_back({between,temp->carte->date,temp->next->carte->date,true});
            temp = temp->next;

        }
        IE.Right = intervalDate_t{afterMax,0,temp->carte->date,true};

    }
    return IE;
}
///retire des intervalles invalides d'un ensemble d'interval
///ne laissant que des intervalles probables
IntervalEnsemble_t extractBadIntervalFrom(const IntervalEnsemble_t mayBeGood,const IntervalEnsemble_t& badInterval)
{

    IntervalEnsemble_t out = mayBeGood;
    ///on v�rifie si les bornes extr�mes sont valides
    if(out.Left.type != pasDeBorne && badInterval.Left.type!=pasDeBorne && badInterval.Left.min > out.Left.min)
    {
        out.Left.valid = false;
        out.Left.type = pasDeBorne;
    }
    if(out.Right.type != pasDeBorne&& badInterval.Right.type!=pasDeBorne && badInterval.Right.max < out.Right.max)
    {
        out.Right.valid = false;
        out.Right.type = pasDeBorne;
    }
    ///on v�rifie si les bornes interm�diaires sont contenues dans des bornes invalides
    ///ou si une partie est contenu dans une borne invalide(dans ce cas on les raccourcis)
    for(unsigned int e = 0;e<out.Between.size();e++)
    {
        ///test si la borne interm�diaire n'est pas contenu dans les bornes extr�mes
        ///des intervalles invalides
        if( (badInterval.Left.type!=pasDeBorne && out.Between[e].max < badInterval.Left.min) ||( badInterval.Right.type!=pasDeBorne && out.Between[e].min > badInterval.Right.max))
        {

            out.Between.erase(out.Between.begin()+e);
            e--;

        }
        else
        {
                for(unsigned int i = 0;i<badInterval.Between.size();i++)
                {
                     croisementType_t temp = estCroises(out.Between[e],badInterval.Between[i]);
                     switch(temp)
                     {
                     case CROISEMENT:
                            if(out.Between[e].max < badInterval.Between[i].max)///out est � gauche de badInterval
                            {
                                out.Between[e].max = badInterval.Between[i].min;
                            }
                            else///i1 est � droite de i2
                            {
                                out.Between[e].min = badInterval.Between[i].max;
                            }
                        break;
                     case CONTIENT:
                         ///Si un intervalle est contenu dans un intervalle invalide
                         ///On le retire
                         if(intervalSize(badInterval.Between[i])>=intervalSize(out.Between[e]))
                         {
                            out.Between.erase(out.Between.begin()+e);
                            e--;
                         }
                         ///si un intervalle contient un intervalle invalide
                         ///on le s�pare en 2 sous intervalles
                         else
                         {
                             out.Between.insert(out.Between.begin()+e,{between,out.Between[e].min,badInterval.Between[i].min,true});
                             e++;
                             out.Between[e].min = out.Between[e].max;
                             out.Between[e].max = badInterval.Between[i].max;
                         }
                        break;
                     case AUCUN:
                        break;
                     }

                }
        }
    }

    return out;
}
///renvoit l'indice dans un vector d'intervalDate qui correspond � la r�ponse
int getGoodIndice(vector<intervalDate_t> reponseVec,int reponse)
{
    for(unsigned int i = 0;i<reponseVec.size();i++)
    {
        switch(reponseVec[i].type)
        {
        case between:
            if(reponse >= reponseVec[i].min && reponse <= reponseVec[i].max)
                return i;
            break;
        case beforeMin:
            if(reponse <= reponseVec[i].min)
                return i;
            break;
        case afterMax:
            if(reponse >= reponseVec[i].max)
                return i;
            break;
        case pasDeBorne:
            break;
        }
    }
    return 0;
}
///renvoit un entier(correspondant � une date) en fonction d'un interval de date probable
///du niveau de l'IA
///ainsi que le la r�ponse attendu
int getAnswer(IntervalEnsemble_t INTERVAL,unsigned int ia_level,int reponse)
{
    unsigned int answerIntervalIndice;
    ///constitu un vector d'interval possiblement valide
    vector<intervalDate_t> reponseVec = INTERVAL.Between;
    ///Ajoute les bornes extr�mes (si elle existe)
    ///� l'extr�mit� du vector
        if(INTERVAL.Left.type!=pasDeBorne)
            reponseVec.insert(reponseVec.begin(),INTERVAL.Left);
        if(INTERVAL.Right.type!=pasDeBorne)
            reponseVec.push_back(INTERVAL.Right);
    ///Si le vector est vide (pas de carte)
    ///l'IA r�pond 0
    if(reponseVec.size()==0)
    {
       return 0;
    }
    ///Si l'IA est de niveau 1(ordinateur facile)
    ///elle renvoit une valeur au hasard comprit dans les intervalles possiblement valide
    else if(ia_level == 1)
    {
        answerIntervalIndice = randomNumber(reponseVec.size());
        return getMid(reponseVec[answerIntervalIndice]);
    }
    ///Si l'IA � un niveau sup�rieur � 1
    else
    {
        ///on r�cup�re l'indice dans le vector correspondant � l'intervalle valide
        unsigned int goodIndice = getGoodIndice(reponseVec,reponse);
        ///On "centre" les intervalles possiblement valide
        ///en calculant les �chantillons centr�s sur le bon intervalle
        ///selon le niveau de l'IA (ce qui correspond � divis� le nombre d'intervalle possible par le niveau de l'IA)
        unsigned int echantillon = ceil((reponseVec.size())/ia_level);
        ///On choisit un nombre au hasard parmis cet �chantillon
        int answerIntervalIndice = randomNumber(echantillon+1);

        ///On fait correspondre ce chiffre � un indice dans le vector d'interval
        ///Si l'indice vaut 0, l'IA donne la bonne r�ponse
        int addedVal = ceil(float(answerIntervalIndice)/2);
        ///Si la r�ponse est %2, cela correspond � la partie droite de l'�chantillon
        if(answerIntervalIndice % 2 == 0)
        {
            int vecIndice;
            ///On v�rifie que la partie � droite n'est pas vide
            if(goodIndice - addedVal < 0)
            {
                vecIndice = goodIndice + addedVal;
            }
            ///si ce n'est pas le cas on initialise l'indice
            else
            {

            vecIndice= goodIndice - addedVal;
            }
            return getMid(reponseVec[vecIndice]);
        }
        ///Si la r�ponse n'est pas %2, cela correspond � la partie gauche de l'�chantillon
        else
        {
            int vecIndice;
            if(goodIndice + addedVal >= reponseVec.size())
            {
                vecIndice = goodIndice - addedVal;
            }
            else
            {

            vecIndice= goodIndice + addedVal;
            }
            return getMid(reponseVec[vecIndice]);
        }


    }
    ///ERREUR
    return 0;
}


