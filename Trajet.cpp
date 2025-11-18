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
#include "Trajet.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Xxx::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

//-------------------------------------------- Constructeurs - destructeur
Trajet::Trajet (const char* depart, const char* arrivee)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Trajet>" << endl;
#endif
m_villeDepart= new char[strlen(depart)+1];
strcpy(m_villeDepart,depart);
m_villeArrivee= new char[strlen(arrivee)+1];
strcpy(m_villeArrivee,arrivee);
}
 //----- Fin de Xxx


Trajet::~Trajet ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Xxx>" << endl;
#endif
delete[] m_villeDepart;
delete[] m_villeArrivee;
} //----- Fin de ~Xxx 

const char * Trajet::GetVilleDepart() const{
    return m_villeDepart;
}

const char * Trajet::GetVilleArrivee() const{
    return m_villeArrivee;
}

void Trajet::Afficher() const{
    cout << m_villeDepart << "->" << m_villeArrivee << endl;
}
//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
