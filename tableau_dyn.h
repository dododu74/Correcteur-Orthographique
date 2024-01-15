/**
 * Projet Correcteur Orthographique. 2024.
 * Phase 2. Conjugaison.
 *
 * Module de tableau redimensionnable.
 *
 * @author  : M. Durand
 * @date    : version
 * @version : 1.0
 */

#ifndef TABLEAU_H
#define TABLEAU_H

typedef struct tableau_s {
  int capacite;
  int nb;
  unsigned char* data;
} tableau;

/* Crée un nouveau tableau redimensionnable et renvoie un pointeur sur la
 * structure associée.
 *
 * Entrée : n  un nombre d'éléments indicatif utilisé pour la préparation du tableau. Si
 * n vaut 0, la valeur par défaut est utilisée.
 */
tableau* creer_tableau(int t);

/* Ajoute un nouvel élément dans le tableau.
 * Entrée : t  un pointeur vers un tableau redimensionnable
 *          v  valeur du nouvel élément
 * Sortie : pas de valeur de retour, le tableau contient un nouvel élément.
 */
void push_back(tableau* t, unsigned char v);

/* Renvoie la valeur d'un élément à l'indice donné.
 * Entrée : t  un pointeur vers un tableau redimensionnable
 *          i  la valeur d'un indice valide
 * Sortie : la valeur de l'élément du tableau à l'indice donné
 */
unsigned char get(tableau* t, int i);

/* Modifie la valeur de l'élément à l'indice donné.
 * Entrée : t  un pointeur vers un tableau redimensionnable
 *          i  l'indice d'un élément dans le tableau
 *          v  la nouvelle valeur de l'élément
 *  Sortie : pas de valeur de retour, la valeur de l'élément a été modifiée dans
 *  le tableau.
 */
void set(tableau* t, int i, unsigned char v);

/* Renvoie le nombre d'éléments du tableau.
 * Entrée : t  un pointeur vers un tableau redimensionnable
 * Sortie : le nombre d'éléments du tableau.
 */
int taille(tableau* t);

/* Libère l'espace associé à un tableau redimensionnable.
 * Entree : t  un pointeur vers un tableau redimensionnable
 * Sortie : pas de valeur de retour, la mémoire allouée dans le tas par la
  structure est libérée, le pointeur t ne doit plus être utilisé.
 */
void liberer_tableau(tableau* t);

#endif
