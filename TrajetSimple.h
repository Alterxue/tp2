/*************************************************************************
                            TrajetSimple - description
                             -------------------
    début           : $DATE$
    copyright       : (C) $YEAR$ par $AUTHOR$
    e-mail          : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <TrajetSimple> (fichier TrajetSimple.h) ----------------
#ifndef TRAJET_SIMPLE_H
#define TRAJET_SIMPLE_H

//--------------------------------------------------- Interfaces utilisées
#include "Trajet.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <TrajetSimple>
// La classe TrajetSimple représente un trajet direct entre une ville de départ 
// et une ville d'arrivée, effectué via un unique moyen de transport.
// Elle hérite de Trajet et implémente les méthodes virtuelles pures de la classe mère.
//
//------------------------------------------------------------------------

class TrajetSimple : public Trajet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    // Implémentation polymorphique de l'affichage. Affiche les villes et le moyen de transport.
    //
    // Contrat :
    // Ne modifie pas l'objet (const).
    virtual void Afficher() const;

    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    // Retourne la ville de départ (implémentation polymorphique).
    //
    // Contrat :
    // Ne modifie pas l'objet (const).
    virtual const char * GetVilleDepart() const;

    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    // Retourne la ville d'arrivée (implémentation polymorphique).
    //
    // Contrat :
    // Ne modifie pas l'objet (const).
    virtual const char * GetVilleArrivee() const;

    


//-------------------------------------------- Constructeurs - destructeur
    TrajetSimple ( const char* villeDepart, const char* villeArrivee, const char* moyenTransport );
    // Mode d'emploi :
    // Construit et initialise un TrajetSimple avec les villes et le moyen de transport spécifiés.
    // Alloue la mémoire pour copier les chaînes de caractères fournies.
    //
    // Contrat :
    // Les paramètres doivent être des pointeurs valides (non NULL).

    virtual ~TrajetSimple ( );
    // Mode d'emploi :
    // Destructeur. Libère la mémoire allouée dynamiquement pour le moyen de transport.
    // Le destructeur virtuel de la classe mère sera appelé automatiquement après celui-ci.
    //
    // Contrat :
    // Assure la libération de toutes les ressources dynamiques propres à TrajetSimple.

//------------------------------------------------------------------ PRIVE

protected:
    // Attributs spécifiques à TrajetSimple : le moyen de transport
    char * m_moyenTransport;
    
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

};

//-------------------------------- Autres définitions dépendantes de <TrajetSimple>

#endif // TRAJET_SIMPLE_H