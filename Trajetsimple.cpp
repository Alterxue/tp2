/*************************************************************************
                            TrajetSimple - description
                             -------------------
    début           : $DATE$
    copyright       : (C) $YEAR$ par $AUTHOR$
    e-mail          : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <TrajetSimple> (fichier TrajetSimple.h) ----------------
#if ! defined ( TRAJET_SIMPLE_H )
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
    virtual void Afficher() const override;

    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    // Retourne la ville de départ (implémentation polymorphique).
    //
    // Contrat :
    // Ne modifie pas l'objet (const).
    virtual const char * GetVilleDepart() const override;

    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    // Retourne la ville d'arrivée (implémentation polymorphique).
    //
    // Contrat :
    // Ne modifie pas l'objet (const).
    virtual const char * GetVilleArrivee() const override;

    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    // Crée une copie profonde de l'objet TrajetSimple courant. Utilisée par le Catalogue.
    //
    // Contrat :
    // L'appelant est responsable de la libération de la mémoire allouée.
    virtual Trajet* Clone() const override; 


//------------------------------------------------- Surcharge d'opérateurs
    TrajetSimple & operator = ( const TrajetSimple & unTrajetSimple );
    // Mode d'emploi :
    // Opérateur d'affectation pour réaliser une copie profonde de tous les attributs dynamiques
    // (villes, moyen de transport) à partir de unTrajetSimple.
    //
    // Contrat :
    // Assure l'auto-affectation et libère correctement les anciennes ressources avant la copie.


//-------------------------------------------- Constructeurs - destructeur
    TrajetSimple ( const TrajetSimple & unTrajetSimple );
    // Mode d'emploi (constructeur de copie) :
    // Construit un nouvel objet TrajetSimple à partir de unTrajetSimple en effectuant une copie profonde
    // des attributs alloués dynamiquement.
    //
    // Contrat :
    // Appelle le constructeur de copie de la classe mère Trajet.

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
    char * moyenTransport;
    
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

};

//-------------------------------- Autres définitions dépendantes de <TrajetSimple>

#endif // TRAJET_SIMPLE_H