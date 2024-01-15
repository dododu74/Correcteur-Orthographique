# Compilation de fichiers pour construire des programmes.
# Vous pouvez rajouter des commentaires en utilisant le symbole #

# Donner ci-dessous le nom des fichiers intermédiaires à générer
# Si vous indiquez un nom de module ici, cela sous-entend que votre programme
# fait appel à des fonctions déclarées dans un fichier .h et définies dans un
# fichier .c de même nom de base que celui du fichier objet généré en .o.
# Nom de base : nom du fichier sans extension.
OBJETS= dictionnaire.o alphabet.o

# Donner ci-dessous le(s) nom(s) du(des) fichier(s) exécutable(s) à produire
NOM_EXECUTABLES = orthographe

# Ligne ci-dessous à conserver
OPTIONS = -std=c99 -Wall -Wextra -Wvla -fsanitize=address,undefined -O0 -g
# enlever les dernières options sous Windows :
# OPTIONS = -std=c99 -Wall -Wextra -Wvla

# Règle principale
all: $(NOM_EXECUTABLES)


modules: $(OBJETS)


%.o : %.c %.h
	gcc -c $< $(OPTIONS)

orthographe: orthographe.c $(OBJETS)
	gcc -o $@ $(OPTIONS) $^

# $(NOM_EXECUTABLE): $(NOM_FICHIER) $(OBJETS)
#	gcc -o $(NOM_EXECUTABLE) $(OPTIONS) $(OBJETS) $(NOM_FICHIER)

clean:
	rm $(NOM_EXECUTABLES) $(OBJETS)

