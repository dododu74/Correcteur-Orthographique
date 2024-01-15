/**
 * Projet Correcteur Orthographique. 2024.
 * Phase 1. Détection d'erreurs.
 *
 * @author  : M. Durand
 * @date    : version
 * @version : 1.0
 */

#include "alphabet.h"

// La ligne suivante sert à compiler sans gérer les accents et les caractères -
// ou /.

// #define SANS_ACCENT 1


/* Le plus simple est d'associer à chaque caractère lu en UTF-8 un numéro.
 *
 * En pratique, les accents courants sont codés sur 2 octets, avec le premier
 * octet qui vaut 0xc3. Seul le oe entrelacé est codé par deux octets dont le
 * premier vaut 0xc5.
 **/
enum lettres_accents {
  a_grave = 0,
  a_circ = 1,
  e_grave = 2,
  e_aigu = 3,
  e_circ = 4,
  e_trema = 5,
  i_circ = 6,
  i_trema = 7,
  o_circ = 8,
  u_grave = 9,
  u_circ = 10,
  u_trema = 11,
  c_cedil = 12,
  oe = 13
};


/**
 * Renvoie l'indice à laquelle la lettre correspond.
 * Renvoie -1 si le caractère n'est pas géré.
 *
 * Il faut utiliser des unsigned char ici car il faut avoir accès aux valeurs de
 * 0 à 255, pour pouvoir détecter que le premier octet est l'une des valeurs
 * spéciales.
 */
int indice_lettre(unsigned char *s)
{
  int res = -1;
  if (s[0] == 0xc3 || s[0] == 0xc5)
  {
    // il s'agit d'une lettre accentuée
    // s[0] == 0xc3 pour toutes les premières
    // s[0] == 0xc5 pour le oe entrelacé
    res = 28;
    switch (s[1]) {
      case 0xa0 :
	res += a_grave;
	break;
      case 0xa2 :
	res += a_circ;
	break;
      case 0xa8 :
	res += e_grave;
	break;
      case 0xa9 :
	res += e_aigu;
	break;
      case 0xaa :
	res += e_circ;
	break;
      case 0xab :
	res += e_trema;
	break;
      case 0xae :
	res += i_circ;
	break;
      case 0xaf :
	res += i_trema;
	break;
      case 0xb4 :
	res += o_circ;
	break;
      case 0xb9 :
	res += u_grave;
	break;
      case 0xbb :
	res += u_circ;
	break;
      case 0xbc :
	res += u_trema;
	break;
      case 0xa7 :
	res += c_cedil;
	break;
      case 0x93 :
	res += oe;
	break;
      default :
	  res = -1;
    }
#ifdef SANS_ACCENT
    res = -1;
#endif
  } else if (s[0] >= 0x61 && s[0] <= 0x7a) {
    res = s[0] - 0x61; // écrire res = s[0] - 'a'; fonctionne tout aussi bien
  } else if (s[0] == '-') {
    res = 26;
#ifdef SANS_ACCENT
    res = -1;
#endif
  } else if (s[0] == '\'') {
    res = 27;
#ifdef SANS_ACCENT
    res = -1;
#endif
  }

  return res;
}
