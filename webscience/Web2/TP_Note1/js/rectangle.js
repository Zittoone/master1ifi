// Une classe pour le rectangle
// typiquement dans rectangle.js
class Rectangle {
    constructor(x, y, l, h, couleur) {
      this.x = x || 0;
      this.y = y || 0;
      this.l = l || 20;
      this.h = h || 20;
      this.couleur = couleur || 'black';
      this.primCouleur = this.couleur
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
      ctx.fillRect(this.x, this.y, this.l, this.h);
      
      ctx.restore();
    }
    
    move() {
      this.x += this.vitesseX;
      this.y += this.vitesseY;
    }
  }
  
  class GrowingRectangle extends Rectangle {
    constructor(x, y, l, h, couleur) {
      super(x, y, l, h, couleur)
      this.maxl = l
      this.minl = 20
      this.maxh = h
      this.minh = 20
      this.growingl = false
      this.growingh = false
    }

    move() {
      super.move()
      // Hauteur
      if(this.growingh == true){
        this.h += 1
        if(this.h >= this.maxh){
          this.h = this.maxh
          this.growingh = false
        }
      } else {
        this.h -= 1
        if(this.h <= this.minh){
          this.h = this.minh
          this.growingh = true
        }
      }

      // Largeur
      if(this.growingl == true){
        this.l += 1
        if(this.l >= this.maxl){
          this.l = this.maxl
          this.growingl = false
        }
      } else {
        this.l -= 1
        if(this.l <= this.minl){
          this.l = this.minl
          this.growingl = true
        }
      }
    }
  }