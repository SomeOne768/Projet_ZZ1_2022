#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "markov.h"
#include "animation.h"
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include "ecriture.h"



//je commence

/*******************************************************************************/
/* Fonctionnement du programme                                                 */
/* But : Pêcher des poissons                                                   */
/* touche:                                                                     */
/* -p mettre la musique en pause                                               */
/* -fleches gauche/droite pour se deplacer                                     */
/* -f ESC ou croix pour quitter le programme                                   */
/* -espace pour pêcher                                                         */
/* -v vendre ses poissons                                                      */
/* -r acheter du temps de musique                                              */ 
/*******************************************************************************/

const int Mat1[9][9]=
        {   {25, 34, 40, 0, 0, 0, 0, 0, 1},     //Matrice transition dans le monde 1
            {29, 40, 30, 0, 0, 0, 0, 0, 1},     // de 0 à 7 : les poissons 
            {40, 29, 30, 0, 0, 0, 0, 0, 1},     //9e ligne pour cas initial (pas de poisson), 9e colonne pour peche spéciale(fin)
            {49, 30, 20, 0, 0, 0, 0, 0, 1},
            {30, 49, 20, 0, 0, 0, 0, 0, 1},
            {29, 30, 40, 0, 0, 0, 0, 0, 1},
            {0, 39, 60, 0, 0, 0, 0, 0, 1},
            {25, 25, 10, 40, 0, 0, 0, 0, 0},
            {35, 35, 29, 0, 0, 0, 0, 0, 1}};

const int Mat2[9][9]=
        { 
            {29, 20, 0, 0, 25, 25, 0, 0, 1},
            {29, 10, 0, 0, 30, 30, 0, 0, 1},
            {25, 25, 0, 0, 10, 40, 0, 0, 1},
            {49, 10, 0, 0, 15, 25, 0, 0, 1},
            {10, 49, 0, 0, 25, 15,  0, 0, 1},
            {29, 30, 0, 0, 20, 20, 0, 0, 1},
            {0, 39, 0, 0, 20, 40, 0, 0, 1},
            {54, 0, 0, 0, 40, 5, 0, 0, 1},
            {35, 35, 0, 0, 20, 9, 0, 0, 1}  };


const int Mat3[9][9]=
        {  
            {30, 35, 0, 0, 0, 0, 4, 30, 1},
            {35, 30, 0, 0, 0, 0, 4, 30, 1},
            {40, 30, 0, 0, 0, 0, 4, 25, 1},
            {50, 20, 0, 0, 0, 0, 4, 25, 1},
            {15, 10, 0, 0, 0, 0, 60, 14, 1},
            {30, 30, 0, 0, 0, 0, 4, 35, 1},
            {20, 49, 0, 0, 0, 0, 0, 30, 1},
            {50, 25, 0, 0,  0, 0, 4, 20, 1},
            {35, 35, 0, 0, 0, 0, 9, 20, 1} 

        };
        


