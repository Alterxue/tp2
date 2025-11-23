/*************************************************************************
                            TrajetCompose - Réalisation
                              -------------------
    début                   : 23/11/2025
    copyright               : (C) 2025 par Votre Nom
    e-mail                  : votre.email@exemple.com
*************************************************************************/

//---------- Réalisation de la classe <TrajetCompose> (fichier TrajetCompose.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstring>

//------------------------------------------------------ Include personnel
#include "TrajetCompose.h" // Interface de la classe
#include "TrajetSimple.h"  // Pour le cast et la manipulation des sous-trajets

//------------------------------------------------------------- Constantes
const unsigned int CAPACITE_INITIALE = 10;

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void TrajetCompose::Afficher() const
// Algorithme :
// Parcourt la collection de sous-trajets et appelle leur méthode Afficher().
{
    cout << "Trajet Composé : " << GetVilleDepart() << " -> " << GetVilleArrivee() << " (";
    for (unsigned int i = 0; i < m_nbTrajets; ++i)
    {
        m_collectionTrajets[i]->Afficher();
        if (i < m_nbTrajets - 1)
        {
            cout << " puis ";
        }
    }
    cout << ")" << endl;
} //----- Fin de Afficher

const char * TrajetCompose::GetVilleDepart() const
// Algorithme :
// Retourne la ville de départ du premier trajet dans la collection.
{
    if (m_nbTrajets > 0)
    {
        return m_collectionTrajets[0]->GetVilleDepart();
    }
    // Si la collection est vide, on retourne la ville stockée dans la partie mère Trajet
    // (qui sera initialisée par l'appel au constructeur de la mère, souvent à vide pour TrajetCompose).
    return Trajet::GetVilleDepart(); 
} //----- Fin de GetVilleDepart

const char * TrajetCompose::GetVilleArrivee() const
// Algorithme :
// Retourne la ville d'arrivée du dernier trajet dans la collection.
{
    if (m_nbTrajets > 0)
    {
        return m_collectionTrajets[m_nbTrajets - 1]->GetVilleArrivee();
    }
    // Si la collection est vide, on retourne la ville stockée dans la partie mère Trajet.
    return Trajet::GetVilleArrivee();
} //----- Fin de GetVilleArrivee

void TrajetCompose::AjouterTrajet(TrajetSimple* unTrajet)
// Algorithme :
// 1. Vérifie la contrainte d'enchaînement.
// 2. Si la collection est pleine, double sa taille (réallocation).
// 3. Ajoute le nouveau trajet. Met à jour la partie mère (m_villeDepart/m_villeArrivee) en cas de premier ajout.
{
    // 1. Vérification de la contrainte d'enchaînement
    if (m_nbTrajets > 0)
    {
        if (strcmp(m_collectionTrajets[m_nbTrajets - 1]->GetVilleArrivee(), unTrajet->GetVilleDepart()) != 0)
        {
            cerr << "ERREUR: Le trajet n'a pas pu être ajouté car l'enchaînement des villes n'est pas respecté." << endl;
            delete unTrajet; // Libère l'objet non ajouté
            return;
        }
    }
    // NOTE : Si m_nbTrajets == 0, on met à jour les villes m_villeDepart et m_villeArrivee de la classe mère
    // Bien que non strictement nécessaire grâce aux accesseurs virtuels redéfinis, c'est une bonne pratique.
    // L'implémentation de Trajet est laissée à TrajetSimple ou au premier trajet ajouté ici.
    
    // 2. Réallocation si la collection est pleine
    if (m_nbTrajets == m_tailleMax)
    {
        unsigned int nouvelleTaille = m_tailleMax * 2;
        TrajetSimple** nouvelleCollection = new TrajetSimple*[nouvelleTaille];

        for (unsigned int i = 0; i < m_nbTrajets; ++i)
        {
            nouvelleCollection[i] = m_collectionTrajets[i];
        }

        delete[] m_collectionTrajets;

        m_collectionTrajets = nouvelleCollection;
        m_tailleMax = nouvelleTaille;

    #ifdef MAP
        cout << "Réallocation de <TrajetCompose> : taille augmentée à " << m_tailleMax << endl;
    #endif
    }

    // 3. Ajout
    m_collectionTrajets[m_nbTrajets] = unTrajet;
    m_nbTrajets++;

} //----- Fin de AjouterTrajet


