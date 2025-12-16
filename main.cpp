/*************************************************************************
                           Main - Interactive
                             -------------------
    début                : 23/11/2025
    copyright            : (C) 2025 par Votre Nom
*************************************************************************/

//-------------------------------------------------------- Include système
#include <iostream>
#include <cstring>

using namespace std;

//------------------------------------------------------ Include personnel
#include "Trajet.h"
#include "TrajetSimple.h"
#include "TrajetCompose.h"
#include "Catalogue.h"

//------------------------------------------------------------- Constantes
const int MAX_STRING = 100; // Taille max pour les noms de villes/transports

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
    cout << "Note: Pour les villes a plusieurs mots, utilisez '_'" << endl;
    cout << "      Exemple: Le_Havre, New_York, Saint_Etienne" << endl;
    cout << "=======================================================" << endl;

    while (choix != 0)
    {
        cout << endl << "---------------- MENU ----------------" << endl;
        cout << "1. Ajouter un Trajet Simple" << endl;
        cout << "2. Ajouter un Trajet Compose" << endl;
        cout << "3. Afficher le Catalogue" << endl;
        cout << "4. Recherche Simple (Trajet direct)" << endl;
        cout << "5. Recherche Avancee (Combinaison)" << endl;
        cout << "6. Sauvegarder le Catalogue dans un fichier" << endl;
        cout << "7. Charger des trajets depuis un fichier" << endl;
        cout << "0. Quitter" << endl;
        cout << "--------------------------------------" << endl;
        cout << "Votre choix : ";
        
        cin >> choix;

        // Si l'entrée n'est pas un nombre
        if(cin.fail()) {
            cout << "Erreur : Veuillez entrer un nombre." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            choix = -1;
            continue;
        }

        cout << endl;

        switch (choix)
        {
            case 1: // Ajouter Trajet Simple
            {
                cout << ">> AJOUT TRAJET SIMPLE" << endl;
                cout << "Ville de depart : ";
                cin >> depart;
                cout << "Ville d'arrivee : ";
                cin >> arrivee;
                cout << "Moyen de transport : ";
                cin >> transport;

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
                    cin >> depart;
                    cout << "Ville d'arrivee : ";
                    cin >> arrivee;
                    cout << "Moyen de transport : ";
                    cin >> transport;

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
                cin >> depart;
                cout << "Ville d'arrivee : ";
                cin >> arrivee;
                
                catalogue.Rechercher(depart, arrivee);
                break;
            }

            case 5: // Recherche Avancée
            {
                cout << ">> RECHERCHE AVANCEE" << endl;
                cout << "Ville de depart : ";
                cin >> depart;
                cout << "Ville d'arrivee : ";
                cin >> arrivee;

                catalogue.RechercherAvance(depart, arrivee);
                break;
            }

            case 6: // Sauvegarder le catalogue
            {
                cout << ">> SAUVEGARDE DU CATALOGUE" << endl;
                char nomFichier[MAX_STRING];
                cout << "Nom du fichier de sauvegarde : ";
                cin >> nomFichier;
                cout << "Mode de sauvegarde (0: tout, 1: simples, 2: composes, 3: par ville, 4: intervalle) : ";
                int mode; cin >> mode;
                char villeDep[MAX_STRING] = "", villeArr[MAX_STRING] = "";
                int n = -1, m = -1;
                if (mode == 3) {
                    cout << "Ville de depart (ou - pour ignorer) : "; cin >> villeDep;
                    cout << "Ville d'arrivee (ou - pour ignorer) : "; cin >> villeArr;
                    catalogue.Sauvegarder(nomFichier, mode, strcmp(villeDep,"-")==0?nullptr:villeDep, strcmp(villeArr,"-")==0?nullptr:villeArr);
                } else if (mode == 4) {
                    cout << "Indice debut (0-base) : "; cin >> n;
                    cout << "Indice fin (0-base) : "; cin >> m;
                    catalogue.Sauvegarder(nomFichier, mode, nullptr, nullptr, n, m);
                } else {
                    catalogue.Sauvegarder(nomFichier, mode);
                }
                cout << "Catalogue sauvegarde dans " << nomFichier << endl;
                break;
            }

            case 7: // Charger des trajets
            {
                cout << ">> CHARGEMENT DE TRAJETS" << endl;
                char nomFichier[MAX_STRING];
                cout << "Nom du fichier a charger : ";
                cin >> nomFichier;
                cout << "Mode de chargement (0: tout, 1: simples, 2: composes, 3: par ville, 4: intervalle) : ";
                int mode; cin >> mode;
                char villeDep[MAX_STRING] = "", villeArr[MAX_STRING] = "";
                int n = -1, m = -1;
                if (mode == 3) {
                    cout << "Ville de depart (ou - pour ignorer) : "; cin >> villeDep;
                    cout << "Ville d'arrivee (ou - pour ignorer) : "; cin >> villeArr;
                    catalogue.Charger(nomFichier, mode, strcmp(villeDep,"-")==0?nullptr:villeDep, strcmp(villeArr,"-")==0?nullptr:villeArr);
                } else if (mode == 4) {
                    cout << "Indice debut (0-base) : "; cin >> n;
                    cout << "Indice fin (0-base) : "; cin >> m;
                    catalogue.Charger(nomFichier, mode, nullptr, nullptr, n, m);
                } else {
                    catalogue.Charger(nomFichier, mode);
                }
                cout << "Chargement termine depuis " << nomFichier << endl;
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