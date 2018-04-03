function traiteKeydown(evt) {
    let code = evt.code;
    switch(code) {
      case 'ArrowRight':
        // on va vers la droite
        joueur.vitesseX = joueur.vitesseMax;
        break;
      case 'ArrowLeft':
        // on va vers la gauche
        joueur.vitesseX = -joueur.vitesseMax;
        break;
      case 'ArrowUp':
        // on va vers la droite
        joueur.vitesseY = -joueur.vitesseMax;
        break;
      case 'ArrowDown':
        // on va vers la gauche
        joueur.vitesseY = joueur.vitesseMax;
        break;
    }
  }
  
  function traiteKeyup(evt) {
    let code = evt.code;
    
    switch(code) {
      case 'ArrowRight':
      case 'ArrowLeft':
        // on s'arrete horizontalement
        joueur.vitesseX = 0;
        break;
      case 'ArrowUp':
      case 'ArrowDown':
        // on s'arrete horizontalement
        joueur.vitesseY = 0;
        break;
    }
  }