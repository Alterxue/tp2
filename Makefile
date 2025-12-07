# ==============================================================================
# VARIABLES DE CONFIGURATION
# ==============================================================================

# Nom de l'exécutable final requis par le TP
TARGET = trajets

# Compilateur C++
CXX = g++

# Options de compilation OBLIGATOIRES selon le cahier des charges
# CXXFLAGS est utilisé à la fois pour la compilation (-c) et l'édition de liens.
CXXFLAGS = -ansi -pedantic -Wall -std=c++11

# ==============================================================================
# RÈGLES PRINCIPALES
# ==============================================================================

# Règle principale : cible "trajets" dépend de tous les fichiers objets.
trajets: main.o Catalogue.o Trajet.o TrajetCompose.o TrajetSimple.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.o Catalogue.o Trajet.o TrajetCompose.o TrajetSimple.o

# ==============================================================================
# RÈGLES DE COMPILATION DES OBJETS (*.o)
# ==============================================================================

# Compilation du fichier main.cpp (qui contient la fonction principale)
main.o: main.cpp Catalogue.h Trajet.h TrajetCompose.h TrajetSimple.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

# Compilation des classes (fichiers .cpp dépendent de leurs .h et autres .h)
# Pour une simplicité maximale, ils ne dépendent que de leur fichier source.

Catalogue.o: Catalogue.cpp Catalogue.h Trajet.h
	$(CXX) $(CXXFLAGS) -c Catalogue.cpp -o Catalogue.o

Trajet.o: Trajet.cpp Trajet.h
	$(CXX) $(CXXFLAGS) -c Trajet.cpp -o Trajet.o

TrajetCompose.o: TrajetCompose.cpp TrajetCompose.h Trajet.h TrajetSimple.h
	$(CXX) $(CXXFLAGS) -c TrajetCompose.cpp -o TrajetCompose.o

TrajetSimple.o: TrajetSimple.cpp TrajetSimple.h Trajet.h
	$(CXX) $(CXXFLAGS) -c TrajetSimple.cpp -o TrajetSimple.o

# ==============================================================================
# NETTOYAGE
# ==============================================================================

clean:
	rm -f *.o $(TARGET)