# TP Noté n°1

## Première aproche

__Attention, ce sera la base du TP a rendre qui sera note (a rendre pour seance 4)__

Prendre (le dernier exercice vu en cours)[http://jsbin.com/qetinun/edit?js,console,output] et vous l'approprier:

1. Ajouter un autre rectangle dont la taille varie pendant qu'il bouge: il grossit, il rapetisse.
2. Ajouter un cercle plein. Faire une classe Cercle en vous inspirant du modele du rectangle. Voir le MOOC HTML5 Coding essentials and best practices, Week 3, pour voir comment dessiner des cercles.
3. Ecrivez une fonction creerEnnemis(nb) qui permet de creer un tableau d'ennemis avec des tailles et des vitesses aleatoires. Quand on demarre le jeu, on appelle cette methode pour peupler le tableau des ennemis.
4. Ok, on a vu comment deplacer le joueur au clavier, on aimerait le deplacer a la souris. Dans un premier temps, vous le dessinerez la ou se trouve le curseur. Vous pouvez momentanement desactiver le deplacement au clavier.
5. Regardez comment dessiner un texte dans le MOOC. Vous afficherez en haut de l'ecran un score et un nombre de vies. Par defaut score = 0 et nombre de vies = 5
6. Faites des cercles et des rectangles rouges (mechants) et des verts (bons a manger). On meurt quand on est touche par un objet rouge, on marque des points quand on mange des objets verts. Vous mettrez a jour le score et le nombre de vies en consequence.
7. Ok, maintenant quand on mange un objet vert, il disparait. Quand tous les objets verts sont manges, on change de niveau et on augmente le nombre et la vitesse des objets rouges. Attention a ne pas recreer les ennemis sur le joueur sinon il y aura collision avant meme que le niveau ne commence.
8. Ah, il est temps de decouper le programme en fichiers. Telechargez ou copiez/collez le code de jsbin (menu fichier/download), et faites en un "vrai" code maintenable avec les fichiers js, css et html separes. Si possible de maniere "logique". A partir de maintenant vous pourrez travailler avec Visual Studio Code, Sublime Text, Atom, WebStorm etc... pour travailler sur votre projet.
    * (ICI l'exemple initial du cours decoupe en fichiers)[http://miageprojet2.unice.fr/@api/deki/files/2789/=Master_IFI.zip] 
9. Amelioration de gameplay : le joueur "suit" la souris comme dans l'exemple suivant tire du MOOC HTML5 Apps and Games: https://jsbin.com/soduko/edit?js,output, ca change le gameplay, il faudra peut-etre ralentir les ennemis.


