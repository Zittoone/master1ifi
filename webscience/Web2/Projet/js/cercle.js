class Cercle {
    constructor(x, y, r) {
        this.x = x || 0;
        this.y = y || 0;
        this.r = r || 20;
        this.l = r * 2;
        this.h = r * 2;
        this.couleur = 'black';
        this.vitesseX = 0;
        this.vitesseY = 0;

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

class ParallaxStar {
    constructor(x, y, layer) {
        this.x = x;
        this.y = y;
        this.layer = layer;
        this.r = 3 + layer;
        this.color1 = "rgb(52, 84, 135," + (layer / 10) + ")";
        this.color2 = "rgb(40, 69, 111," + (layer / 10) + ")";
    }

    draw(ctx) {

        let angle = -45 * 180 / Math.PI;
        ctx.save();

        ctx.fillStyle = this.color1;

        ctx.beginPath();
        ctx.arc(this.x, this.y, this.r, 0 + angle, Math.PI + angle);
        ctx.closePath();
        ctx.fill();

        ctx.fillStyle = this.color2;
        ctx.beginPath();
        ctx.arc(this.x, this.y, this.r, Math.PI + angle, 2 * Math.PI + angle);
        ctx.closePath();
        ctx.fill();

        ctx.restore();
    }

    move(modifier) {
        let m = modifier || 1;
        this.x -= (this.layer / 2) * m;
    }
}