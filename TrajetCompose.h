/*************************************************************************
                            TrajetCompose - description
                             -------------------
    début           : $DATE$
    copyright       : (C) $YEAR$ par $AUTHOR$
    e-mail          : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <TrajetCompose> (fichier TrajetCompose.h) ----------------
#ifndef TRAJET_COMPOSE_H
#define TRAJET_COMPOSE_H

//--------------------------------------------------- Interfaces utilisées
#include "Trajet.h"
#include "TrajetSimple.h" // Nécessaire pour manipuler des objets TrajetSimple* dans la collection

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <TrajetCompose>
// La classe TrajetCompose représente un parcours formé d'une séquence ordonnée
// de Trajets Simples. Elle garantit l'enchaînement des villes et est stockée
// dans le Catalogue de manière polymorphique.
//
//------------------------------------------------------------------------

class TrajetCompose : public Trajet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    // Implémentation polymorphique de l'affichage. Affiche la séquence ordonnée des sous-trajets.
    //
    // Contrat :
    // Ne modifie pas l'objet (const). Doit appeler l'Afficher() de chaque sous-trajet.
    virtual void Afficher() const override;

    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    // Retourne la ville de départ du premier TrajetSimple de la séquence (implémentation polymorphique).
    //
    // Contrat :
    // Ne modifie pas l'objet (const).
    virtual const char * GetVilleDepart() const;

    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    // Retourne la ville d'arrivée du dernier TrajetSimple de la séquence (implémentation polymorphique).
    //
    // Contrat :
    // Ne modifie pas l'objet (const).
    virtual const char * GetVilleArrivee() const;

    
    
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    // Ajoute un TrajetSimple à la séquence, vérifiant immédiatement la contrainte d'enchaînement.
    // La méthode alloue plus de mémoire pour la collection interne si nécessaire.
    //
    // Contrat :
    // Le TrajetSimple fourni doit être alloué dynamiquement (sera géré par TrajetCompose).
    // La ville de départ du nouveau trajet doit être l'arrivée du précédent.
    void AjouterTrajet(TrajetSimple* unTrajet);


//------------------------------------------------- Surcharge d'opérateurs
    TrajetCompose & operator = ( const TrajetCompose & unTrajetCompose );
    // Mode d'emploi :
    // Opérateur d'affectation pour réaliser une copie profonde de tous les sous-trajets du TrajetCompose.
    //
    // Contrat :
    // Assure l'auto-affectation, libère correctement les anciennes ressources avant la copie
    // et recopie en profondeur la collection interne et tous les objets pointés.


//-------------------------------------------- Constructeurs - destructeur
    TrajetCompose ( const TrajetCompose & unTrajetCompose );
    // Mode d'emploi (constructeur de copie) :
    // Construit un nouvel objet TrajetCompose en effectuant une copie profonde de tous les sous-trajets.
    //
    // Contrat :
    // Appelle le constructeur de la classe mère Trajet.
    // Copie en profondeur chaque TrajetSimple de la collection.

    TrajetCompose ( );
    // Mode d'emploi :
    // Constructeur par défaut. Initialise la structure de la collection interne (vide).
    //
    // Contrat :
    // Appelle le constructeur par défaut de la classe mère Trajet.

    virtual ~TrajetCompose ( );
    // Mode d'emploi (Destructeur) :
    // Libère la mémoire allouée dynamiquement pour les sous-trajets (les TrajetSimple*).
    // Libère ensuite la structure de la collection interne (le tableau de pointeurs).
    // Le destructeur virtuel de la classe mère sera appelé après celui-ci.
    //
    // Contrat :
    // Assure la libération de toutes les ressources dynamiques propres à TrajetCompose.

//------------------------------------------------------------------ PRIVE

protected:
    // La collection interne pour stocker les TrajetSimple* (votre "liste chaînée")
    TrajetSimple** m_collectionTrajets; 
    
    // Nombre actuel de trajets dans la collection
    unsigned int m_nbTrajets;
    
    // Taille maximale actuelle du tableau (capacité)
    unsigned int m_tailleMax;
    
    // Vous pouvez conserver les villes de départ/arrivée héritées de Trajet
    // pour des raisons d'implémentation, mais vous ne les gérez pas directement ici.

//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

};

//-------------------------------- Autres définitions dépendantes de <TrajetCompose>

#endif // TRAJET_COMPOSE_H