//------------------------------------------------- Surcharge d'opérateurs
TrajetCompose & TrajetCompose::operator = ( const TrajetCompose & unTrajetCompose )
// Algorithme :
// 1. Test d'auto-affectation.
// 2. Appel à l'opérateur d'affectation de la classe mère (Trajet).
// 3. Libération des ressources de la collection actuelle.
// 4. Recopie profonde des attributs et de la nouvelle collection.
{
    if (this != &unTrajetCompose)
    {
        // 2. Appel à l'opérateur de la classe mère (gère m_villeDepart/m_villeArrivee)
        // Attention: l'opérateur d'affectation de Trajet n'est pas défini dans le .h que vous avez fourni. 
        // Par défaut il fait une copie superficielle. S'il existe, l'appeler : 
        // Trajet::operator=(unTrajetCompose);

        // 3. Libération des anciennes ressources de la collection
        for (unsigned int i = 0; i < m_nbTrajets; ++i)
        {
            delete m_collectionTrajets[i];
        }
        delete[] m_collectionTrajets;

        // 4. Recopie profonde de la collection
        m_tailleMax = unTrajetCompose.m_tailleMax;
        m_nbTrajets = unTrajetCompose.m_nbTrajets;

        m_collectionTrajets = new TrajetSimple*[m_tailleMax];

        for (unsigned int i = 0; i < m_nbTrajets; ++i)
        {
            // Copie en profondeur du TrajetSimple*
            m_collectionTrajets[i] = new TrajetSimple(*unTrajetCompose.m_collectionTrajets[i]);
        }
    }
    return *this;
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur

TrajetCompose::TrajetCompose ( const TrajetCompose & unTrajetCompose ) 
    // IMPORTANT : Appel au constructeur de copie de la classe mère, car elle gère l'allocation des villes.
    : Trajet(unTrajetCompose), 
      m_tailleMax(unTrajetCompose.m_tailleMax), 
      m_nbTrajets(unTrajetCompose.m_nbTrajets)
// Algorithme :
// 1. Appel du constructeur de copie de la classe mère.
// 2. Initialisation des attributs de taille.
// 3. Copie en profondeur de la collection interne.
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <TrajetCompose>" << endl;
#endif

    m_collectionTrajets = new TrajetSimple*[m_tailleMax];

    for (unsigned int i = 0; i < m_nbTrajets; ++i)
    {
        // Copie en profondeur du TrajetSimple*
        m_collectionTrajets[i] = new TrajetSimple(*unTrajetCompose.m_collectionTrajets[i]);
    }

} //----- Fin de TrajetCompose (constructeur de copie)

TrajetCompose::TrajetCompose ( ) 
    // IMPORTANT : Appel au constructeur de la classe mère avec des villes initiales (vides ici).
    : Trajet("", ""), // On utilise des chaînes vides ou NULL selon la gestion attendue
      m_collectionTrajets(new TrajetSimple*[CAPACITE_INITIALE]), 
      m_nbTrajets(0), m_tailleMax(CAPACITE_INITIALE)
// Algorithme :
// Initialisation de la collection interne (tableau de pointeurs vide) avec une capacité initiale.
{
#ifdef MAP
    cout << "Appel au constructeur par défaut de <TrajetCompose>" << endl;
#endif

} //----- Fin de TrajetCompose (constructeur par défaut)

TrajetCompose::~TrajetCompose ( )
// Algorithme :
// 1. Libère la mémoire allouée pour chaque TrajetSimple* dans la collection.
// 2. Libère le tableau de pointeurs lui-même.
// 3. Le destructeur de la classe mère est appelé automatiquement après celui-ci pour libérer m_villeDepart/m_villeArrivee.
{
#ifdef MAP
    cout << "Appel au destructeur de <TrajetCompose>" << endl;
#endif
    // 1. Libération des sous-trajets
    for (unsigned int i = 0; i < m_nbTrajets; ++i)
    {
        delete m_collectionTrajets[i];
    }
    
    // 2. Libération du tableau de pointeurs
    delete[] m_collectionTrajets;

} //----- Fin de ~TrajetCompose

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées