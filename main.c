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

dico dictionnaire_vide(void) {
    dico dict = (dico)malloc(sizeof(cellule)*26);
    printf("%c" ,dict[0].data);
    return dict;
}


bool chercher_mot(dico dic,char* mot){
    if (dic=NULL) return false;
    if (mot=="") return dic->isterminal ;
    dico next=dic[mot[0]-'a'].suiv;
    if (next==NULL) return false;
    return chercher_mot(next,&mot[1]);
}



int main(int argc, char* argv[]){
    assert(argc == 2);
    dico dict = dictionnaire_vide();
    // Les entrées attendus sont : ./prog FILENAME
    int errno = 0;
    FILE* fd = fopen (argv[1] , "r" ); // On ouvre le fichier mis en commentaire en mode 'read'
    if ( fd == NULL ) {
        printf ("Erreur lors de l'ouverture du fichier %s : %d (%s) \n" ,
        argv [1],errno ,strerror(errno));
        return 1;
    }
    
    int nb = 0;
    fscanf (fd , "%d" , &nb ) ;
    fclose (fd );

    return 0;
}