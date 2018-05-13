function testeCollisions(joueur, obstacles, lasers, stars) {
    if(joueur.state != entityStates.alive)
        return;

    testeCollisionsAvecMurs(joueur);
    testCollisionJoueursObstacles(joueur, obstacles);
    testCollisionJoueursLasers(joueur, lasers);
    testCollisionStars(stars);
}

function testCollisionJoueursObstacles(joueur, obstacles) {
    obstacles.forEach((o) => {
        if(o.x > 0 && o.x < w)            
        if (((joueur.x + joueur.l) > o.x) && ((joueur.x) < o.x + o.l) && ((joueur.y + joueur.h) > o.y) && ((joueur.y) < (o.y + o.h))){
            o.explode();
            joueur.explode();
        } 
    });
}

function testCollisionJoueursLasers(joueur, lasers) {
    lasers.forEach((o) => {
        // testeCollisionsAvecMurs(o);
    });
}

function testCollisionStars(stars) {
    stars.forEach((s) => {
        if (s.x + s.r <= 0) {
            s.x = w;
        }
    });
}

function testeCollisionsAvecMurs(r) {
    // MURS DROITE ET GAUCHE

    if ((r.x + r.l) > canvas.width) {
        r.x = canvas.width - r.l;
        r.resetSpeed();
    } else if ((r.x) < 0) {
        r.x = 0;
        r.resetSpeed();
    }

    // MURS BAS ET HAUT
    if ((r.y + r.h) > canvas.height) {
        r.y = canvas.height - r.h;
        r.resetSpeed();
    } else if ((r.y) < 0) {
        r.y = 0;
        r.resetSpeed();
    }
}

function testCollisionJoueursEnnemis() {
    ennemis.forEach((el) => {
        if (rectsOverlap(joueur.x, joueur.y, joueur.l, joueur.h,
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