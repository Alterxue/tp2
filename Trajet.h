/*************************************************************************
                           Trajet  -  Classe abstraite représentant un trajet
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Trajet> (fichier Trajet.h) ----------------
#ifndef TRAJET_H

#define TRAJET_H


//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Trajet>
// Classe abstraite servant de base pour la hiérarchie des trajets.
// Définit l'interface commune pour TrajetSimple et TrajetCompose.
// Gère les attributs communs : ville de départ et ville d'arrivée.
//------------------------------------------------------------------------

class Trajet
{
//----------------------------------------------------------------- PUBLIC

    public:
    
    
//----------------------------------------------------- Méthodes publiques
    
    virtual void Afficher() const = 0;
    // Mode d'emploi :
    // Affiche sur la sortie standard les détails complets du Trajet. 
    // Pour un TrajetSimple, affiche les villes et le moyen de transport. 
    // Pour un TrajetCompose, affiche la séquence des sous-trajets.
    //
    // Contrat :
    // Doit être implémentée par chaque classe fille pour son type spécifique.
    // Ne modifie pas l'état de l'objet (const).

    
    virtual const char * GetVilleDepart() const;
    // Mode d'emploi :
    // Retourne un pointeur constant vers la chaîne de caractères représentant la ville de départ du Trajet.
    // Utilisé par le Catalogue pour la recherche et par TrajetCompose pour la validation de l'enchaînement.
    //
    // Contrat :
    // La chaîne de caractères retournée ne doit pas être modifiable (const char *).
    // Ne modifie pas l'état de l'objet (const).
    // Doit renvoyer la ville de départ du premier segment pour un TrajetCompose.

    virtual const char * GetVilleArrivee() const;
    // Mode d'emploi :
    // Retourne un pointeur constant vers la chaîne de caractères représentant la ville d'arrivée du Trajet.
    // Utilisé par le Catalogue pour la recherche et par TrajetCompose pour la validation de l'enchaînement.
    //
    // Contrat :
    // La chaîne de caractères retournée ne doit pas être modifiable (const char *).
    // Ne modifie pas l'état de l'objet (const).
    // Doit renvoyer la ville d'arrivée du dernier segment pour un TrajetCompose.

//-------------------------------------------- Constructeurs - destructeur
    
    Trajet( const char* m_villeDepart, const char* m_villeArrivee );
    // Mode d'emploi :
    // Construit un nouvel objet Trajet. 
    // Il est chargé d'allouer dynamiquement la mémoire pour stocker les noms des villes de départ et d'arrivée.
    // Il ne devrait jamais être appelé directement, car Trajet est abstraite, mais il est appelé par les constructeurs des classes dérivées (TrajetSimple, TrajetCompose).
    //
    // Contrat :
    // Les paramètres doivent être des pointeurs valides (non NULL).
    // La classe doit effectuer une copie profonde (deep copy) des chaînes de caractères fournies.
    // Les classes dérivées appellent ce constructeur pour initialiser la partie mère.

    
    virtual ~Trajet();
    // Mode d'emploi :
    // Libère la mémoire allouée dynamiquement par le constructeur pour stocker les noms des villes (villeDepart et villeArrivee).
    //
    // Contrat :
    // Le mot-clé 'virtual' garantit que si l'objet est supprimé via un pointeur Trajet* (polymorphisme),
    // le destructeur de la classe fille correcte est appelé en premier, puis celui de la classe Trajet.
    // C'est un point CRITIQUE pour éviter les fuites de mémoire dans un contexte d'héritage polymorphique.

    

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

    char * m_villeDepart;
    char * m_villeArrivee;

};

//-------------------------------- Autres définitions dépendantes de <Trajet>

#endif // TRAJET_H

