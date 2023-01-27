#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "affichageSDL.h"
#include "apparition.h"
#include "modelisation_temps.h"
#include "ecriture.h"
#include "apprentissage.h"
#include <SDL2/SDL_mixer.h>
#include "affichage_laby.h"
#include "labyrinthe.h"

char *filename = "labyrinthe/monde6.txt";
char *apprentissage = "labyrinthe/Laby_monde6.txt";

// FUTUR POUR BABETHE
// MUSIQUE MARIO KART POUR ANTONIO
// MUSIQUE MEXICAINE UR COCO

// commenter ligne 265 pour comportement nul

/*******************************************************************************/
/*       PROGRAMME DE LIVRAISON DE TACOS/NACHOS/BURRITOS                       */
/*      Gobelin: burritos;  Squelette: tacos; Elf: nachos                      */
/* Codage des plats:                                                           */
/*  -Nachos: 0                                                                 */
/*  -Burritos: 1                                                               */
/*  -Tacos: 2                                                                  */
/*  -Null: 3                                                                   */
/*******************************************************************************/

/*******************************************************************************/
/*                  Definition des matrices d'états                            */
/*******************************************************************************/
// Se situe dans modelisation.h
//  float M[64][3];
//  init_matrice(M);

void choixservice(int *presence, int *quiservir, int *quisuremplacement, int *tempsattente, int *tempspreparation, int *profitrecompense, int *compteursvente, int *xservi, int *yservi, coordonnee gauche, coordonnee haut, coordonnee bas)
{

    // fonction sale et en plus je l'ai mise dans le main
    // p'tin mais si elle est sale fais lui prendre une douche tu abuses !
    // Si tu l'as mise dans ta main j'espere que tu mets bien du desinfectant au RU avant de manger !
    int trouve = 0;
    for (int i = 0; i < NBDEMPLACEMENTS; i++)
    {
        if (quisuremplacement[i] == 0 && (*tempsattente) >= 8 && !(trouve))
        {
            (*quiservir) = i;
            trouve = 1;
        }
    }
    if (!(trouve))
    {
        for (int i = 0; i < NBDEMPLACEMENTS; i++)
        {
            if (quisuremplacement[i] == 1 && (*tempsattente) >= 22 && !(trouve))
            {
                (*quiservir) = i;
                trouve = 1;
            }
        }
    }
    if (!(trouve))
    {
        for (int i = 0; i < NBDEMPLACEMENTS; i++)
        {
            if (quisuremplacement[i] == 2 && (*tempsattente) >= 30 && !(trouve))
            {
                (*quiservir) = i;
                trouve = 1;
            }
        }
    }
    if (!(trouve))
    {
        (*tempsattente) = 0;
        (*tempspreparation) = 0;
    }

    if (trouve)
    {
        service(quisuremplacement[(*quiservir)], profitrecompense, tempspreparation, compteursvente, tempsattente, 0);
        // détermine les coordonnées pour afficher le petit icone vert
        switch ((*quiservir))
        {
        case 0:
            (*xservi) = gauche.x + 54;
            (*yservi) = gauche.y + 130;
            break;
        case 1:
            (*xservi) = bas.x + 54;
            (*yservi) = bas.y + 130;
            break;

        case 2:
            (*xservi) = haut.x + 54;
            (*yservi) = haut.y + 130;
            break;

        default:
            break;
        }

        presence[(*quiservir)] = 0;
        quisuremplacement[(*quiservir)] = -1;
    }
}

