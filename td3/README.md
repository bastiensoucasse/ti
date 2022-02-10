Iantsa Provost & Bastien Soucasse – TI

# TD 3

Pour compiler :

```
make
```

Pour nettoyer :

```
make clean
```

Pour nettoyer et supprimer les rendus :

```
make reset
```

Pour tester :

```
make test
```

N.B.

La deuxième ligne du Makefile est définie comme tel :

```
CFLAGS := -std=c99 -g -I$(HOMEBREW_PATH)/include -Iinclude -O3 -Wall
````

La partie `-I$(HOMEBREW_PATH)/include` correspond à la localisation des _headers_ installé sur Mac via Homebrew. Il sera probablement nécessaire de la changer pour utiliser le Makefile sur d'autres systèmes.
