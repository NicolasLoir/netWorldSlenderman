---
author: Guillaume Lozengez ; Alexis Lebis
version: 1.0
---
# Audit - TEAM-PROJECT-XXX

@auditor: Guillaume L.

## Process 

1. Connect to the git webpage of the project and get a first view of the project.
2. Follow the install instruction 
3. Execute the software.
4. Enter in the source code and the documentation.

## Presentation:

**Does the index page (the README file) provides a clear overview of the project and an overmealing desire to try it ?**

Ok

**Is The installation instruction clear and complete ?**

Oui

**Is the compilation of the software easy ?**

Oui, mais beaucoup de Warnings.

**Is the project correctly organized ?**

Oui, on appréciera les plusieurs exécutables pour tester les différents modules

On regrettera qu'il n'y ai pas un exécutable pour les mètres tous en musique.

**Further comments ?**


## Quality of the solution:

**Does the provided software run well ?**

TestNetWorld ok

TestIA: Rien, longtemps, puis ferme.

Nico: ok, succession de deux petits jeux vectorielle

Quentin: On peut zoomer dézoomer avec la molette.


**Does the software have a clear and ergonomic interface ?**

nico: oui, du moins le texte aide.

**Is there any tutorial of some sort to highlight specific software functionalities ?**

nico: directement dans le jeux.


**Further comments ?**


## The project in depth:

### Project managment

**Does projet-outline.md clearly state what has been done, and by who ?**

Difficile de séparer ce qui est fait de ce qui reste à faire.

**Does projet-outline.md defines the next steps to achieve ?**

...

**Did the group distribute the tasks between them correctly ?**

Sur le papier oui et particulièrement le détail dans l'UI. 


### Source code

**Is the entrance point of the application easy to find ?**

À quoi sert Window.c ? Il n'ai connecté à aucun autre élément du programme...

main.c: 250 lignes sur un main c'est beaucoup trop...


**Is source code of quality (names, comments, small atomic functions...) ?**

Pas de problème sur le nommage, mais la division en fonction atomique permettrais de s'y retrouver  plus facilement.


**Is source code architecture coherent (decomposition in structure and their interaction, well desgined OOP, programming patterns...) ?**

Globalement oui, il manque essentiellement une structure pour représenter le jeu globalement, voire chacun des mini-jeux (ainsi qu'un report de ces éléments sur des fichiers sources spécifiques).
D'autre part, certaines des fonctions ne sont pas au bon endroit. Typiquement, duplicateNetWorldForIA.

- En quoi duplicateNetWorldForIA est spécifique à l'IA ?
- Pourquoi ne pas faire un duplicateNetWorld dans NetWorld, puis s'appuyer sur une telle méthode dans duplicateNetWorldForIA, pour effectuer ensuite ce qui est spécifique ici ?


**Is the solution's algorithmic efficient (minimizing the computation time while K.I.S.S) ?**

Dans attente d'une intégration de l'IA, il n'y a RàS.


**Does the solution has a good memory management (no memory leaks, heavy element is manipulated with pointers, the memory is allocated and free appropriately) ?**

Il semble que les malloc et free soit correctement utilisé cependant, de nouveau un manque de méthode unitaire n'aide pas visualiser s'ils sont faits un bon moment.

Exemple dans IA: 

```c
node ** allLinked = edgeGetAllLinked(nodeToRemove, res.edges, res.edgeSize);

...


free(allLinked);

```

Il faut savoir qu'un malloc est caché dans `edgeGetAllLinked` et qu'un free doit être effectué ensuite.

Seul un profiler permettrait de valider une bonne gestion de la mémoire avec des outils tels que gdb ou mentest...


**Is there a documentation and what is its quality ?**

Les commentaires dans le code sont effectivement riches.


**Further comments ?**



## Recomentations:


- S'organiser avec plusieurs branches pour permettre à chaque développeur d'avoir son environnement de travail sans polluer inutilement le Master (à minima une branche dev commune)
- Procéder à une réflexion sur qu'elle morceau de code se rattache à quel élément du programme, et déporter ces morceaux dans des fonctions spécifiques, déporter sur dans le fichier source de l'élément (par exemple, le dessin de la carte dans main).


## Conclusion


**Is the development of the project far advanced ?**


Difficile à établir. Pas vraiment si le main.c intègre déjà tous se qui à était réalisé, mais cela ne semble pas être le cas.


**Would-it be easy for a new developer to participate in the project ?**

non


**Is it interresting to further develop this project ?**

Oui, le contrôle, l'affichage fonctionne, mais je n'ai pas identifié l'intérêt du jeu en construction (et pas non plus dans les descriptions).


**Final comments...**

