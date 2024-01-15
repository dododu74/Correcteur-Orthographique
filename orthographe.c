#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include "dictionnaire.h"
#include "read_with_mmap.h"
#include "tableau_dyn.h"


/**
 * Cette fonction lit le contenu du fichier dont le nom est transmis en
 * paramètre et renvoie un dictionnaire qui contient tous les mots lus dans le
 * fichier.
 */
dictionnaire creer_dictionnaire(char* filename)
{
  dictionnaire d = dictionnaire_vide();


  errno = 0;
  FILE* fd = fopen(filename, "r");
  if (fd == NULL)
  {
    printf("Une erreur s'est produite : %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  int nb;
  fscanf(fd, "%d\n", &nb);
  printf("On attend %d mots \n", nb);

  fscanf(fd, "-\n");

  char buffer[256];
  while(fscanf(fd, "%s", buffer) != EOF) {
    ajouter_mot(d, buffer);
  }

  // fermeture du flot de lecture du fichier
  fclose(fd);

  printf("On a ajouté %d mots \n", nombre_de_mots(d));
  assert(nb == nombre_de_mots(d));

  return d;
}


/**
 * Cette fonction ouvre le fichier 'a_corriger.txt' en écriture puis lit des
 * mots sur l'entrée standard.
 * Si le mot n'existe pas dans le dictionnaire il est écrit dans le fichier
 * a_corriger.txt sur une nouvelle ligne.
 *
 */
void verifier_mots(dictionnaire d)
{
  // Préparation du flot d'écriture dans le fichier (remarquez le mode 'w'
  // utilisé).
  errno = 0;
  FILE *fres = fopen("a_corriger.txt", "w");
  if (fres == NULL)
  {
    printf("Une erreur s'est produite : %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  // Utilisation d'une chaîne de caractères pour lire ce qui est entré par
  // l'utilisateur.
  char buffer[256];

  // Affichage d'une consigne - non nécessaire
  printf("Donner un mot, terminer par STOP\n");

  scanf("%s", buffer); // lecture d'une première chaîne

  // Boucle tant que le mot entré n'est pas STOP.
  while (strncmp(buffer, "STOP", 5) != 0) {
    bool existe = chercher_mot(d, buffer);
    if (!existe) {
      fprintf(fres, "%s\n", buffer);
    }
    scanf("%s", buffer);
  }

  // fermeture du flot d'écriture du fichier (enregistrement en mémoire)

  fclose(fres);
}

void printout(FILE* fichout, tableau* tabmots, int n){
  // écrit les mots du tableau tabmots de taille n dans le fichier fich
  for (int i=0;i<n;i++){
    fprintf(fichout,"%s ",tabmots->data[i]);
  }
  fprintf(fichout,"\n");
}

void conjuguer(tableau* tabmots,int n){
  // conjugue les verbes du tableau de mots tabmots de taille n en les modifiant
  // /!\ il va falloir modifier la structure du dico pour implémenter les natures des mots; ou au moins pour les verbes
  //les verbes du 1er grp ont un /a après eux dans le dico, et ceux du 2e ont un /f
  for (int i=0;i<n;i++){
    if est_un_verbe(tabmots->data[i]) /*à définir*/{
      
    } 
  }
}

////////////////////////////////////// Pour executer : /////////////
// ./orthographe Ressources/fr-reforme1990_court_sans.dic texte5.txt


int main(int argc, char *argv[])
{
  char nom_fichier[256];

  if (argc > 1) {
    strncpy(nom_fichier, argv[1], 256);
  } else {
    strcpy(nom_fichier, "Ressources/fr-reforme1990_court_sans.dic");
  }

  // Initialisation du mmap
  size_t size;
  char* adresse = open_mmapfile(argv[2], &size); 
  
  // On va mettre tous les mots de l'entrée dans un tableau redimentionnable pour obtenir 
  // Création du tableau prenant tous les mots de l'entée
  tableau* tabmot = creer_tableau(0);
  // Ajout des mots dans le tableau
  char* mot;
  for (unsigned int i = 0; i<=size; i++) {

    // printf ("%c",adresse[i]); pour tester
    if (adresse[i] != ' ') {  // On va considerer un mot comme étant l'ensembles des lettres qui se suivent
      
      //  !!!!!!!!!!!!!!!!!!!!!
      //  Il nous faut un moyen de faire une chaine de char avec la "somme" des char adresse[i]
      //  Comme ça on a juste a récuperer les mots un par un pour les corriger ect..

    }
    else {
      // On ajoute ensuite le mot au tableau des mots
      push_back(tabmot, mot);
      mot = "";
    }
  }

  // Création du dictionnaire
  dictionnaire d = creer_dictionnaire(nom_fichier);

  // Affichage de quelques statistiques sur la sortie standard (non demandé)
  printf("Le nombre de mots est %d\n", nombre_de_mots(d));
  printf("Le nombre de structures est %d\n", nombre_de_structures(d));

  // Vérification des mots donnés en entrée par l'utilisateur
  // verifier_mots(d);
  
  // Suppression du tableau
  liberer_tableau(tabmot);

  // Suppression du dictionnaire
  supprimer_dictionnaire(d);
  // Fermetude du fichier d'entrée
  close_mmapfile(adresse, size); 

  return 0;
}


