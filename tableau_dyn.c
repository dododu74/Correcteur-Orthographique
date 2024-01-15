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

#include "tableau_dyn.h"
#include <stdlib.h>
#include <assert.h>

/* Crée un nouveau tableau redimensionnable et renvoie un pointeur sur la
 * structure associée.
 */
tableau* creer_tableau(int n)
{
  tableau* t = (tableau*)malloc(sizeof(tableau));
  if (t == NULL) { exit(EXIT_FAILURE); }

  t->capacite = 10;
  if (n != 0)
  {
    t->capacite = n;
  }
  t->nb = 0;
  t->data = (unsigned char*)malloc(sizeof(unsigned char)*(t->capacite));
  if (t->data == NULL) { exit(EXIT_FAILURE); }

  return t;
}

/* Ajoute un nouvel élément dans le tableau.
 * Entrée : t  un pointeur vers un tableau redimensionnable
 *          v  valeur du nouvel élément
 * Sortie : pas de valeur de retour, le tableau contient un nouvel élément.
 */
void push_back(tableau* t, unsigned char v)
{
  if (t->nb == t->capacite)
  {
#ifdef CONFORME_PROGRAMME
    int* tmp = (int*)malloc(sizeof(int)*(t->capacite)*2);
    if (tmp == NULL)
    {
      liberer_tableau(t);
      exit(EXIT_FAILURE);
    }
    for(int i = 0; i < t->nb; i++)
    {
      tmp[i] = t->data[i];
    }
    free(t->data);
    t->data = tmp;
#else
    t->data = (unsigned char*)realloc(t->data, sizeof(unsigned char)*(t->capacite)*2);
    if (t->data == NULL)
    {
      liberer_tableau(t);
      exit(EXIT_FAILURE);
    }
#endif
    t->capacite = t->capacite * 2;
  }
  t->data[t->nb] = v;
  t->nb++;
}

/* Renvoie la valeur d'un élément à l'indice donné.
 * Entrée : t  un pointeur vers un tableau redimensionnable
 *          i  la valeur d'un indice valide
 * Sortie : la valeur de l'élément du tableau à l'indice donné
 */
unsigned char get(tableau* t, int i)
{
  assert(i >=0 && i < t->nb);
  return t->data[i];
}

/* Modifie la valeur de l'élément à l'indice donné.
 * Entrée : t  un pointeur vers un tableau redimensionnable
 *          i  l'indice d'un élément dans le tableau
 *          v  la nouvelle valeur de l'élément
 *  Sortie : pas de valeur de retour, la valeur de l'élément a été modifiée dans
 *  le tableau.
 */
void set(tableau* t, int i, unsigned char v)
{
  assert(i >= 0 && i < t->nb);
  t->data[i] = v;
}


/* Renvoie le nombre d'éléments du tableau.
 * Entrée : t  un pointeur vers un tableau redimensionnable
 * Sortie : le nombre d'éléments du tableau.
 */
int taille(tableau* t)
{
  return t->nb;
}

/* Libère l'espace associé à un tableau redimensionnable.
 * Entree : t  un pointeur vers un tableau redimensionnable
 * Sortie : pas de valeur de retour, la mémoire allouée dans le tas par la
  structure est libérée, le pointeur t ne doit plus être utilisé.
 */
void liberer_tableau(tableau* t)
{
  free(t->data);
  free(t);
}

