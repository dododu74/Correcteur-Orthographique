/**
 * Projet Correcteur Orthographique. 2024.
 * Phase 1. Détection d'erreurs.
 *
 * @author  : M. Durand
 * @date    : version
 * @version : 1.0
 */


#ifndef DICTIONNAIRE_H
#define DICTIONNAIRE_H 1

#include <stdbool.h>
#include "alphabet.h"

/* Remarque : les deux lignes précédentes et la ligne à la toute fin du fichier sont
 * des directives à destination du pré-processeur, une étape réalisée avant la
 * compilation.
 * Ces lignes permettent d'éviter d'inclure plusieurs fois les déclarations de
 * fonctions ou de types contenues dans le fichier.
 *
 * #ifndef DICTIONNAIRE_H signifie si DICTIONNAIRE_H n'est pas définie, alors
 * passer dans le bloc suivant (et l'enlever, ce ne sera pas visible dans le
 * code C que le compilateur traitera).
 * La ligne #define DICTIONNAIRE_H 1 définie DICTIONNAIRE_H et indique qu'il
 * faudra substituer toute apparition de DICTIONNAIRE_H par un 1. La valeur
 * n'importe pas ici.
 */




// const int nb_lettres = 42; // pas de VLA au programme !
/*
 * NB_LETTRES est 'définie' dans le fichier alphabet.h, il s'agit d'une chaîne
 * de caractères qui sera remplacée par 42.
 * Il n'est pas recommandé d'utiliser des define en général, le problème c'est
 * que j'avais envie d'avoir un tableau de lettres suivantes déclaré de manière
 * statique, comme dans la structure ci-dessous. Or le programme interdit
 * explicitement la déclaration de tableau du type int tableau[nb]; avec nb une
 * variable, y compris s'il s'agit d'une constante connue avant la compilation.
 */

/* Définition d'une structure pour représenter une lettre sur le chemin d'un
 * mot. Accéder à cette lettre permet de poursuivre le chemin vers une lettre
 * suivante grâce au tableau suivantes.
 */
struct lettre_s {
  struct lettre_s* suivantes[NB_LETTRES];
  bool terminal;
  int nb_mots; // non nécessaire
};

typedef struct lettre_s lettre;

typedef lettre* dictionnaire; // un dictionnaire est représenté par un pointeur vers une structure de type lettre
// il est possible de manipuler des lettre* partout à la place.

/**
 * Renvoie un dictionnaire vide initialisé à 0.
 */
dictionnaire dictionnaire_vide();

/**
 * Ajoute un mot à un dictionnaire précédemment créé par un appel à
 * dictionnaire_vide().
 *
 * @param d      un dictionnaire
 * @param mot    un mot
 */
void ajouter_mot(dictionnaire d,  char* mot);

/**
 * Cherche un mot dans un dictionnaire précédemment créé et enrichi.
 *
 * @param d      un dictionnaire
 * @param mot    un mot
 * @return true  si le mot a été trouvé dans le dictionnaire, false sinon
 */
bool chercher_mot(dictionnaire d,  char* mot);


/**
 * Libère l'espace mémoire alloué au dictionnaire complet.
 *
 * @param d      un dictionnaire
 */
void supprimer_dictionnaire(dictionnaire d);


/* Fonctions ci-dessous non demandées */
int nombre_de_mots(dictionnaire d);

int nombre_de_structures(dictionnaire d);

#endif // DICTIONNAIRE_H
