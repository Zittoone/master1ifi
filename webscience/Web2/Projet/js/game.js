window.onload = init;

let canvas, ctx;
let ennemis = [];
let score = 0
let vies = 5

var mousepos = {x: 0, y: 0}

// main.js
function init() {
  console.log("page chargee");
  
  // 1 On recupere un pointeur sur le canvas
  canvas = document.querySelector("#myCanvas");
  
  // 2 On recupere le contexte graphique pour dessiner
  // dans le canvas
  ctx = canvas.getContext("2d");
  
  // 3 on dessine pour verifier que ca marche
  //ctx.fillStyle = 'red';
  //ctx.fillRect(10, 10, 100, 100);
  /*rect1 = new Rectangle(10, 10, 30, 30, 'red');
  rect1.vitesseX = 5;
  rect1.vitesseY=3;
  ennemis.push(rect1);
  
   rect2 = new GrowingRectangle(110, 110, 100, 100, 'green');
    rect2.vitesseY = 2;
  ennemis.push(rect2);

  cercle1 = new Cercle(60, 60, 15, 'blue')
  cercle1.vitesseX = 5
  cercle1.vitesseY = 2
  ennemis.push(cercle1)
  */
  joueur = new Rectangle(20, 250, 10, 10, 'blue');
  joueur.move = function(){
    let dx = joueur.x - mousepos.x;
    let dy = joueur.y - mousepos.y;
    let angle = Math.atan2(dy, dx);
    
    if (distance(joueur.x, joueur.y, mousepos.x, mousepos.y) >= 10) {
        //ball.v = 0;
        joueur.x -= joueur.vitesseMax * Math.cos(angle);
        joueur.y -= joueur.vitesseMax * Math.sin(angle);
    }
  }

  creerEnnemis(5)
  
  // Ecouteurs de clavier
  // window.onkeydown = traiteKeydown;
  // window.onkeyup = traiteKeyup;

  canvas.addEventListener('mousemove', function (evt) {
    mousepos = getMousePos(canvas, evt);
  }, false);

  // on demarre l'animation
  requestAnimationFrame(animation);
}



// Boucle d'animation
// typiquement dans game.js
function animation() {
  // 1 on efface
  ctx.clearRect(0, 0, canvas.width, canvas.height);
  
  // 2 on dessine et on deplace
  dessineEtDeplaceLesObjets();

  // On dessine le text
  ctx.fillText("Score : " + score, canvas.width - 50, 20)
  ctx.fillText("Vies : " + vies, canvas.width - 50, 40)
  
  // 3 on teste les collisions
  testeCollisions();
  
  // 4 on rappelle la boucle d'animation 60 fois / s
  requestAnimationFrame(animation);
}


function dessineEtDeplaceLesObjets() {
   ennemis.forEach((el) => {
     el.draw(ctx);
     el.move();
   })
   
   joueur.move();
   joueur.draw(ctx);
}


function creerEnnemis(nb){
  for(let i = 0; i < nb; i++){
    let x, y, h, l, couleur
    x = Math.random() * canvas.width
    y = Math.random() * canvas.height
    h = Math.random() * (60 - 20) + 20
    l = Math.random() * (60 - 20) + 20
    couleur = '#'+(Math.random()*0xFFFFFF<<0).toString(16);
    let rect = new Rectangle(x, y, h, l, couleur)
    rect.vitesseX = 2 || Math.random * rect.vitesseMax + 1
    rect.vitesseY = 2 || Math.random * rect.vitesseMax + 1

    ennemis.push(rect)
  }
}