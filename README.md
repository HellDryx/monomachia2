

Pour utiliser le XOR:

Le fichier .exe, suivi de 1 ou 2 arguments, créé le RNA et 
l'exécute successivement sur un nombre de valeurs d'entrée 
données. Pour chaque exemple d'apprentissage, le programme affiche
 la valeur de sortie. Puis il affiche le résultat pour les 4 cas 
(0,0) (0,1) (1,0) et (1,1) afin de verifier l'efficacité de 
l'apprentissage du réseau.

Il faut fournir 1 ou 2 arguments:

-Le premier argument est le nombre d'exemples d'apprentissage.

-Le second argument (facultatif) permet de ne pas afficher 
 certains résultats trouvés par le réseau.
 Par exemple, il est possible de n'afficher que l'évolution des
 résultats pour la valeur d'entrée (0,0)
 Pour cela, il faut taper XOR_propre 40 0
 
Voici les combinaisons associées au deuxième argument:

0 = (0,0)	// XOR_propre 40 0
1 = (0,1)	// XOR_propre 40 1
2 = (1,0)	// XOR_propre 40 2
3 = (1,1)	// XOR_propre 40 3
4 = Toutes	// XOR_propre 40 4

