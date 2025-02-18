Synchronisation entre 3 threads 

On suppose un procédé  qui demande de synchroniser les 6 fonctions suivantes funcU(), funcV(), funcW(), funcX(), funcY(), funcZ() 
devant toujours être exécutées dans ce même ordre (U, V, W, X, Y, Z et ainsi de suite) et 3 thread T1(), T2() et T3(). 
Le thread T1() appelle les fonctions funcU() et funcX(), le thread T2() les fonctions funcV() et funcY() et le thread T3() 
les fonction funcW() et funcZ(). Écrivez le code des thread T1(), T2() et T3() en veillant à ce que l’ordre d’appel des 
fonction (U, V, W, X, Y, Z) soit respecté.

Notez que les exercices 4 et 5 sont similaires à celui-ci en ce sens que ce sont des problèmes pour synchroniser des threads 
entre eux et non faire de l'exclusion mutuelle.
