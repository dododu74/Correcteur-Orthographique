#include <stdio.h>

struct cellule_s {
    char data;
    struct cellule_s* suiv;
};
typedef struct cellule_s cellule ;
typedef cellule* dico ;




int main(int argc, char* argv[]){
    assert (argc == 2);
    // Les entrées attendus sont : ./prog FILENAME
    int errno = 0;
    FILE* fd = fopen (argv [1] , "r" ); // On ouvre le fichier mis en commentaire en mode 'read'
    if ( fd == NULL ) {
        printf ("Erreur lors de l'ouverture du fichier %s : %d (%s) \n" ,
        argv [1],errno ,strerror(errno));
        return 1;
    }
    
    int nb = 0;
    fscanf ( fd , " % d " , & nb ) ;
    fclose ( fd );

    return 0;
}