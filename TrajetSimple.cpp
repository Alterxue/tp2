/*************************************************************************
                            TrajetSimple - Réalisation
                              -------------------
    début                   : 23/11/2025
    copyright               : (C) 2025 par Votre Nom
    e-mail                  : votre.email@exemple.com
*************************************************************************/

//---------- Réalisation de la classe <TrajetSimple> (fichier TrajetSimple.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstring>
//------------------------------------------------------ Include personnel
#include "TrajetSimple.h"
#include "Trajet.h" // Nécessaire pour l'appel au constructeur de la classe mère

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

// CONSTRUCTEUR PARAMÉTRÉ
TrajetSimple::TrajetSimple (const char* villeDepart, const char* villeArrivee, const char* moyenTransport)
    // 1. Appel du constructeur de la classe mère (Trajet)
    : Trajet(villeDepart, villeArrivee)
// Algorithme :
// Stocke les chaînes de caractères fournies. La classe mère Trajet s'occupe de villeDepart et villeArrivee.
// TrajetSimple s'occupe de moyenTransport.
{
#ifdef MAP
    cout << "Appel au constructeur de <TrajetSimple>" << endl;
#endif
    // 2. Allocation et copie de l'attribut propre à TrajetSimple
    m_moyenTransport = new char[strlen(moyenTransport) + 1];
    strcpy(m_moyenTransport, moyenTransport);

} //----- Fin de TrajetSimple (Constructeur paramétré)

// CONSTRUCTEUR DE COPIE (Règle des Trois/Cinq)
TrajetSimple::TrajetSimple (const TrajetSimple & unTrajetSimple)
    // 1. Appel du constructeur de copie de la classe mère Trajet
    : Trajet(unTrajetSimple)
// Algorithme :
// La classe mère gère la copie profonde de villeDepart et villeArrivee.
// TrajetSimple doit gérer la copie profonde de m_moyenTransport.
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <TrajetSimple>" << endl;
#endif
    // 2. Copie profonde de l'attribut m_moyenTransport
    m_moyenTransport = new char[strlen(unTrajetSimple.m_moyenTransport) + 1];
    strcpy(m_moyenTransport, unTrajetSimple.m_moyenTransport);
} //----- Fin de TrajetSimple (Constructeur de copie)

// OPÉRATEUR D'AFFECTATION (Règle des Trois/Cinq)
TrajetSimple & TrajetSimple::operator = (const TrajetSimple & unTrajetSimple)
// Algorithme :
// 1. Test d'auto-affectation.
// 2. Libération des ressources actuelles.
// 3. Appel de l'opérateur d'affectation de la classe mère.
// 4. Copie des nouvelles ressources.
{
    if (this != &unTrajetSimple)
    {
        // 2. Libération de l'attribut propre (m_moyenTransport)
        delete[] m_moyenTransport;

        // 3. Appel à l'opérateur d'affectation de la classe mère (doit être défini dans Trajet)
        Trajet::operator=(unTrajetSimple);

        // 4. Allocation et copie du nouvel attribut m_moyenTransport
        m_moyenTransport = new char[strlen(unTrajetSimple.m_moyenTransport) + 1];
        strcpy(m_moyenTransport, unTrajetSimple.m_moyenTransport);
    }
    return *this;
} //----- Fin de operator =


// DESTRUCTEUR
TrajetSimple::~TrajetSimple ( )
// Algorithme :
// Libère la mémoire allouée dynamiquement pour m_moyenTransport.
// Le destructeur de la classe mère Trajet est appelé automatiquement après pour libérer m_villeDepart et m_villeArrivee.
{
#ifdef MAP
    cout << "Appel au destructeur de <TrajetSimple>" << endl;
#endif
    delete[] m_moyenTransport;
} //----- Fin de ~TrajetSimple

// GETTERS
const char* TrajetSimple::GetVilleDepart() const
{
    return m_villeDepart; // Utilise l'attribut hérité géré par Trajet
}

const char* TrajetSimple::GetVilleArrivee() const
{
    return m_villeArrivee; // Utilise l'attribut hérité géré par Trajet
}

// AFFICHAGE
void TrajetSimple::Afficher() const {
    // La classe mère Trajet n'a pas de corps pour Afficher() puisqu'elle est abstraite.
    // Pour un TrajetSimple, on affiche VilleDepart -> VilleArrivee en MoyenTransport
    cout << m_villeDepart << " en " << m_moyenTransport << " vers " << m_villeArrivee;
} //----- Fin de Afficher

// Méthode de sauvegarde d'un trajet simple dans un flux de sortie (fichier)
// Format exemple : SIMPLE;villeDepart;villeArrivee;moyenTransport
void TrajetSimple::Sauvegarder(std::ostream & os) const
{
    os << "SIMPLE;" << m_villeDepart << ";" << m_villeArrivee << ";" << m_moyenTransport << std::endl;
}

// Méthode statique pour charger un trajet simple depuis un flux
// Retourne un pointeur vers un nouvel objet TrajetSimple ou nullptr si erreur
TrajetSimple* TrajetSimple::Charger(std::istream & is)
{
    std::string ligne;
    if (!std::getline(is, ligne)) return nullptr;
    if (ligne.find("SIMPLE;") != 0) return nullptr;
    size_t pos1 = ligne.find(';');
    size_t pos2 = ligne.find(';', pos1+1);
    size_t pos3 = ligne.find(';', pos2+1);
    if (pos1 == std::string::npos || pos2 == std::string::npos || pos3 == std::string::npos) return nullptr;
    std::string villeDep = ligne.substr(pos1+1, pos2-pos1-1);
    std::string villeArr = ligne.substr(pos2+1, pos3-pos2-1);
    std::string moyen = ligne.substr(pos3+1);
    return new TrajetSimple(villeDep.c_str(), villeArr.c_str(), moyen.c_str()); //construire un new trajet simple et return it
}