class Cercle {
    constructor(x, y, r, couleur) {
      this.x = x || 0;
      this.y = y || 0;
      this.r = r || 20;
      this.l = r * 2
      this.h = r * 2
      this.couleur = couleur || 'black';
      this.vitesseX = 0; // en pixels par image d'animation
      this.vitesseY = 0; // en pixels par image d'animation
      this.vitesseMax = 3;
  
    }
    
    draw(ctx) {
      // Bonne pratique : si on modifie le contexte
      // couleur, epaisseur du trait, repere geometrique etc
      // on sauvegarde au debut de la fonction, on restaure a
      // la fin
      ctx.save();
      
      ctx.fillStyle = this.couleur;
      ctx.beginPath();
      ctx.arc(this.x + this.r, this.y + this.r, this.r, 0, 2 * Math.PI);
      ctx.closePath();
      ctx.fill();
      
      ctx.restore();
    }
    
    move() {
      this.x += this.vitesseX;
      this.y += this.vitesseY;
    }
  }