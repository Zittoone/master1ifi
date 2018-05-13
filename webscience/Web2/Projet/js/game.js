// useful
Array.prototype.pushArray = function(arr) {
  this.push.apply(this, arr);
};

var canvas, ctx, w, h, game;
window.onload = () => {
  canvas = document.querySelector("#myCanvas");
  ctx = canvas.getContext("2d");

  w = canvas.width;
  h = canvas.height;

  game = GF();
  game.start();
};

var gameStates = {
  mainMenu: 0,
  gameRunning: 1,
  gameLevelWon: 2,
  gameOver: 3
};

var entityStates = {
  alive: 0,
  exploding: 1,
  dead: 2
};

var GF = () => {
  var gameState = gameStates.gameRunning;
  var inputStates = {};

  /** Level related variables */
  var currentLevel = 1;
  var lasers = [];
  var obstacles = [];
  var stars = [];
  var joueur = [];
  var time_start, time_level;
  var vitesse;

  /** Only function visbile by the API */
  var start = function(timestamp) {
    time_start = Date.now();

    createJoueur(w / 2 - 80 / 2, h / 2 - 48 / 2, joueur, 1);

    window.addEventListener(
      "keydown",
      function(event) {
        event.inputStates = inputStates;
        onKeydown(event);
      },
      false
    );
    window.addEventListener(
      "keyup",
      function(event) {
        event.inputStates = inputStates;
        onKeyup(event);
      },
      false
    );

    stars.pushArray(createStars(50, 1));
    stars.pushArray(createStars(30, 3));
    stars.pushArray(createStars(15, 6));
    stars.pushArray(createStars(1, 9));

    createAsteroids(80, 8, w * 2, w * 10, obstacles);

    vitesse = 1;
    requestAnimationFrame(draw);
  };

  var draw = timestamp => {
    switch (gameState) {
      case gameStates.mainMenu:
        drawMainMenu(timestamp);
        break;
      case gameStates.gameRunning:
        drawGameRunning(timestamp);
        break;
      case gameStates.gameLevelWon:
        drawGameLevelWon(timestamp);
        break;
      case gameStates.gameOver:
        drawGameOver(timestamp);
        break;
    }

    requestAnimationFrame(draw);
  };

  var drawMainMenu = timestamp => {};

  var drawGameRunning = timestamp => {
    ctx.clearRect(0, 0, w, h);

    // Draw the decorations first
    stars.forEach(s => {
      s.draw(ctx);
      s.move(vitesse);
    });

    if (joueur[0]) {
      if(joueur[0].state != entityStates.alive){
        vitesse *= 0.97;
      }
      joueur[0].move(1, inputStates);
      joueur[0].draw(ctx);

      if (inputStates.space) {
        joueur[0].activateShield();
        inputStates.space = false;
      }
    }

    obstacles.forEach(o => {
      o.draw(ctx);
      o.move(vitesse);
    });
    // obstacles[0].x -= 2;
    lasers.forEach(p => p.draw(ctx));

    if (joueur[0]) testeCollisions(joueur[0], obstacles, lasers, stars);

    ctx.fillText("Score : " + 50, canvas.width - 50, 20);
    ctx.fillText("Vies : " + 1, canvas.width - 50, 40);
  };

  var drawGameOver = timestamp => {};

  return {
    start: start
  };
};

function createStars(n, layer) {
  let stars = [];
  for (let i = 0; i < n; i++) {
    stars.push(new ParallaxStar(Math.random() * w, Math.random() * h, layer));
  }
  return stars;
}

function createAsteroids(n, s, xStart, xEnd, array) {
  let SPRITESHEET_URL = "./asteroids.png";
  let SPRITE_WIDTH = 128;
  let SPRITE_HEIGHT = 128;
  let NB_POSTURES = 4;
  let NB_SPRITES_PER_ROW = 2;
  let delta = 30;

  loadAssetsFractional(
    SPRITESHEET_URL,
    SPRITE_WIDTH,
    SPRITE_HEIGHT,
    NB_POSTURES,
    function(sprites) {
      for (let i = 0; i < n; i++) {
        let x = xStart + Math.random() * (xEnd - xStart + 1);
        let y = Math.random() * h;
        let asteroid = new Asteroid(
          x,
          y,
          (SPRITE_WIDTH / 2) - delta,
          -s,
          sprites[Math.floor(Math.random() * NB_POSTURES)],
          0.25 + Math.random() * 0.75
        );
        array.push(asteroid);
      }
    }
  );
}

function createJoueur(xPos, yPos, joueur, scale) {
  let SPRITESHEET_URL = "./joueur.png";
  let SPRITE_WIDTH = 64;
  let SPRITE_HEIGHT = 29;
  let NB_POSTURES = 1;
  let NB_SPRITES_PER_ROW = 1;

  loadAssetsAnimated(
    SPRITESHEET_URL,
    SPRITE_WIDTH,
    SPRITE_HEIGHT,
    NB_POSTURES,
    4,
    function(sprites) {
      joueur[0] = new Triangle(
        xPos,
        yPos,
        SPRITE_WIDTH,
        SPRITE_HEIGHT,
        sprites,
        scale
      );
      createExplosionSprite(joueur[0], scale);
      createShieldSprite(joueur[0], 0.5);
    }
  );
}

function createExplosionSprite(joueur, scale){
  let SPRITESHEET_URL = "./explosion.png";
  let SPRITE_WIDTH = 128;
  let SPRITE_HEIGHT = 128;
  let NB_POSTURES = 1;
  let NB_SPRITES_PER_ROW = 4;
  loadAssetsAnimated(
    SPRITESHEET_URL,
    SPRITE_WIDTH,
    SPRITE_HEIGHT,
    NB_POSTURES,
    14,
    function(sprites) {
      sprites[0].setNbImagesPerSecond(7);
      joueur.explosion = sprites;
    }
  );
}

function createShieldSprite(joueur, scale){
  let SPRITESHEET_URL = "./ring.png";
  let SPRITE_WIDTH = 256;
  let SPRITE_HEIGHT = 256;
  let NB_POSTURES = 1;
  let NB_SPRITES_PER_ROW = 1;
  loadAssetsAnimated(
    SPRITESHEET_URL,
    SPRITE_WIDTH,
    SPRITE_HEIGHT,
    NB_POSTURES,
    1,
    function(sprites) {
      sprites[0].setNbImagesPerSecond(7);
      joueur.shield_sprite = sprites;
    }
  );
}

/*
function createBoss(boss, scale) {
  let SPRITESHEET_URL = "./head_sheet.png";
  let SPRITE_WIDTH = 128;
  let SPRITE_HEIGHT = 128;
  let NB_POSTURES = 1;
  let NB_SPRITES_PER_ROW = 1;
  loadAssetsAnimated(
    SPRITESHEET_URL,
    SPRITE_WIDTH,
    SPRITE_HEIGHT,
    NB_POSTURES,
    14,
    function(sprites) {
      sprites[0].setNbImagesPerSecond(7);
      boss[0] = new Boss(x, y, r, v, img, scale)
    }
  );
}
*/