int main(int argc, char **argv)
{

    /*******************************************************************************/
    // Initialisation de la SDL
    (void)argc;
    (void)argv;

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

    // on dit qu'on veut l'image precedente comme icone
    SDL_SetWindowIcon(window, icon);

    if (TTF_Init() < 0)
        end_sdl(0, "Couldn't initialize SDL TTF", window, renderer);

    TTF_Font *font = NULL;                           // la variable 'police de caractere'
    font = TTF_OpenFont("Tacos_de_Tijuana.ttf", 60); // La police a charger, la taille desiree
    if (font == NULL)
        end_sdl(0, "Can't load font", window, renderer);

    // Mix_Music *music = Mix_LoadMUS("sonne.mp3");
    Mix_Music *MusiqueMexique = Mix_LoadMUS("./mariachi.mp3");
    Mix_PlayMusic(MusiqueMexique, 0);

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
    SDL_Texture *Crabe = load_texture_from_image("./img/srek.png", window, renderer);
    SDL_Texture *Heure = load_texture_from_image("./img/horaire.png", window, renderer);
    SDL_Texture *Srab = load_texture_from_image("./img/srek.png", window, renderer);
    SDL_Texture *bouff;
    SDL_Texture *goal = load_texture_from_image("img/goal2.png", window, renderer);
    SDL_Texture *wall = load_texture_from_image("img/wall2.png", window, renderer);
    SDL_Texture *persoAchat = load_texture_from_image("img/srek.png", window, renderer);
    SDL_Texture *road = load_texture_from_image("img/road2.png", window, renderer);
    int width_tonton, height_tonton;
    SDL_QueryTexture(Cheztonton, // Recuperation des dimensions de l'image
                     NULL, NULL,
                     &width_tonton, &height_tonton);

    // Variables de positionnement
    coordonnee gauche = {0.22 * width, 0.46 * height},
               haut = {0.72 * width, 0.28 * height},
               bas = {0.62 * width, 0.78 * height};

    int w_perso, h_perso;
    SDL_QueryTexture(Elf, // Récupération des dimensions de l'image
                     NULL, NULL,
                     &w_perso, &h_perso);
    // coordonnee gauche = {0.32 * width, 0.46 * height},
    //            haut = {0.52 * width, 0.32 * height},
    //            bas = {0.52 * width, 0.60 * height};

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
    int plat;
    int col;
    int vitesse;

    int stocksrestant;
    // coordonnées qui indiquent ou positionner l'indicateur de personne servie
    int xservi, yservi;

    int periode = 0; // entier qui représente le moment de la journée (0 : matin; 1 : midi ; 2 : soir)
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
    // on met platdistribue = 5 pour avoir l'écriture en noir (il faut >3 pour qu'il n'y ait jamais de rouge affiché)
    affiche_compteur(window, renderer, text_surface); // Affichage stock
    LibererCompteur(&text_surface);
    SDL_RenderCopy(renderer, profit_texture, NULL, &profit_pos);
    appliquer_image(Cheztonton, window, renderer, 1, 1, 0, 0, width / 2 - width_tonton / 2, height / 2 - height_tonton / 2, 1);
    appliquer_image(Kichta, window, renderer, 1, 1, 0, 0, 0.85 * width, 0.1 * height, 0.2);
    appliquer_image(Crabe, window, renderer, 1, 1, 0, 0, 100, 800, 0.3);
    appliquer_image(Heure, window, renderer, 3, 1, 0, periode, 140, 745, 2);
    appliquer_image(Poele, window, renderer, 1, 1, 0, 0, xpoele, ypoele, 0.5);

    SDL_RenderPresent(renderer);
    // SDL_Delay(1000);

    // Gestion de la vente de plat
    double **Matentrainee = init_matrice_cosimienne(192, 6);
    chargerMatrice(Matentrainee, 192, 6, "esclavagisme.txt");
    int tempsattente;
    set_t file = initSet(4);
    int indicetableau;

    // Gestion de l'achat de nouveau stock
    int n, m;

    // char **M1 = init_matrice_labyrinthe(filename, &n, &m);
    // char **M2 = malloc(sizeof(char *) * n);
    // for (int i = 0; i < n; i++)
    // {
    //     M2[i] = malloc(sizeof(char *) * m);
    //     for (int j = 0; j < m; j++)
    //     {
    //         M2[i][j] = M1[i][j];
    //     }
    // }

    // double **Cosimienne = init_matrice_cosimienne(n * m, 4);
    // chargerMatrice(Cosimienne, n * m, 4, apprentissage);
    // copiage(M1, M2, n, m);

    int achat = 0;
    int fini=0;
     int stocktotal = NB_TACO_TOTAL + NB_BURRITOS_TOTAL + NB_BURRITOS_TOTAL;

    while (program_on &&!fini)
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

        if (!achat)
        {
            nouveauxclients(presence);
            for (int i = 0; i < 3; i++)
            {
                quisuremplacement[i] = -1;
            }

            tempsattente = 30;

            // Tracking d'erreur
            // printf("tacos :  restant %d, burritos :  restant %d, nachos restant %d \n", compteurs[2], compteurs[1], compteurs[0]);

            // attribution de plat pour les différents emplacement
            quellecommandesurquelemplacement(presence, quisuremplacement, compteurs);

            // Definition de l'état dans lequel on est
            stocksrestant = compteurs[0] + compteurs[1] + compteurs[2];
            periode = ecoulementDesStocks(stocksrestant,  stocktotal);
            int ligne = h(periode, quisuremplacement[0], quisuremplacement[1], quisuremplacement[2]);

            // Definition de la meilleure vente/action possible
            if(!Matentrainee){
                printf("Probleme !!\n");exit(-1);
            }
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

                plat = file.tab[file.fin];
                file.fin--;

                // fonction sale et en plus je l'ai mise dans le main
                // p'tin mais si elle est sale fais lui prendre une douche tu abuses !
                // Si tu l'as mise dans ta main j'espere que tu mets bien du desinfectant au RU avant de manger !

                indicetableau = 0;
                while (indicetableau < 3 && quisuremplacement[indicetableau] != plat)
                {
                    indicetableau++;
                }

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
                LibererCompteur(&text_surface);

                // affichage profit
                SDL_DestroyTexture(profit_texture);
                profit_texture = appliquer_profit(renderer, font, profitrecompense, &profit_pos);
                SDL_RenderCopy(renderer, profit_texture, NULL, &profit_pos);
                // Affichage du maxi BG food truck Mexicano
                appliquer_image(Cheztonton, window, renderer, 1, 1, 0, 0, width / 2 - width_tonton / 2, height / 2 - height_tonton / 2, 1);
                appliquer_image(Poele, window, renderer, 1, 1, 0, 0, xpoele, ypoele, 0.5);

                appliquer_image(Crabe, window, renderer, 1, 1, 0, 0, 100, 800, 0.3);
                appliquer_image(Heure, window, renderer, 3, 1, 0, periode, 140, 745, 2);

                if (perso[0])
                {
                    appliquer_image(Bulle, window, renderer, 1, 1, 0, 0, gauche.x + 90, gauche.y - 60, 0.2);
                    appliquer_image(nourriture[0], window, renderer, 1, 1, 0, 0, gauche.x + 125, gauche.y - 45, 0.3);
                    appliquer_image(perso[0], window, renderer, 3, 4, 2, 1, gauche.x, gauche.y, 4);
                }

                if (perso[1])
                {
                    appliquer_image(Bulle, window, renderer, 1, 1, 0, 0, bas.x + 90, bas.y - 60, 0.2);
                    appliquer_image(nourriture[1], window, renderer, 1, 1, 0, 0, bas.x + 125, bas.y - 45, 0.3);
                    appliquer_image(perso[1], window, renderer, 3, 4, 3, 1, bas.x, bas.y, 4);
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
                    SDL_Delay(50); // SDL_Delay(1500);
                }
                else
                {
                    bouff = nourriture[indicetableau];
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

                    tempspreparationaffichage = tempspreparation * 100; // temps = 8 ou 22 ou 30
                    indice_img_feu = 0;

                    // afficher l'animation du feu sur la poele pendant qu'un client se fait servir
                    int nb_passage = tempspreparation;                // == tempspreparationaffichage / 100; car temp.. decrementer de 100 à chaque passage
                    vitesse = tempspreparationaffichage / nb_passage; // On souhaite qu'il se deplace vers la bas
                    // float x_depart = width / 2,
                    //       y_depart = height / 2,
                    //       dx_livreur = xservi-x_depart -54,
                    //       dy_livreur = yservi-y_depart -130,
                    //       dx_it = dx_livreur / nb_passage,
                    //       dy_it = dy_livreur / nb_passage,
                    //       it = 0;
                    float x_depart = width / 2,
                          y_depart = height / 2,
                          dx_livreur = xservi - x_depart,
                          dy_livreur = yservi - y_depart;
                    dx_livreur += (indicetableau != 0) ? 150 : -150;
                    dy_livreur += (indicetableau == 0) ? 0 : -50;
                    float
                        dx_it = dx_livreur / nb_passage,
                        dy_it = dy_livreur / nb_passage,
                        it = 0;
                    float zoom_kichta = 0.3;

                    appliquer_image(Srab, window, renderer, 1, 1, 0, 0, x_depart - 50, y_depart - 50, 0.3);
                    appliquer_image(bouff, window, renderer, 1, 1, 0, 0, x_depart, y_depart, 0.3);

                    // 3 itérations pour aller vers le client et 3 pour revenir
                    while (tempspreparationaffichage > 0)
                    {
                        if (it < (nb_passage / 2))
                        {
                            // On se deplace vers le client
                            x_depart += dx_it;
                            y_depart += dy_it;
                        }
                        else
                        {
                            // On retourne au camion
                            x_depart -= dx_it;
                            y_depart -= dy_it;
                            bouff = Kichta;
                            zoom_kichta = 0.1;
                        }

                        appliquer_background(playa, window, renderer);
                        affiche_nourriture(window, renderer, texture_nourriture);

                        // Affichage de la ez money
                        appliquer_image(Kichta, window, renderer, 1, 1, 0, 0, 0.85 * width, 0.1 * height, 0.2);

                        text_surface = creation_surfaces(compteursvente, font, window, renderer, plat);
                        affiche_compteur(window, renderer, text_surface); // Affichage stock
                        LibererCompteur(&text_surface);

                        // affichage profit
                        SDL_DestroyTexture(profit_texture);
                        profit_texture = appliquer_profit(renderer, font, profitrecompense, &profit_pos);
                        SDL_RenderCopy(renderer, profit_texture, NULL, &profit_pos);
                        // Affichage du maxi BG food truck Mexicano
                        appliquer_image(Cheztonton, window, renderer, 1, 1, 0, 0, width / 2 - width_tonton / 2, height / 2 - height_tonton / 2, 1);
                        appliquer_image(Poele, window, renderer, 1, 1, 0, 0, xpoele, ypoele, 0.5);
                        appliquer_image(Crabe, window, renderer, 1, 1, 0, 0, 100, 800, 0.3);
                        appliquer_image(Heure, window, renderer, 3, 1, 0, periode, 140, 745, 2);

                        if (perso[0])
                        {
                            appliquer_image(Bulle, window, renderer, 1, 1, 0, 0, gauche.x + 90, gauche.y - 60, 0.2);
                            appliquer_image(nourriture[0], window, renderer, 1, 1, 0, 0, gauche.x + 125, gauche.y - 45, 0.3);
                            appliquer_image(perso[0], window, renderer, 3, 4, 2, 1, gauche.x, gauche.y, 4);
                        }

                        if (perso[1])
                        {
                            appliquer_image(Bulle, window, renderer, 1, 1, 0, 0, bas.x + 90, bas.y - 60, 0.2);
                            appliquer_image(nourriture[1], window, renderer, 1, 1, 0, 0, bas.x + 125, bas.y - 45, 0.3);
                            appliquer_image(perso[1], window, renderer, 3, 4, 3, 1, bas.x, bas.y, 4);
                        }

                        if (perso[2])
                        {

                            appliquer_image(Bulle, window, renderer, 1, 1, 0, 0, haut.x + 90, haut.y - 60, 0.2);
                            appliquer_image(nourriture[2], window, renderer, 1, 1, 0, 0, haut.x + 125, haut.y - 45, 0.3);
                            appliquer_image(perso[2], window, renderer, 3, 4, 0, 1, haut.x, haut.y, 4);
                        }
                        appliquer_image(Srab, window, renderer, 1, 1, 0, 0, x_depart - 50, y_depart - 50, 0.3);
                        appliquer_image(bouff, window, renderer, 1, 1, 0, 0, x_depart, y_depart, zoom_kichta);
                        appliquer_image(Feu, window, renderer, 8, 1, 0, indice_img_feu, xpoele + 67, ypoele - 35, 4);
                        // affichage du l'icone indiquant le personnage servi
                        appliquer_image(Servi, window, renderer, 1, 1, 0, 0, xservi, yservi, 0.1);
                        indice_img_feu++;
                        indice_img_feu %= 8;
                        SDL_RenderPresent(renderer);
                        SDL_Delay(50); // SDL_Delay(200);
                        // printf("temps prep : %d \n", tempspreparation);
                        tempspreparationaffichage -= 100;
                        it++;
                    }
                }
            }

            // On affiche notre monde avec les différents éléments
            appliquer_background(playa, window, renderer);
            affiche_nourriture(window, renderer, texture_nourriture);
            appliquer_image(Cheztonton, window, renderer, 1, 1, 0, 0, width / 2 - width_tonton / 2, height / 2 - height_tonton / 2, 1);
            appliquer_image(Kichta, window, renderer, 1, 1, 0, 0, 0.85 * width, 0.1 * height, 0.2);
            appliquer_image(Crabe, window, renderer, 1, 1, 0, 0, 100, 800, 0.3);
            appliquer_image(Heure, window, renderer, 3, 1, 0, periode, 140, 745, 2);
            appliquer_image(Poele, window, renderer, 1, 1, 0, 0, xpoele, ypoele, 0.5);
            text_surface = creation_surfaces(compteursvente, font, window, renderer, 5);
            affiche_compteur(window, renderer, text_surface);
            LibererCompteur(&text_surface);
            // affichage du profit
            SDL_DestroyTexture(profit_texture);
            profit_texture = appliquer_profit(renderer, font, profitrecompense, &profit_pos);
            SDL_RenderCopy(renderer, profit_texture, NULL, &profit_pos);
            SDL_RenderPresent(renderer);
            achat = estfini(compteurs);
        }
        else
        {
            char temp[120];
            int r = rand()%6;r++;
            
            sprintf(temp, "labyrinthe/monde%d.txt", r);
            char **M2 = init_matrice_labyrinthe(temp, &n, &m);
            sprintf(temp, "labyrinthe/Laby_monde%d.txt", r);
            double **Cosimienne = init_matrice_cosimienne(n * m, 4);
            chargerMatrice(Cosimienne, n * m, 4, temp);
            //On va vendre !!!
            faire_les_courses(window, renderer, road, wall, goal, persoAchat, M2, n, m, Cosimienne, &fini);
            achat = !achat;
            fini = !achat_MP(&profitrecompense, compteurs);
            stocktotal = compteurs[0] + compteurs[1] + compteurs[2];
            printf("profit: %d\n", stocktotal);
           
            LibererLaby(M2, n);
            LibererMatrice(Cosimienne, n*m);
        }
        SDL_Delay(50);
    }

    // SDL_Color rouge = {255, 0, 0, 255};
    // SDL_Surface *or_surface = TTF_RenderText_Blended(font,
    //                                                  "Fin",
    //                                                  rouge);
    // SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, or_surface);
    // SDL_Rect pos = {0, 0, 0, 0},
    //          dest = {(width/2)-100, 250, 1000, 500};
    // SDL_QueryTexture(texture, NULL, NULL, &pos.w, &pos.h);
    // dest.w = pos.w; dest.h = pos.h;
    // SDL_FreeSurface(or_surface);

    // // pos.w*=10;
    // SDL_RenderCopy(renderer, texture,
    //                &pos,
    //                &dest);

    // SDL_RenderPresent(renderer);

    SDL_Delay(2500);
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
    SDL_DestroyTexture(Crabe);
    SDL_DestroyTexture(Heure);
    LibererMatrice(Matentrainee, 192);
    LibererSet(&file);
    end_sdl(0, "Normal Ending", window, renderer);
    SDL_FreeSurface(icon);
    return 0;
}