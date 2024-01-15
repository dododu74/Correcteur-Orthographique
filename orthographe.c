#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include "dictionnaire.h"

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



int main(int argc, char *argv[])
{
  char nom_fichier[256];

  if (argc > 1) {
    strncpy(nom_fichier, argv[1], 256);
  } else {
    strcpy(nom_fichier, "fr-reforme1990_court_sans.dic");
  }

  // Création du dictionnaire
  dictionnaire d = creer_dictionnaire(nom_fichier);

  // Affichage de quelques statistiques sur la sortie standard (non demandé)
  printf("Le nombre de mots est %d\n", nombre_de_mots(d));
  printf("Le nombre de structures est %d\n", nombre_de_structures(d));

  // Vérification des mots donnés en entrée par l'utilisateur
  verifier_mots(d);

  // Suppression du dictionnaire
  supprimer_dictionnaire(d);

  return 0;
}


