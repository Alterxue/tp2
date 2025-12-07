/*************************************************************************
                           Main - Interactive
                             -------------------
    début                : 23/11/2025
    copyright            : (C) 2025 par Votre Nom
*************************************************************************/

//-------------------------------------------------------- Include système
#include <iostream>
#include <cstring>
#include <limits> // Pour vide le buffer cin

using namespace std;

//------------------------------------------------------ Include personnel
#include "Trajet.h"
#include "TrajetSimple.h"
#include "TrajetCompose.h"
#include "Catalogue.h"

//------------------------------------------------------------- Constantes
const int MAX_STRING = 100; // Taille max pour les noms de villes/transports

//------------------------------------------------------------- Fonctions Utilitaires
// Vide le buffer d'entrée pour éviter les bugs si l'utilisateur tape n'importe quoi
void viderBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Lit une chaîne de caractères (avec ou sans espaces)
void lireChaine(char* buffer) {
    cin.getline(buffer, MAX_STRING);
}

//------------------------------------------------------------------ Main

int main()
{
    Catalogue catalogue;
    int choix = -1;
    char depart[MAX_STRING];
    char arrivee[MAX_STRING];
    char transport[MAX_STRING];

    cout << "=======================================================" << endl;
    cout << "      GESTIONNAIRE DE TRAJETS (Mode Interactif)" << endl;
    cout << "=======================================================" << endl;

    while (choix != 0)
    {
        cout << endl << "---------------- MENU ----------------" << endl;
        cout << "1. Ajouter un Trajet Simple" << endl;
        cout << "2. Ajouter un Trajet Compose" << endl;
        cout << "3. Afficher le Catalogue" << endl;
        cout << "4. Recherche Simple (Trajet direct)" << endl;
        cout << "5. Recherche Avancee (Combinaison)" << endl;
        cout << "0. Quitter" << endl;
        cout << "--------------------------------------" << endl;
        cout << "Votre choix : ";
        
        cin >> choix;

        // Si l'entrée n'est pas un nombre
        if(cin.fail()) {
            cout << "Erreur : Veuillez entrer un nombre." << endl;
            viderBuffer();
            choix = -1; // Force le redémarrage de la boucle
            continue;
        }

        cout << endl;

        switch (choix)
        {
            case 1: // Ajouter Trajet Simple
            {
                cout << ">> AJOUT TRAJET SIMPLE" << endl;
                cout << "Ville de depart : ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.getline(depart, MAX_STRING);
                cout << "Ville d'arrivee : ";
                cin.getline(arrivee, MAX_STRING);
                cout << "Moyen de transport : ";
                cin.getline(transport, MAX_STRING);

                // Création et ajout
                catalogue.Ajouter(new TrajetSimple(depart, arrivee, transport));
                cout << "Trajet simple ajoute avec succes !" << endl;
                break;
            }

            case 2: // Ajouter Trajet Composé
            {
                cout << ">> AJOUT TRAJET COMPOSE" << endl;
                TrajetCompose* tc = new TrajetCompose();
                bool continuer = true;
                int nbrEtapes = 0;

                while (continuer) {
                    cout << "--- Etape " << (nbrEtapes + 1) << " ---" << endl;
                    cout << "Ville de depart : ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.getline(depart, MAX_STRING);
                    cout << "Ville d'arrivee : ";
                    cin.getline(arrivee, MAX_STRING);
                    cout << "Moyen de transport : ";
                    cin.getline(transport, MAX_STRING);

                    TrajetSimple* ts = new TrajetSimple(depart, arrivee, transport);
                    
                    // On tente d'ajouter. Note : Votre TrajetCompose doit gérer la vérification
                    // Si c'est la 1ere étape, ça marche toujours.
                    // Sinon, il faut que ts.depart == tc.derniereArrivee
                    
                    // ASTUCE : Pour que l'utilisateur ne se trompe pas, on pourrait 
                    // pré-remplir la ville de départ avec la ville d'arrivée précédente
                    // mais ici je laisse l'utilisateur saisir pour tester votre méthode AjouterTrajet.
                    
                    // Attention : La méthode AjouterTrajet dans votre code précédent est void
                    // et affiche une erreur sur cerr si ça échoue.
                    tc->AjouterTrajet(ts); 
                    nbrEtapes++;

                    cout << "Ajouter une autre etape a ce trajet ? (1: Oui, 0: Non) : ";
                    int sousChoix;
                    cin >> sousChoix;
                    if (sousChoix == 0) continuer = false;
                }

                catalogue.Ajouter(tc);
                cout << "Trajet compose finalise et ajoute au catalogue." << endl;
                break;
            }

            case 3: // Afficher
            {
                cout << ">> CONTENU DU CATALOGUE" << endl;
                catalogue.Afficher();
                break;
            }

            case 4: // Recherche Simple
            {
                cout << ">> RECHERCHE SIMPLE" << endl;
                cout << "Ville de depart : ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.getline(depart, MAX_STRING);
                cout << "Ville d'arrivee : ";
                cin.getline(arrivee, MAX_STRING);
                
                catalogue.Rechercher(depart, arrivee);
                break;
            }

            case 5: // Recherche Avancée
            {
                cout << ">> RECHERCHE AVANCEE" << endl;
                cout << "Ville de depart : ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.getline(depart, MAX_STRING);
                cout << "Ville d'arrivee : ";
                cin.getline(arrivee, MAX_STRING);

                catalogue.RechercherAvance(depart, arrivee);
                break;
            }

            case 0:
                cout << "Au revoir !" << endl;
                break;

            default:
                cout << "Choix invalide. Veuillez recommencer." << endl;
                break;
        }
    }

    return 0;
}