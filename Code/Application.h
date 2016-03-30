#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED

// Fonction permettant d'initialiser SDL, la fen�tre et le jeu
int init(const char* title, int width, int height);

// Fonction permettant de quitter proprement
void quit();

// Fonction permettant de g�rer les entr�es de l'utilisateur
void handleEvents();

// Fonction permettant de g�rer l'intelligence des entit�s
void update();

// Fonction permettant de rendre l'int�gralit� du jeu
void render();

// Fonction principale du programme
void run();

#endif // APPLICATION_H_INCLUDED
