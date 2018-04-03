function testeCollisions() {
    testeCollisionsAvecMurs(joueur);
    testCollisionsEnnemisMurs();
    testCollisionJoueursEnnemis();
  }

  function testCollisionsEnnemisMurs() {
    ennemis.forEach((el) => {
      testeCollisionsAvecMurs(el);
    })
    
   joueur.draw(ctx);
   
 }
 function testeCollisionsAvecMurs(r) {
   // MURS DROITE ET GAUCHE
   
   if((r.x + r.l) > canvas.width) {
     // detection avec mur de droite
     // on met la vitesse horizontale a zero
     r.vitesseX = -r.vitesseX;
     // on le remet au point de contact
     r.x = canvas.width - r.l;
   } else if((r.x) < 0) {
     // detection avec mur de gauche
     // on met la vitesse horizontale a zero
     r.vitesseX = -r.vitesseX;
     // on le remet au point de contact
     r.x = 0;
   }
   
   // MURS BAS ET HAUT
   if((r.y + r.h) > canvas.height) {
     // detection avec mur de droite
     // on met la vitesse horizontale a zero
     r.vitesseY = -r.vitesseY;
     // on le remet au point de contact
     r.y = canvas.height - r.h;
   } else if((r.y) < 0) {
     // detection avec mur de gauche
     // on met la vitesse horizontale a zero
     r.vitesseY = -r.vitesseY;
     // on le remet au point de contact
     r.y = 0;
   }
 }
 
 function testCollisionJoueursEnnemis() {
   ennemis.forEach((el) => {
         if(rectsOverlap(joueur.x, joueur.y, joueur.l, joueur.h,
                  el.x, el.y, el.l, el.h)) {
     //console.log("collision");
     el.couleur = 'pink';
   } else {
     el.couleur = el.primCouleur;
   }      
  })
   
 }
 
 // Collisions between aligned rectangles
 // dans collision.js
 function rectsOverlap(x1, y1, w1, h1, x2, y2, w2, h2) {
  
   if ((x1 > (x2 + w2)) || ((x1 + w1) < x2)) {
      return false; // No horizontal axis projection overlap
   }
   if ((y1 > (y2 + h2)) || ((y1 + h1) < y2)) {
      return false; // No vertical axis projection overlap
   }
   return true; // If previous tests failed, then both axis projections
                // overlap and the rectangles intersect
 }