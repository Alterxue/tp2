/*************************************************************************
                           Catalogue - description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Catalogue> (fichier Catalogue.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <cstring>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Catalogue.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void Catalogue::Afficher() const
{
    if (m_nbTrajets == 0)
    {
        cout << "Le catalogue est vide." << endl;
    }
    else
    {
        cout << "Contenu du catalogue (" << m_nbTrajets << " trajets) :" << endl;
        for (unsigned int i = 0; i < m_nbTrajets; ++i)
        {
            cout << i + 1 << " : ";
            m_collectionTrajets[i]->Afficher();
            cout << endl;
        }
    }
} //----- Fin de Afficher

void Catalogue::Ajouter(Trajet* unTrajet)
{
    // Vérification de la capacité et redimensionnement si nécessaire
    if (m_nbTrajets >= m_tailleMax)
    {
        m_tailleMax *= 2; // On double la capacité
        Trajet** nouvelleCollection = new Trajet*[m_tailleMax];

        // Copie des pointeurs existants
        for (unsigned int i = 0; i < m_nbTrajets; ++i)
        {
            nouvelleCollection[i] = m_collectionTrajets[i];
        }

        // Suppression de l'ancien tableau (mais pas des trajets pointés !)
        delete[] m_collectionTrajets;
        m_collectionTrajets = nouvelleCollection;
    }

    // Ajout du trajet
    m_collectionTrajets[m_nbTrajets] = unTrajet;
    m_nbTrajets++;
} //----- Fin de Ajouter

void Catalogue::Rechercher(const char* depart, const char* arrivee) const
{
    cout << "Recherche simple de " << depart << " vers " << arrivee << " :" << endl;
    bool trouve = false;

    for (unsigned int i = 0; i < m_nbTrajets; ++i)
    {
        // Comparaison des chaînes de caractères (strcmp renvoie 0 si identique)
        if (strcmp(m_collectionTrajets[i]->GetVilleDepart(), depart) == 0 &&
            strcmp(m_collectionTrajets[i]->GetVilleArrivee(), arrivee) == 0)
        {
            cout << " -> ";
            m_collectionTrajets[i]->Afficher();
            cout << endl;
            trouve = true;
        }
    }

    if (!trouve)
    {
        cout << "Aucun trajet direct trouve." << endl;
    }
} //----- Fin de Rechercher

void Catalogue::RechercherAvance(const char* depart, const char* arrivee)
{
    cout << "Recherche avancee de " << depart << " vers " << arrivee << " :" << endl;
    
    // Allocation temporaire pour suivre le chemin en cours de construction
    // Dans le pire des cas, un chemin ne peut pas être plus long que le nombre de trajets total
    Trajet** chemin = new Trajet*[m_nbTrajets];
    
    // Tableau pour marquer les trajets visités dans la branche courante (éviter les boucles infinies)
    bool* estVisite = new bool[m_nbTrajets];
    for(unsigned int i = 0; i < m_nbTrajets; ++i) estVisite[i] = false;

    rechercheAvanceRecursive(depart, arrivee, chemin, 0, estVisite);

    // Nettoyage des tableaux temporaires
    delete[] chemin;
    delete[] estVisite;
} //----- Fin de RechercherAvance


//-------------------------------------------- Constructeurs - destructeur

Catalogue::Catalogue ( ) : m_nbTrajets(0), m_tailleMax(CAPACITE_INITIALE)
{
    m_collectionTrajets = new Trajet*[m_tailleMax];
} //----- Fin de Catalogue


Catalogue::~Catalogue ( )
{
    // Destruction de chaque trajet stocké
    for (unsigned int i = 0; i < m_nbTrajets; ++i)
    {
        delete m_collectionTrajets[i];
    }
    
    // Destruction du tableau lui-même
    delete[] m_collectionTrajets;
} //----- Fin de ~Catalogue


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

    void Catalogue::rechercheAvanceRecursive(const char* villeActuelle, const char* villeFinale, Trajet** chemin, int profondeur, bool* estVisite)
    {
        // Parcourt tous les trajets du catalogue pour trouver ceux qui partent de la villeActuelle
        for (unsigned int i = 0; i < m_nbTrajets; ++i)
        {
            // Si le trajet n'a pas déjà été utilisé dans ce chemin (évite les cycles)
            // ET si le départ du trajet correspond à notre position actuelle
            if (!estVisite[i] && strcmp(m_collectionTrajets[i]->GetVilleDepart(), villeActuelle) == 0)
            {
                // On ajoute ce trajet au chemin temporaire
                chemin[profondeur] = m_collectionTrajets[i];
                estVisite[i] = true;

                // CAS 1 : C'est la destination finale !
                if (strcmp(m_collectionTrajets[i]->GetVilleArrivee(), villeFinale) == 0)
                {
                    // On affiche la solution complète trouvée
                    cout << "Solution trouvee :" << endl;
                    for (int j = 0; j <= profondeur; ++j)
                    {
                        cout << "   " << (j+1) << ". ";
                        chemin[j]->Afficher();
                        cout << endl;
                    }
                    cout << "-----------------------" << endl;
                }
                // CAS 2 : Ce n'est pas la fin, on continue de chercher à partir de la ville d'arrivée de ce trajet
                else
                {
                    rechercheAvanceRecursive(m_collectionTrajets[i]->GetVilleArrivee(), villeFinale, chemin, profondeur + 1, estVisite);
                }

                // Backtracking : on marque le trajet comme non visité pour permettre 
                // son utilisation dans d'autres combinaisons potentielles
                estVisite[i] = false;
            }
        }
    }