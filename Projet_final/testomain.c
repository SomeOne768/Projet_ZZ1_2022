#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include "ecriture.h"
#include "modelisation_temps.h"
#include "apprentissage.h"
#include "affichageSDL.h"
#include "apparition.h"

int main(int argc, char **argv)
{

    srand(time(NULL));
    /*******************************************************************************/
    // Initialisation de la SDL
    (void)argc;
    (void)argv;

    srand(time(NULL));
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_DisplayMode screen;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
        SDL_Quit();

    SDL_GetCurrentDisplayMode(0, &screen);

    int width = screen.w;
    int height = screen.h;

    /* Création de la fenêtre */
    window = SDL_CreateWindow("Jeu mexicain", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    if (window == NULL)
        end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

    /* Création du renderer */
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

    /* Chargement musique */
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    // changement de l'icône de la fenêtre du jeu
    SDL_Surface *icon;

    // on charge l'image dans la surface
    icon = SDL_LoadBMP("./img/Jalapeno_Red.bmp");

    // on dit qu'on veut l'image prÃ©cÃ©dente comme icÃ´ne
    SDL_SetWindowIcon(window, icon);

    if (TTF_Init() < 0)
        end_sdl(0, "Couldn't initialize SDL TTF", window, renderer);

    TTF_Font *font = NULL;                           // la variable 'police de caractÃ¨re'
    font = TTF_OpenFont("Tacos_de_Tijuana.ttf", 60); // La police Ã  charger, la taille dÃ©sirÃ©e
    if (font == NULL)
        end_sdl(0, "Can't load font", window, renderer);

    /*******************************************************************************/
    /*                      Gestion des variables de jeu                            */
    /*******************************************************************************/

    SDL_Texture *playa = load_texture_from_image("./fonds/fondpix2.xcf", window, renderer);
    SDL_Texture *Elf = load_texture_from_image("./img/elfe.png", window, renderer);
    SDL_Texture *Gobelin = load_texture_from_image("./img/gobelin.png", window, renderer);
    SDL_Texture *Squelette = load_texture_from_image("./img/squelette.png", window, renderer);
    SDL_Texture *Cheztonton = load_texture_from_image("./img/CheztontonMexique.xcf", window, renderer);
    SDL_Texture *Nachos = load_texture_from_image("./img/Nachos.png", window, renderer);
    SDL_Texture *Burrito = load_texture_from_image("./img/Burrito_open.png", window, renderer);
    SDL_Texture *Taco = load_texture_from_image("./img/Taco.png", window, renderer);
    SDL_Texture *Feu = load_texture_from_image("./img/burning_loop_2.png", window, renderer);
    SDL_Texture *Poele = load_texture_from_image("./img/poele.png", window, renderer);
    SDL_Texture *Servi = load_texture_from_image("./img/Tasks_Green.png", window, renderer);
    SDL_Texture *Bulle = load_texture_from_image("./img/pngegg.png", window, renderer);
    SDL_Texture *Kichta = load_texture_from_image("./img/moulaga.png", window, renderer);

    int width_tonton, height_tonton;
    SDL_QueryTexture(Cheztonton, // RÃ©cupÃ©ration des dimensions de l'image
                     NULL, NULL,
                     &width_tonton, &height_tonton);

    // Variables de positionnement
    coordonnee gauche = {0.32 * width, 0.46 * height},
               haut = {0.52 * width, 0.23 * height},
               bas = {0.52 * width, 0.65 * height};
    // printf("width : %d, heigth : %d \n", width, height);
    /*******************************************************************************/
    /*                  PROGRAMME PRINCIPAL                                        */
    /*******************************************************************************/

    // Programme principale
    SDL_Texture *texture_nourriture[3] = {Nachos, Burrito, Taco};

    int presence[3];          // savoir quel(s) emplacement(s) est/sont occupé(s)
    int quisuremplacement[3]; // savoir qui est sur quel emplacement : -1 personne, 0 si elfe, 1 si gobelin, 2 si squelette
    int profitrecompense = 0; // A maximiser
    int tempspreparation = 0; // A minimiser
    int tempspreparationaffichage;
    SDL_Texture *perso[3];                                                                // Pour positionner les images sur les différents emplacements
    int compteurs[NBDEMPLACEMENTS] = {NB_NACHOS_TOTAL, NB_BURRITOS_TOTAL, NB_TACO_TOTAL}; // Nb du plat i restant (stock)
    SDL_Texture *nourriture[3];                                                           // Nourriture associée à un emplacement/client
    int xpoele = 0.009 * width,
        ypoele = 0.31 * height;

    // coordonnées qui indiquent ou positionner l'indicateur de personne servie
    int xservi, yservi;
    int col = 0;
    int plat;
    int periode;
    int stocksrestant;

    int indice_img_feu = 0;

    int compteursvente[NBDEPLATS];
    for (int init = 0; init < NBDEMPLACEMENTS; init++)
    {
        presence[init] = 0;
        quisuremplacement[init] = -1;
    }
    for (int init = 0; init < NBDEPLATS; init++)
    {
        compteursvente[init] = 0;
    }

    SDL_Rect profit_pos;
    profit_pos.x = 0.9 * width;
    profit_pos.y = 0.09 * height;
    SDL_Texture *profit_texture = appliquer_profit(renderer, font, profitrecompense, &profit_pos);

    SDL_bool program_on = SDL_TRUE; // toujours cringe d'utiliser le type bool
    SDL_Event event;
    appliquer_background(playa, window, renderer); // On affiche la toile de picasso
    affiche_nourriture(window, renderer, texture_nourriture);
    SDL_Surface **text_surface = creation_surfaces(compteursvente, font, window, renderer, 5);
    affiche_compteur(window, renderer, text_surface); // Affichage stock
    SDL_RenderCopy(renderer, profit_texture, NULL, &profit_pos);
    appliquer_image(Cheztonton, window, renderer, 1, 1, 0, 0, width / 2 - width_tonton / 2, height / 2 - height_tonton / 2, 1);
    appliquer_image(Kichta, window, renderer, 1, 1, 0, 0, 0.85 * width, 0.1 * height, 0.2);

    SDL_RenderPresent(renderer);
    SDL_Delay(500);
    // int a = ecoulementDesStocks(19);

    double **Matentrainee = init_matrice_cosimienne(192, 6);
    int tempsattente;
    set_t file = initSet(4);
    int indicetableau, coeff;

    while (program_on && !(estfini(compteurs)))
    {

        // Gestion des evenements (agit seulement sur la fermeture de la fenetre)
        while (program_on && SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                program_on = SDL_FALSE;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    program_on = 0;
                    break;

                default:
                    break;
                }
                break;

            default:
                break;
            }
        }

        nouveauxclients(presence);
        for (int i = 0; i < 3; i++)
        {
            quisuremplacement[i] = -1;
        }

        tempsattente = 30;

        // Tracking d'erreur
        printf("tacos :  restant %d, burritos :  restant %d, nachos restant %d \n", compteurs[2], compteurs[1], compteurs[0]);

        // attribution de plat pour les différents emplacement
        quellecommandesurquelemplacement(presence, quisuremplacement, compteurs);

        // Definition de l'état dans lequel on est
        stocksrestant = compteurs[0] + compteurs[1] + compteurs[2];
        periode = ecoulementDesStocks(stocksrestant);
        int ligne = h(periode, quisuremplacement[0], quisuremplacement[1], quisuremplacement[2]);

        // Definition de la meilleure vente/action possible
        col = meilleur_action(Matentrainee, ligne);

        // Vidage fictif de la file
        file.fin = -1;

        // Recupération de la production à réaliser
        insertionfile(col, &file);

        // On sert les clients
        while (tempsattente > 0 && (file.fin >= 0))
        {

            // Tracking d'erreur
            // printf("tacos :  restant %d, burritos :  restant %d, nachos restant %d \n", compteurs[2], compteurs[1], compteurs[0]);

            // Attribution des images sur les différents emplacements
            for (int i = 0; i < 3; i++)
            {
                switch (quisuremplacement[i])
                {
                case 0:
                    perso[i] = Elf;
                    nourriture[i] = Nachos;
                    break;
                case 1:
                    perso[i] = Gobelin;
                    nourriture[i] = Burrito;
                    break;
                case 2:
                    perso[i] = Squelette;
                    nourriture[i] = Taco;
                    break;
                default:
                    perso[i] = NULL;
                    nourriture[i] = NULL;
                    break;
                }
            }

            // // on cherche la ligne de la matrice correspondant
            // printf("%d\n", col);
            // printf("%d\n", file.tab[file.fin]);

            plat = file.tab[file.fin];
            file.fin--;

            // on recherche l'emplacement de la personne qu'on veut servir

            // Recherche de l'emplacement du plat qu'on sert (si +ieur fois le meme plat, on peut attribuer au hasard osef ça change rien pour notre ia)
            indicetableau = 0;
            while (indicetableau < 3 && quisuremplacement[indicetableau] != plat)
            {
                indicetableau++;
            }

            // Methode caca pour la gestion eprte d'argent
            int exprix = profitrecompense;
            service(plat, &profitrecompense, &tempspreparation, compteursvente, &tempsattente, periode);
            if (indicetableau == 3)
            {
                profitrecompense = exprix - (profitrecompense - exprix);
            }

            // Affichage
            // Affichage des elements constant d'une scene (bg + plat)
            appliquer_background(playa, window, renderer);
            affiche_nourriture(window, renderer, texture_nourriture);

            // Affichage de la ez money
            appliquer_image(Kichta, window, renderer, 1, 1, 0, 0, 0.85 * width, 0.1 * height, 0.2);

            text_surface = creation_surfaces(compteursvente, font, window, renderer, plat);
            affiche_compteur(window, renderer, text_surface); // Affichage stock

            // affichage profit
            SDL_DestroyTexture(profit_texture);
            profit_texture = appliquer_profit(renderer, font, profitrecompense, &profit_pos);
            SDL_RenderCopy(renderer, profit_texture, NULL, &profit_pos);
            // Affichage du maxi BG food truck Mexicano
            appliquer_image(Cheztonton, window, renderer, 1, 1, 0, 0, width / 2 - width_tonton / 2, height / 2 - height_tonton / 2, 1);
            appliquer_image(Poele, window, renderer, 1, 1, 0, 0, xpoele, ypoele, 0.5);

            if (perso[0])
            {
                appliquer_image(Bulle, window, renderer, 1, 1, 0, 0, gauche.x + 90, gauche.y - 60, 0.2);
                appliquer_image(nourriture[0], window, renderer, 1, 1, 0, 0, gauche.x + 125, gauche.y - 45, 0.3);
                appliquer_image(perso[0], window, renderer, 3, 4, 0, 1, gauche.x, gauche.y, 4);
            }

            if (perso[1])
            {
                appliquer_image(Bulle, window, renderer, 1, 1, 0, 0, bas.x + 90, bas.y - 60, 0.2);
                appliquer_image(nourriture[1], window, renderer, 1, 1, 0, 0, bas.x + 125, bas.y - 45, 0.3);
                appliquer_image(perso[1], window, renderer, 3, 4, 0, 1, bas.x, bas.y, 4);
            }

            if (perso[2])
            {

                appliquer_image(Bulle, window, renderer, 1, 1, 0, 0, haut.x + 90, haut.y - 60, 0.2);
                appliquer_image(nourriture[2], window, renderer, 1, 1, 0, 0, haut.x + 125, haut.y - 45, 0.3);
                appliquer_image(perso[2], window, renderer, 3, 4, 0, 1, haut.x, haut.y, 4);
            }

            if (indicetableau == 3)
            {

                SDL_RenderPresent(renderer);
                SDL_Delay(1500);
            }
            else
            {

                quisuremplacement[indicetableau] = -1;
                presence[indicetableau] = 0;

                switch (indicetableau)
                {
                case 0:
                    xservi = gauche.x + 54;
                    yservi = gauche.y + 130;
                    break;
                case 1:
                    xservi = bas.x + 54;
                    yservi = bas.y + 130;
                    break;

                case 2:
                    xservi = haut.x + 54;
                    yservi = haut.y + 130;
                    break;

                default:
                    break;
                }

                tempspreparationaffichage = tempspreparation * 100;
                indice_img_feu = 0;
                // afficher l'animation du feu sur la poele pendant qu'un client se fait servir
                while (tempspreparationaffichage > 0)
                {
                    appliquer_image(Feu, window, renderer, 8, 1, 0, indice_img_feu, xpoele + 67, ypoele - 35, 4);
                    // affichage du l'icone indiquant le personnage servi
                    appliquer_image(Servi, window, renderer, 1, 1, 0, 0, xservi, yservi, 0.1);
                    indice_img_feu++;
                    indice_img_feu %= 8;
                    SDL_RenderPresent(renderer);
                    SDL_Delay(200);
                    // printf("temps prep : %d \n", tempspreparation);
                    tempspreparationaffichage -= 100;
                }
            }
        }

        appliquer_background(playa, window, renderer);
        affiche_nourriture(window, renderer, texture_nourriture);
        appliquer_image(Cheztonton, window, renderer, 1, 1, 0, 0, width / 2 - width_tonton / 2, height / 2 - height_tonton / 2, 1);
        appliquer_image(Kichta, window, renderer, 1, 1, 0, 0, 0.85 * width, 0.1 * height, 0.2);
        appliquer_image(Poele, window, renderer, 1, 1, 0, 0, xpoele, ypoele, 0.5);

        text_surface = creation_surfaces(compteursvente, font, window, renderer, plat);
        affiche_compteur(window, renderer, text_surface);
        // affichage profit
        SDL_DestroyTexture(profit_texture);
        profit_texture = appliquer_profit(renderer, font, profitrecompense, &profit_pos);
        SDL_RenderCopy(renderer, profit_texture, NULL, &profit_pos);
        SDL_RenderPresent(renderer);
        SDL_Delay(50);
    }

    /*******************************************************************************/
    /*                          Fermeture du programme                             */
    /*******************************************************************************/

    // /!\ On oubliera pas d'ajouter chaque texture à détruire/malloc a free /!\.
    TTF_CloseFont(font);
    IMG_Quit();
    TTF_Quit();
    SDL_DestroyTexture(playa);
    SDL_DestroyTexture(Elf);
    SDL_DestroyTexture(Gobelin);
    SDL_DestroyTexture(Squelette);
    SDL_DestroyTexture(Cheztonton);
    SDL_DestroyTexture(Nachos);
    SDL_DestroyTexture(Burrito);
    SDL_DestroyTexture(Taco);
    SDL_DestroyTexture(Feu);
    SDL_DestroyTexture(Poele);
    SDL_DestroyTexture(Servi);
    SDL_DestroyTexture(Bulle);
    SDL_DestroyTexture(Kichta);

    return 0;
}