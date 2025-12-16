/*************************************************************************
                           Catalogue - description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Catalogue> (fichier Catalogue.h) ----------------
#ifndef CATALOGUE_H
#define CATALOGUE_H

//--------------------------------------------------- Interfaces utilisées
#include "Trajet.h"
#include "TrajetSimple.h"
#include "TrajetCompose.h"

//------------------------------------------------------------- Constantes
const int CAPACITE_INITIALE = 10;

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Catalogue>
// La classe Catalogue gère une collection de Trajets (Simples ou Composés).
// Elle permet d'ajouter des trajets, de les afficher et d'effectuer deux types
// de recherches :
// 1. Recherche Simple : Trajets directs existant dans le catalogue.
// 2. Recherche Avancée : Combinaison de trajets pour relier A à B.
//------------------------------------------------------------------------

class Catalogue
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    // Affiche le contenu complet du catalogue.
    //
    // Contrat :
    // Ne modifie pas l'objet (const).
    void Afficher() const;

    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    // Ajoute un nouveau trajet (Simple ou Composé) au catalogue.
    // Gère le redimensionnement dynamique du tableau si nécessaire.
    //
    // Contrat :
    // Le catalogue prend la responsabilité du pointeur (le détruira).
    // Le pointeur ne doit pas être NULL.
    void Ajouter(Trajet* unTrajet);

    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    // Recherche les trajets directs (existants dans le catalogue) allant de depart à arrivee.
    //
    // Contrat :
    // Les chaînes de caractères ne doivent pas être NULL.
    void Rechercher(const char* depart, const char* arrivee) const;

    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    // Recherche complexe : trouve toutes les combinaisons de trajets permettant
    // d'aller de depart à arrivee en utilisant l'algorithme de parcours en profondeur (DFS).
    //
    // Contrat :
    // Les chaînes de caractères ne doivent pas être NULL.
    void RechercherAvance(const char* depart, const char* arrivee);

    // Sauvegarde le catalogue dans un fichier
    // Mode d'emploi :
    // Permet de sauvegarder tout ou partie du catalogue dans un fichier, selon différents critères (type, ville, intervalle)
    // Contrat :
    // Le nom du fichier doit être valide. Les critères sont optionnels.
    void Sauvegarder(const char* nomFichier, int mode = 0, const char* villeDep = nullptr, const char* villeArr = nullptr, int n = -1, int m = -1) const;

    // Charge des trajets depuis un fichier et les ajoute au catalogue
    // Mode d'emploi :
    // Permet de charger tout ou partie d'un fichier de trajets dans le catalogue courant, selon différents critères (type, ville, intervalle)
    // Contrat :
    // Le nom du fichier doit être valide. Les critères sont optionnels.
    void Charger(const char* nomFichier, int mode = 0, const char* villeDep = nullptr, const char* villeArr = nullptr, int n = -1, int m = -1);

//-------------------------------------------- Constructeurs - destructeur

    Catalogue ( );
    // Mode d'emploi :
    // Constructeur par défaut. Initialise la collection.
    //
    // Contrat :
    // Aucune action spécifique.

    virtual ~Catalogue ( );
    // Mode d'emploi :
    // Destructeur. Libère la mémoire de tous les trajets stockés et du tableau lui-même.
    //
    // Contrat :
    // Assure l'absence de fuite de mémoire.

//------------------------------------------------------------------ PRIVE

protected:
    //----------------------------------------------------- Méthodes protégées
    
    // Méthode helper pour la recherche avancée (récursive)
    // depart : ville actuelle dans la récursion
    // arrivee : ville cible finale
    // chemin : pile des trajets empruntés pour la solution en cours
    // profondeur : nombre de trajets dans le chemin actuel
    // visite : tableau de booléens pour éviter les cycles infinis (optionnel mais recommandé)
    void rechercheAvanceRecursive(const char* villeActuelle, const char* villeFinale, Trajet** chemin, int profondeur, bool* estVisite);

    //----------------------------------------------------- Attributs protégés
    
    Trajet** m_collectionTrajets; // Tableau dynamique de pointeurs vers Trajet
    unsigned int m_nbTrajets;     // Nombre actuel d'éléments
    unsigned int m_tailleMax;     // Capacité actuelle du tableau

};

#endif // CATALOGUE_H