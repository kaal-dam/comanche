# Ces variables servent à préciser le compilateur que l’on veut utiliser # ainsi
# que les paramètres de compilation
CC=gcc
LD=gcc
CFLAGS=-Wall -W -Werror
LDFLAGS=

# Le nom de l’exécutable à fabriquer
EXE=pawnee


# Les variables HEADERS, CFILES et OBJS vont contenir respectivement
# la listes des fichiers .h, .c et le nom des fichiers .o à fabriquer
# On utilise la directive particulière $(wildcard ...) qui permet
# de construire automatiquement une liste de fichiers
HEADERS=$(wildcard *.h)
CFILES=$(wildcard *.c)

# Cette construction de variable veut dire: remplacer la chaine ".c" par 
# ".o" dans la variable CFILES
# Ceci nous permet de construire la liste des fichiers .o à fabriquer
OBJS=$(CFILES:.c=.o)

# La règle par défaut déclenche la fabrication de l’exécutable par dépendance
all: $(EXE)


# Cette règle permet de construire l’exécutable. Elle dépend des fichiers # .o
# et effectue l’édition de lien. Rien de nouveau ici
$(EXE): $(OBJS)
	$(LD) $^ $(LDFLAGS) -o $@

# Cette règle permet de construire automatiquement les règles de compilation
# pour chacun des fichiers .c
# l’option -MM de gcc analyse un fichier .c et
# affiche sur sa sortie standard une règle compatible
# make pour le compiler.
# Ceci permet d’ajouter automatiquement les fichiers .h aux dépendances des
# fichiers .o à construire. Ainsi, en modifiant un fichier .h
# tous les fichiers .c qui incluent ce fichier sont recompilés
# Après votre première compilation, regardez le contenu du fichier
# makefile.dep généré afin de comprendre exactement de quoi il retourne.
makefile.dep: $(CFILES) $(HEADERS)
	$(CC) -MM $(CFILES) > $@

# Cette règle efface le fichier de dépendances et les fichiers .o
clean:
	$(RM) $(OBJS) makefile.dep

# Cette règle effectue la précédente et efface en plus l’exécutable
mrproper: clean
	$(RM) $(EXE)

# On inclue le fichier de dépendance qui va contenir les règles de
# construction des fichiers .o
# S’il n’existe pas, make invoque automatiquement la règle
# qui l’a pour cible
include makefile.dep
