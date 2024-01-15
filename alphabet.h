/**
 * Projet Correcteur Orthographique. 2024.
 * Phase 1. Détection d'erreurs.
 *
 * @author  : M. Durand
 * @date    : version
 * @version : 1.0
 */


#ifndef ALPHABET_H
#define ALPHABET_H

/**
 * L'ensemble du projet sera gêré uniquement avec les lettres suivantes.
 * a-z
 * - '
 * àâèéêëîïôùûüç
 * œ
 *
 * L'objectif est de limiter l'espace en mémoire utilisé en ne représentant pas
 * toute la table ASCII et encore moins la table complète UTF-8 travaillant sur
 * 2 octets !
 *
 * Rappel ou information : dans le codage UTF-8 les 128 premiers caractères de
 * la table ASCII conservent leur code et s'écrivent sur un seul octet. Cette
 * partie contient les lettres majuscules et minuscules, le tiret et
 * l'apostrophe (entre autres). C'est ce qui nous a permis d'utiliser le code
 * des caractères comme indice dans le tableau suivantes.
 * Les caractères accentués sont encodés sur deux octets (plus d'octets sont
 * nécessaires dans d'autres systèmes). Le codage est pensé de manière à ce
 * qu'en lisant un premier octet, on puisse savoir combien d'octets sont
 * nécessaires.
 *
 * Dans notre situation, il n'y en aura que 2. Voir alphabet.c pour la gestion
 * en pratique.
 *
 * Pour que la console ou l'éditeur de fichier utilisé reconnaisse ensuite qu'il
 * s'agit d'un caractère accentué il faut écrire les deux octets bien sûr.
 **/


/*
 * 26 lettres minuscules + le tiret + l'apostrophe + lettres accentuées + oe
 * entrelacé => 42 (même pas fait exprès !).
 */

#define NB_LETTRES 42

/**
 * Renvoie l'indice à laquelle la lettre correspond.
 *
 * Les indices de 0 à 25 correspondent aux lettres de a à z. Le charactère - a pour
 * indice 26, le caractère ' a pour indice 27, les indices suivants sont
 * utilisés pour les lettres accentuées dans l'ordre indiqué ci-dessus.
 *
 * Renvoie -1 si le caractère n'est pas géré.
 **/
int indice_lettre(unsigned char *s);

#endif // ALPHABET_H
