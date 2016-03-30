#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED

// Fonction permettant d'initialiser SDL, la fenêtre et le jeu
int init(const char* title, int width, int height);

// Fonction permettant de quitter proprement
void quit();

// Fonction permettant de gérer les entrées de l'utilisateur
void handleEvents();

// Fonction permettant de gérer l'intelligence des entités
void update();

// Fonction permettant de rendre l'intégralité du jeu
void render();

// Fonction principale du programme
void run();

#endif // APPLICATION_H_INCLUDED
