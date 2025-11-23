/*************************************************************************
                           Xxx  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Xxx> (fichier Xxx.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstring>
//------------------------------------------------------ Include personnel
#include "TrajetSimple.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Xxx::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

TrajetSimple::TrajetSimple (const char* villeDepart, const char* villeArrivee, const char* moyenTransport
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Xxx>" << endl;
#endif
m_villeDepart= new char[strlen(villeDepart)+1];
strcpy(m_villeDepart,villeDepart);
m_villeArrivee= new char[strlen(villeArrivee)+1];
strcpy(m_villeArrivee,villeArrivee);
m_moyenTransport= new char[strlen(moyenTransport)+1];
strcpy(m_moyenTransport,moyenTransport);
}
//----- Fin de Xxx


TrajetSimple::~TrajetSimple ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Xxx>" << endl;
#endif
delete[] m_villeDepart;
delete[] m_villeArrivee;
delete[] m_moyenTransport;
} //----- Fin de ~Xxx

const char* TrajetSimple::GetVilleDepart() const
{
    return m_villeDepart;
}

const char* TrajetSimple::GetVilleArrivee() const
{
    return m_villeArrivee;
}

void TrajetSimple::Afficher() const {
    Trajet::Afficher();
    cout << " en " << m_moyenTransport << endl;
}
//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
