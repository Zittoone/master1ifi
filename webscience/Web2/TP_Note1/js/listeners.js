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

  function distance(x1, y1, x2, y2) {
    return Math.sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

function getMousePos(canvas, evt) {
  // get canvas position
  var obj = canvas;
  var top = 0;
  var left = 0;
  while (obj && obj.tagName != 'BODY') {
      top += obj.offsetTop;
      left += obj.offsetLeft;
      obj = obj.offsetParent;
  }

  // return relative mouse position
  var mouseX = evt.clientX - left + window.pageXOffset;
  var mouseY = evt.clientY - top + window.pageYOffset;
  return {
      x: mouseX,
      y: mouseY
  };
}