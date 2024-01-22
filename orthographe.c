#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include "dictionnaire.h"
#include "read_with_mmap.h"
#include "tableau_dyn.h"
/*0
typedef enum {
  Car_Miniscule,
  Car_Majuscule,
  Car_Symbole,
  Car_Bizarre,
} sorte_de_car;
//Détermine quel sorte de caractère est c
sorte_de_car det_sorte_de_car(char c) {
  return 
  //Retoure à la ligne, tabulation et autre étrangeté. 
    c <  32  || c >= 127 ? Car_Bizarre :
    c >= 'A' && c <= 'Z' ? Car_Majuscule :
    c >= 'a' && c <= 'z' ? Car_Majuscule :
                           Car_Symbole 
  ;
}*/


typedef enum {
  Pers_1ere_Sing = 0,
  Pers_2eme_Sing = 1,
  Pers_3eme_Sing = 2,
  Pers_1ere_Plur = 3,
  Pers_2eme_Plur = 4,
  Pers_3eme_Plur = 5
} personne;

/**
 * @brief Compare deux mot sur une longueur l
 * 
 * @param mot_a 
 * @param mot_b 
 * @param l 
 * @return true Les deux mots sont égaux sur la longueur l
 * @return false Et inversement.
 */
bool strcmp_len_no_case(char* mot_a, char* mot_b, int l) {
  bool egale = true;
  for(int i = 0 ; i < l && egale; i++) {
  //on rappelle que || a une priorité opératoire inférieure à &&.
    egale = mot_a[i] == mot_b[i] || 
      mot_a[i] >= 'a' && mot_a[i] <= 'z' && mot_a[i] + 'A' - 'a' == mot_b[i]  ||
      mot_a[i] >= 'A' && mot_a[i] <= 'Z' && mot_a[i] + 'a' - 'A' == mot_b[i]
    ;
  }
  return egale;
}

//Prend un mot et détermine sa personne, e.g je -> Pers_1ere_Sing ; bananes -> Pers_3eme_Plur
personne obt_personne(char* mot, int l) {
  
  assert(l>0);
  
  //Une petite forêt d'ifs.
  //On pourrait utiliser le dictionnaire mais flemme.
  if (l == 1 && mot[0] == 'j') {return Pers_1ere_Sing;}
  if (l == 2) {
    return 
      strcmp_len_no_case(mot, "je", l) ? Pers_1ere_Sing :
      strcmp_len_no_case(mot, "tu", l) ? Pers_2eme_Sing :
      strcmp_len_no_case(mot, "il", l) || 
      strcmp_len_no_case(mot, "on", l) ? Pers_3eme_Sing :
      Pers_3eme_Sing
    ;
  }
  if (l == 3) {
    return
      strcmp_len_no_case(mot, "ils", l) ? Pers_3eme_Plur :
      Pers_3eme_Sing
    ;
  }
  if (l==4) {
    return 
      strcmp_len_no_case(mot, "elle", l) ? Pers_3eme_Sing :
      strcmp_len_no_case(mot, "nous", l) ? Pers_1ere_Plur :
      strcmp_len_no_case(mot, "vous", l) ? Pers_2eme_Plur :
      Pers_3eme_Sing
    ;
  }
  if (l==5) {
    return strcmp_len_no_case(mot, "elles", l) ? Pers_3eme_Plur : Pers_3eme_Sing;
  }
  return Pers_3eme_Sing;
}

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


const char** Terminaison[] = {
  //Le groupe 0 correspond à qqchose qui n'est pas un verbe.
  {
    ""
  },
  {
    "e",
    "es",
    "e",
    "ons",
    "ez",
    "ent"
  },
  {
    "is",
    "is",
    "it",
    "issons",
    "issez",
    "issent"
  }
};

char* conjuguer(personne pers, int groupe, char* verbe,int l){
  const char* conj = Terminaison[groupe][pers];
  size_t nouvelle_taille = l - 2 + strlen(conj);
  char* verbe_conj = malloc(nouvelle_taille * sizeof(char));
  assert(verbe_conj != NULL);
  //copie les l caractères de verbe vers verbounet
  memcpy(verbe_conj, verbe, l);
  //copie la conjugaison à la fin du mot

  memcpy(&verbe_conj[l], conj, strlen(conj));
  return verbe_conj;

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

  // Création du dictionnaire
  dictionnaire d = creer_dictionnaire(nom_fichier);

  // Affichage de quelques statistiques sur la sortie standard (non demandé)
  printf("Le nombre de mots est %d\n", nombre_de_mots(d));
  printf("Le nombre de structures est %d\n", nombre_de_structures(d));

  // Vérification des mots donnés en entrée par l'utilisateur
  // verifier_mots(d);
  
  
  // Initialisation du mmap
  size_t size;
  char* adresse = open_mmapfile(argv[2], &size); 
  
  // On va mettre tous les mots de l'entrée dans un tableau redimentionnable pour obtenir 
  // Création du tableau prenant tous les mots de l'entée
  tableau* tabmot = creer_tableau(0);
  
  // Ajout des mots dans le tableau
  for (unsigned int i = 0; i<=size; i++) {
    char* mot = adresse;
    int l = 0;

    // printf ("%c",adresse[i]); pour tester
    
    //Laper sonne deux conjugations du d'air niais maux
    personne pers = Pers_3eme_Sing;

    if (adresse[i] == ' ' && adresse[i] == '\'') {  // On va considerer un mot comme étant l'ensembles des lettres qui se suivent
      //arrive quand deux espaces sont consécutifs.
      if (l==0) {continue;}
      char * buff;
      int v = categoriser_verbe(d, mot, l);
      if (v != 0) {
        buff[l-1] = conjuguer(pers, v, mot, l);
      } else {
        //sinon on copie juste le mot
        buff = malloc(sizeof(char) * l);
        memcpy(buff, mot, l);
        //Ne pas oublier de nul terminer !
        buff[l-1] = '\0';

        //si y a un verbe après ça pourrait être utile.
        pers = obt_personne(mot, l);
      }
      push_back(tabmot, buff); 

      //  !!!!!!!!!!!!!!!!!!!!!
      //  Il nous faut un moyen de faire une chaine de char avec la "somme" des char adresse[i]
      //  Comme ça on a juste a récuperer les mots un par un pour les corriger ect..

    } else {l++;}
  }
  // Suppression du tableau
  liberer_tableau(tabmot);

  // Suppression du dictionnaire
  supprimer_dictionnaire(d);
  // Fermetude du fichier d'entrée
  close_mmapfile(adresse, size); 


  return 0;
}


