#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

struct cellule_s {
    char data;
    bool isterminal;
    struct cellule_s* suiv[26];
};
typedef struct cellule_s cellule ;
typedef cellule* dico ;

bool chercher_mot(dico dic,string mot){
    int l=strlen(mot);
    for (int i=0;i<l;i++){
        if (dico[mot[i]-'a'].suiv==NULL) 
    }
}


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
    fscanf ( fd , "%d" , &nb ) ;
    fclose ( fd );

    return 0;
}