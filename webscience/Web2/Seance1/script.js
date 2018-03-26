window.onload = init;

let canvas, ctx;
let audioCtx = new AudioContext();

function init() {
  console.log("page chargee DOM ready");
  // a l'ancienne
  // canvas = document.getElementById("myCanvas");
  
  // avec selector API, meme syntaxe que css
  canvas = document.querySelector("#myCanvas");
  
  // Pour dessiner, il faut un contexte graphique
  ctx = canvas.getContext("2d");
  
  // On peut maintenant dessiner  
  //drawRectanglePlein(100, 200, 100, 100, "green");
  //drawRectanglePlein(50, 50, 100, 100, "rgba(255, 0, 0, 0.5)");

  //ctx.strokeStyle = "blue";
  //ctx.lineWidth = 5;
  //ctx.strokeRect(200, 200, 70, 60);
  
  osc1 = audioCtx.createOscillator();
  osc1.connect(audioCtx.destination); // Haut parleur
  //osc1.start();
  
  lfo = audioCtx.createOscillator();
  lfo.frequency.value = 20;
  
  let g = audioCtx.createGain();
  g.gain.value = 300;
  
  lfo.connect(g);
  
  g.connect(osc1.frequency);
  lfo.start();
  
  // On lance l'animation a 60 images/s
  requestAnimationFrame(animation);
  //setInterval(animation, 10)
}

function drawRectanglePlein(x, y, l, h, couleur) {
  // bonne pratique : toujours sauvegarder le contexte dans 
  // une fonction ou methode qui change ses proprietes
  ctx.save();
  
  ctx.fillStyle = couleur;
  ctx.fillRect(x, y, l, h);
  
  ctx.restore();
}

function drawRectangleObjet(r) {
    ctx.save();
  
    ctx.fillStyle = r.couleur;
    ctx.fillRect(r.x, r.y, r.l, r.h);
  
    ctx.restore();
}

let x = 0;
let rect2 = new Rectangle(10, 10, 100, 100, "blue");

function animation(time) {
  // 1 On efface le canvas
  ctx.clearRect(0, 0, canvas.width, canvas.height);
  
  // 2 On dessine les objets
  //drawRectanglePlein(Math.random()*20, 100, 100, 100, "green");
  //drawRectanglePlein(50, 50, 100, 100, "rgba(255, 0, 0, 0.5)");
  //drawRectangleObjet(rect3)
  rect3.draw(ctx);
  
  // 3 On deplace les objets
  rect3.move();
  testeCollisionsAvecMurs(rect3);
  
  // On anime le son, la frequence va dependre
  // de la position en x
  osc1.frequency.value = rect3.x*10;
  
  // 4 On rappelle la boucle d'animation par defaut 60 fois par seconde
  requestAnimationFrame(animation);
}

function testeCollisionsAvecMurs(r) {
  if(r.x + r.l > canvas.width){
    r.x = canvas.width - r.l;
    r.vitesseX = -r.vitesseX;
  } else {
    if(r.x <0 ){
      r.x = 0;
      r.vitesseX = -r.vitesseX;
    }
  }
  
  if(r.y + r.h > canvas.height){
    r.y = canvas.height - r.h;
    r.vitesseY = -r.vitesseY;
  } else {
    if(r.y <0 ){
      r.y = 0;
      r.vitesseY = -r.vitesseY;
    }
  }
}

// L'objet en JS
// 1ere maniere : objet "litteraux" ou "singleton"
var rect1 = {
  x:10,
  y:10,
  l:150,
  h:150,
  couleur: "red",
  decrisToi: function() {
    return "rectangle : x = " + this.x;
  }
}

// 2eme maniere: les fonctions constructeurs de ES5/JavaScript 5
function Rectangle(x, y, l, h, couleur) {
  this.x = x || 0;
  this.y = y || 0;
  this.l = l || 10;
  this.h = h || 10;
  this.couleur = couleur || "black";
  
  this.decrisToi = function() {
    return "rectangle : x = " + this.x;
  }
}

// 3eme syntaxe : classe ES6 / JavaScript 6
// REGLE/ASTUCE : plus jamais le mot "function" !!!!

class RectangleES6 {
  constructor(x, y, l, h, couleur) {
    this.x = x || 0;
    this.y = y || 0;
    this.l = l || 10;
    this.h = h || 10;
    this.couleur = couleur || "black";
    this.vitesseX = 2;
    this.vitesseY = 5;
  }
  
  decrisToi() {
    return "rectangle : x = " + this.x;
  }
  
  draw(ctx) {
    ctx.save();
  
    ctx.fillStyle = this.couleur;
    ctx.fillRect(this.x, this.y, this.l, this.h);
  
    ctx.restore();
 }
  
  move() {
    this.x += this.vitesseX;
    this.y += this.vitesseY;
    
    // this.x += this.vitesse * Math.cos(this.angle)
    // this.y += this.vitesse * Math.sin(this.angle)

  }
}

var rect3 = new RectangleES6(100, 100, 100, 100, "red");


