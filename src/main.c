#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int MAX = 100, MIN = 1;

int main( int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    srand(time(NULL));
    int nombreMystere = (rand() % (MAX - MIN + 1)) + MIN;

    int nb_vie = 5;
    int find = 0;
    int tmp = -1;

    printf("\n### Plus ou Moins ###\n\n");
    printf("Bienvenu dans le jeux du Plus ou moins !\n");
    printf("Le but ? Trouver le nombre mystère compris en %d et %d en moin de %d coup !\n", MIN, MAX, nb_vie);
    printf("Simple non ? A vous de jouer !\n\n");

    while(!find && nb_vie){
        nb_vie--;
        printf("Quel est le nombre ? ");
        scanf("%d", &tmp);
        if( tmp > nombreMystere ) {
            printf("C'est moins !\n");
            printf("%d vie(s) restante(s) !\n", nb_vie);
        }
        else if ( tmp < nombreMystere ) {
            printf("C'est plus !\n");
            printf("%d vie(s) restante(s) !\n", nb_vie);
        }
        else {
            printf("Bravo, vous avez trouve le nombre mystere !!!\nEt en seulement %d coup !", 5-nb_vie);
            find++;
        }
    }
    if(!nb_vie) {
        printf("Vous n'avez malheureusement pas trouver le nombre mystere qui etait %d ...\n", nombreMystere);
    }

    return EXIT_SUCCESS;
}