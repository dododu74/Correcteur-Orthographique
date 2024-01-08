#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char* argv[]){

    assert ( argc == 2) ;
    errno = 0;
    FILE * fd = fopen ( argv [1] , " r " ) ;
    if ( fd == NULL ) {
    printf ( " Erreur lors de l ' ouverture du fichier % s : % d (% s ) \ n " ,
    argv [1] , errno , strerror ( errno ) ) ;
    return 1;
    }

    int nb = 0;
    fscanf ( fd , " % d " , & nb ) ;
    fclose ( fd );

    return 0;
}