int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_DisplayMode screen;
    
    
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
        SDL_Quit();


    SDL_GetCurrentDisplayMode(0, &screen);
    
    int width = screen.w;
    int height = screen.h;

    /* Création de la fenêtre */
    window = SDL_CreateWindow("Jeu de la pêche", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    if (window == NULL) 
        end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

    /* Création du renderer */
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) 
        end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

    /* Chargement musique */
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    // changement de l'icône de la fenêtre du jeu
    SDL_Surface* icon;
 
    // on charge l'image dans la surface
    icon = SDL_LoadBMP("./img/Fish-rod.bmp");
    
    // on dit qu'on veut l'image précédente comme icône
    SDL_SetWindowIcon(window, icon);

    if (TTF_Init() < 0) 
        end_sdl(0, "Couldn't initialize SDL TTF", window, renderer);

    TTF_Font* font = NULL;                                               // la variable 'police de caractère'
    font = TTF_OpenFont("retro-land.ttf", 60);                     // La police à charger, la taille désirée
    if (font == NULL)   
        end_sdl(0, "Can't load font", window, renderer);

    TTF_Font* font2 = TTF_OpenFont("retro-land.ttf", 90);

    //Mix_Music *music = Mix_LoadMUS("sonne.mp3");
    Mix_Music *Jul_remix = Mix_LoadMUS("./music/MyRec_0623_0803.mp3");
    Mix_Music *Cosima_Reves_music = Mix_LoadMUS("./music/MyRec_0623_0824.mp3");



    //coucouc la zonee ouasi uaois jul
    SDL_Texture* texture = load_texture_from_image("./img/Fisherman/Fisherman_hook.png", window, renderer);
    SDL_Texture* texture_ferrer = load_texture_from_image("./img/Fisherman/Fisherman_hook.png", window, renderer);
    SDL_Texture* texture_bateau = load_texture_from_image("./img/objects/Boat.png", window, renderer);
    SDL_Texture* monde_mid = load_texture_from_image("./img/desert_essai.png", window, renderer);
    SDL_Texture* monde_left = load_texture_from_image("./img/espace_essai.png", window, renderer);
    SDL_Texture* monde_right = load_texture_from_image("./img/montagne_essai.png", window, renderer);
    

    SDL_Texture* poisson0 = load_texture_from_image("./img/objects/0.png", window, renderer);
    SDL_Texture* poisson1 = load_texture_from_image("./img/objects/1.png", window, renderer);
    SDL_Texture* poisson2 = load_texture_from_image("./img/objects/2.png", window, renderer);
    SDL_Texture* poisson3 = load_texture_from_image("./img/objects/3.png", window, renderer);
    SDL_Texture* poisson4 = load_texture_from_image("./img/objects/4.png", window, renderer);
    SDL_Texture* poisson5 = load_texture_from_image("./img/objects/5.png", window, renderer);
    SDL_Texture* poisson6 = load_texture_from_image("./img/objects/6.png", window, renderer);
    SDL_Texture* poisson7 = load_texture_from_image("./img/objects/7.png", window, renderer);
    SDL_Texture* poulet = load_texture_from_image("./img/objects/Chicken.png", window, renderer);
    SDL_Texture* piece = load_texture_from_image("./img/Coin_Gems/MonedaD.png", window, renderer);



    SDL_Texture * texture_pechedujour[9] = {poisson0, poisson1, poisson2, poisson3, poisson4, poisson5, poisson6, poisson7, poulet};
    
    SDL_Texture* tab_monde[3] ={monde_left, monde_mid, monde_right};
    int indice_monde_cur = 1,
        nb_mondes = 3,
        poisson_actuel=8;

    
    //play_with_texture_5(monde_mid, texture, window,renderer);
    


    

    //Nos coordonnées seront relatives au pêcheur
    int x_pecheur = width/2,
        y_pecheur = height-250,//250 car ne pas oublier la hauteur de l'image
        indice_img = 2,//Permet de faire les "sprite" 2 = mode peche
        indice_img_piece = 0;

    int pecher = 0; 
    int a_deja_peche = 0;
    int poissonspeches[]= {0, 0, 0, 0, 0, 0, 0, 0};
    int findepartie=0;
    int or_compteur = 0;
    SDL_Rect or_pos;
    or_pos.x = width-150;
    or_pos.y =50;
    SDL_Texture* or_texture = appliquer_score(renderer, font, or_compteur, &or_pos);


    //1er affichage: BG + pecheur + bateau
    SDL_Surface** text_surface = creation_surfaces(poissonspeches, poisson_actuel, font, window, renderer);
    // ecran_debut(renderer, font2);
    appliquer_background(tab_monde[indice_monde_cur], window, renderer);
    appliquer_image(texture_ferrer, window, renderer, 6, x_pecheur, y_pecheur, 3.5, indice_img);
    appliquer_image(texture_bateau, window, renderer, 1, x_pecheur-100, y_pecheur+100, 4.5, 0);
    affiche_score(window, renderer, text_surface);
    appliquer_image(piece, window, renderer, 5, width-50, 50, 3, indice_img_piece);
    SDL_RenderCopy(renderer, or_texture, NULL, &or_pos);
    SDL_RenderPresent(renderer);
    Mix_PlayMusic(Jul_remix, 0);
    Mix_PauseMusic(); 
    int duree_Jul_remix = 0;//ms
    int music_on = 0;

    SDL_bool program_on = SDL_TRUE;               
    SDL_Event event;
    while (program_on  && !(findepartie))
    {              
        
        if(x_pecheur>=width)// && indice_monde_cur<(nb_mondes-1))
        {
            //Si besoin d'aller dans le monde de droite
            indice_monde_cur++;
            indice_monde_cur%=nb_mondes;
            x_pecheur = 0;
        }
        else if(x_pecheur<-50)// && indice_monde_cur>0)
        {
            indice_monde_cur--;
            if(indice_monde_cur<0)indice_monde_cur=nb_mondes-1;
            x_pecheur = width-20;
        }


        while (program_on && SDL_PollEvent(&event))
        {          
                  
            switch(event.type)
            {                       
                case SDL_QUIT:                          
                    program_on = SDL_FALSE;                 
                    break;

                case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_RIGHT:
                        x_pecheur += 17;
                        break;

                    case SDLK_LEFT:
                        x_pecheur -= 17;
                        
                        break;

                    case 'f':
                        program_on = SDL_FALSE;                 
                        break;
                    
                    case 'v':
                        or_compteur+= prix_revente(poissonspeches);
                        SDL_DestroyTexture(or_texture);
                        or_texture = appliquer_score(renderer, font, or_compteur, &or_pos);
                        break;
                    
                    case 'r':
                        if(duree_Jul_remix<0){duree_Jul_remix=0;}
                        duree_Jul_remix += or_compteur *1000;
                        or_compteur = 0;
                        SDL_DestroyTexture(or_texture);
                        or_texture = appliquer_score(renderer, font, or_compteur, &or_pos);
                        if(duree_Jul_remix>10000){Mix_ResumeMusic(); music_on=1;}

                        break;
                    
                    case SDLK_SPACE:
                        pecher=1;   
                        int attente= (rand()%3+0.5)*1000;
                        SDL_Delay (attente);
                        a_deja_peche=1;
                        switch(indice_monde_cur)
                        {
                            case 0:
                                poisson_actuel=prochainEtatMarkov(Mat1,poisson_actuel);
                                break;
                            case 1:
                                poisson_actuel=prochainEtatMarkov(Mat2,poisson_actuel);
                                break;
                            case 2:
                                poisson_actuel=prochainEtatMarkov(Mat3,poisson_actuel);
                                break;
                            default:
                                break;

                        }
                        poissonspeches[poisson_actuel]+=1;
                        

                        break;
                    
                    case SDLK_ESCAPE:
                        program_on = 0;
                        break;
                    
                    case 'p':
                        //On met la musique en pause
                        if(music_on)
                        {
                            music_on = !music_on;
                            Mix_PauseMusic(); 
                        }
                        else
                        {
                            music_on = !music_on;
                            Mix_ResumeMusic(); 
                        }
                        break;
                    default:
                        break;
                }

                default:
                break;
            }
        }

        if(pecher)
        {
            if (poisson_actuel==8) 
            {
                findepartie = 1;
            }
            
            indice_img++;
            SDL_Delay(100);
            
        }
        if(indice_img==6){pecher=0; indice_img=0;}

        appliquer_background(tab_monde[indice_monde_cur], window, renderer);
        text_surface = creation_surfaces(poissonspeches, poisson_actuel, font, window, renderer);
        affiche_score(window, renderer, text_surface);
        appliquer_image(texture_ferrer, window, renderer, 6, x_pecheur, y_pecheur, 3.5, indice_img);
        appliquer_image(texture_bateau, window, renderer, 1, x_pecheur-100, y_pecheur+100, 4.5, 0);
        appliquer_image(piece, window, renderer, 5, width-50, 50, 3, indice_img_piece);
        affiche_poisson_score(window, renderer, texture_pechedujour);
        SDL_RenderCopy(renderer, or_texture, NULL, &or_pos);


        if (a_deja_peche)
        {
            if ((poisson_actuel==4 || poisson_actuel==5))
            {
                appliquer_image(texture_pechedujour[poisson_actuel], window, renderer, 2, x_pecheur-110, y_pecheur+70, 2.5, 0);
            }
            else
            {
                if (poisson_actuel==8)
                {
                    appliquer_image(texture_pechedujour[poisson_actuel], window, renderer, 1, x_pecheur-110, y_pecheur+70, 4, 0);
                }
                else 
                {
                    if (poisson_actuel==0) appliquer_image(texture_pechedujour[poisson_actuel], window, renderer, 2, x_pecheur-110, y_pecheur+80, 4.8, 0);
                    else appliquer_image(texture_pechedujour[poisson_actuel], window, renderer, 2, x_pecheur-110, y_pecheur+70, 4.5, 0);
                }
            } 
        }
        int i=0;
        if (!findepartie)
        {
            //On compte le nombre de poisson différents
            while (i<8 && poissonspeches[i])
            {
                i++;
            }
            //Si on les a tous, la partie est terminée
            findepartie = (i==8);
        }
        
        if (findepartie)
        {
            
            Mix_PlayMusic(Cosima_Reves_music, 1);
            SDL_Color color_fin = {231, 14, 14, 255};                                  // la couleur du texte
            SDL_Surface* text_surface_fin = NULL;                                    // la surface  (uniquement transitoire)
            text_surface_fin = TTF_RenderText_Blended(font, "You win :)", color_fin); // création du texte dans la surface 
            if (text_surface_fin == NULL) 
                end_sdl(0, "Can't create text surface", window, renderer);

            SDL_Texture* text_texture_fin = NULL;                                    // la texture qui contient le texte
            text_texture_fin = SDL_CreateTextureFromSurface(renderer, text_surface_fin); // transfert de la surface à la texture
            if (text_texture_fin == NULL) 
                end_sdl(0, "Can't create texture from surface", window, renderer);
            SDL_FreeSurface(text_surface_fin);                                       // la texture ne sert plus à rien

            SDL_Rect pos = {850, 500, 0, 0};                                         // rectangle où le texte va être prositionné
            SDL_QueryTexture(text_texture_fin, NULL, NULL, &pos.w, &pos.h);          // récupération de la taille (w, h) du texte 
            SDL_RenderCopy(renderer, text_texture_fin, NULL, &pos);                  // Ecriture du texte dans le renderer   
            SDL_DestroyTexture(text_texture_fin);                                    // On n'a plus besoin de la texture avec le texte

            SDL_RenderPresent(renderer);                                         // Affichage 
            SDL_Delay(8000);
        }

        if(music_on==1 && duree_Jul_remix<0){music_on=0; Mix_PauseMusic(); }
        SDL_RenderPresent(renderer);
        SDL_Delay(50);
        duree_Jul_remix-=50;
        indice_img_piece++;
        indice_img_piece%=5;
    }
    

    TTF_CloseFont(font);
    TTF_Quit(); 
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(texture_ferrer);
    SDL_DestroyTexture(monde_mid);  
    SDL_DestroyTexture(monde_left);
    SDL_DestroyTexture(monde_right);
    SDL_DestroyTexture(texture_bateau);    
    SDL_DestroyTexture(poisson0);
    SDL_DestroyTexture(poisson1);
    SDL_DestroyTexture(poisson2);
    SDL_DestroyTexture(poisson3);
    SDL_DestroyTexture(poisson4);
    SDL_DestroyTexture(poisson5);
    SDL_DestroyTexture(poisson6);
    SDL_DestroyTexture(poisson7);
    SDL_DestroyTexture(poulet);
    SDL_DestroyTexture(piece); 
    IMG_Quit();                              // Si on charge une librairie SDL, il faut penser à la décharger   
    end_sdl(1, "Normal ending", window, renderer);
    return EXIT_SUCCESS;
}