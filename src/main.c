#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int VIE_MAX = 10;

void title() {
    //system("clear");
    printf("\033[2J\033[1;1H");
    printf("###############################################################################\n");
    printf("# _____               ____                 _      _ _____ _              ____ #\n");
    printf("# |   \\ |     |    | /                     |\\    /|   |   |\\   | |    | /     #\n");
    printf("# |___| |     |    | \\___       _  ___     | \\  / |   |   | \\  | |    | \\___  #\n");
    printf("# |     |     |    |     \\     / \\ |       |  \\/  |   |   |  \\ | |    |     \\ #\n");
    printf("# |     |____ |____| ____/     \\_/ |       |      | __|__ |   \\| |____| ____/ #\n");
    printf("#                                                                             #\n");
    printf("###############################################################################\n\n");
}

int main( int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    srand(time(NULL));

    int nombreMystere = -1;
    int nb_vie = VIE_MAX;
    int find = 0;
    int tmp = -1;
    int play = 0;
    int MAX = -1;
    int MIN = -1;
    int choixNiveau = 0;

    title();
    printf("Bienvenu dans le jeux du Plus ou moins !\n");
    printf("Le but ? Trouver le nombre mystère compris entre un Minimum et Maximum en moin de %d coup !\n", VIE_MAX);
    printf("Simple non ? Vous voulez jouer ? (1/0) ");
    scanf("%d", &play);

    while(play) {
        while(!choixNiveau) {
            printf("\n");
            printf("Mode de jeu disponible :\n");
            printf("1. niveau Debutant\t( 1 : 20 )\n");
            printf("2. niveau Amateur\t( 1 : 50 )\n");
            printf("3. niveau Confirme\t( 1 : 100 )\n");
            printf("4. niveau Expert\t( 1 : 1000 )\n");
            printf("Quel niveau choissez-vous ? ");
            scanf("%d", &choixNiveau);
            printf("\n");
            switch(choixNiveau) {
                case 1:
                MIN = 1;
                MAX = 20;
                printf("L'ordinateur ce prepare pour passer en mode Debutant ...\n");
                break;
                case 2:
                MIN = 1;
                MAX = 50;
                printf("L'ordinateur ce prepare pour passer en mode Amateur ...\n");
                break;
                case 3:
                MIN = 1;
                MAX = 100;
                printf("L'ordinateur ce prepare pour passer en mode Confirme ...\n");
                break;
                case 4:
                MIN = 1;
                MAX = 1000;
                printf("L'ordinateur ce prepare pour passer en mode Expert ...\n");
                break;
                default:
                choixNiveau = 0;
                break;
            }
        }

        choixNiveau = 0;
        nb_vie = 10;
        find = 0;
        nombreMystere = (rand() % (MAX - MIN + 1)) + MIN;
        printf("Le nombre Mystere a été elu, a vous de jouer !\n\n");
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
                printf("Bravo, vous avez trouve le nombre mystere !!!\nEt en seulement %d coup !\n", VIE_MAX-nb_vie);
                find++;
            }
        }
        if(!nb_vie) {
            printf("Vous n'avez malheureusement pas trouver le nombre mystere qui etait %d ...\n", nombreMystere);
        }
        printf("\nEncor une partie ? (1/0) ");
        scanf("%d", &play);
    }
    
    printf("\nA une prochaine fois peut-etre !\n");

    return EXIT_SUCCESS;
}
