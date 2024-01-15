#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "read_with_mmap.h"

/**
 * Ce module permet de copier en mémoire le contenu d'un fichier stocké sur le
 * disque dur. Les données peuvent ensuite être lues et traitées directement en
 * mémoire.
 *
 * À chaque appel de la fonction open_mmapfile devra correspondre un appel de la
 * fonction close_mmapfile, comme dans le fichier retrouver_message.c.
 */

/***********************************************************************/
/* Attention : le contenu de ce fichier est assez technique et surtout
 * complètement hors programme.
 * Vous ne devriez pas avoir besoin réellement besoin de le consulter :
 * les appels nécessaires ont été réalisés
 * dans le fichier conjugaison.c. */
/***********************************************************************/

/**
 * Renvoie l'adresse du premier octet à partir duquel le contenu du fichier
 * a été copié (mapped).
 * Entrées : chaîne de caractères représentant le nom du fichier.
 * Sortie : en sortie, le champ size a été mis à jour et contient le nombre
 * d'octets qui ont été mappés en mémoire.
 * La valeur de retour est l'adresse du premier octet.
 */
void *open_mmapfile(const char* filename, size_t* size)
{
  if ((filename ==0) || (size ==0)) return 0;

  int err;
  int fd;              /* file descriptor to filename */
  struct stat fd_stat; /* statistics about the file */
  void* baseaddr;      /* the returned value */

  /* here : Read and Write open flags. */
  fd = open(filename, O_RDWR);
  /* here open in O_RDONLY, access mode in mmap is related to read only */
  // fd = open(filename, O_RDONLY);
  if (fd == -1)
  {
    fprintf(stderr, "*** cannot open file '%s'\n", filename);
    return 0;
  }

  err = fstat(fd, &fd_stat);
  if (err !=0)
  {
    fprintf(stderr, "*** cannot read information about file '%s'\n", filename);
    return 0;
  }

  *size = fd_stat.st_size;
  if (*size ==0)
    return 0;


  fprintf(stdout, "*** file '%s' size is: %i\n", filename, (int)*size);
  // baseaddr = (void*)0x7f7096094000;
  baseaddr = (void*)mmap(
      // 0,                    /* let the OS to choose the base adress */
      0,
      // baseaddr,
      fd_stat.st_size,
      PROT_READ|PROT_WRITE, /* allow both read & write on the memory mapped op. */
      MAP_SHARED,  /* report write to file */
      //MAP_PRIVATE,        /* make copy private and do not reported memory update to file */
      fd,
      0                     /* 0 offset */
  );

  if (baseaddr == (void*)-1)
  {
    fprintf(stderr, "*** cannot map file '%s', error=%i, msg=%s\n",
        filename,
        errno,
        strerror(errno)
    );
    return 0;
  }
  close(fd);

  return baseaddr;
}


void close_mmapfile( void* addr, size_t size )
{
  munmap( addr, size );
}
