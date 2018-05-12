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


var GF = () => {

    var gameState = gameStates.gameRunning;
    var inputStates = {};

    /** Level related variables */
    var currentLevel = 1;
    var lasers = [];
    var obstacles = [];
    var stars = [];
    var joueur;
    var length;
    var vitesse;

    /** Only function visbile by the API */
    var start = function(timestamp) {
        joueur = new Triangle(w / 2 - 80 / 2, h / 2 - 48 / 2, 80, 48);
        joueur.rot = 90;

        window.addEventListener('keydown', function(event) {
            event.inputStates = inputStates;
            onKeydown(event);
        }, false);
        window.addEventListener('keyup', function(event) {
            event.inputStates = inputStates;
            onKeyup(event);
        }, false);

        stars.pushArray(createStars(50, 1));
        stars.pushArray(createStars(30, 3));
        stars.pushArray(createStars(15, 6));
        stars.pushArray(createStars(1, 9));

        obstacles.pushArray(createAsteroids(60, 20, 8, w * 2, w * 10));

        vitesse = 2;
        requestAnimationFrame(draw);
    };

    var draw = (timestamp) => {
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

    var drawMainMenu = (timestamp) => {

    };

    var drawGameRunning = (timestamp) => {

        ctx.clearRect(0, 0, w, h);

        // Draw the decorations first
        stars.forEach(s => {
            s.draw(ctx);
            s.move();
        });

        joueur.move(1, inputStates);
        joueur.draw(ctx);

        if (inputStates.space) {
            joueur.nextColor();
            inputStates.space = false;

        }



        obstacles.forEach(o => {
            o.draw(ctx);
            o.move();
        });
        // obstacles[0].x -= 2;
        lasers.forEach(p => p.draw(ctx));

        testeCollisions(joueur, obstacles, lasers, stars);

        ctx.fillText("Score : " + 50, canvas.width - 50, 20);
        ctx.fillText("Vies : " + 1, canvas.width - 50, 40);
    };

    var drawGameOver = (timestamp) => {


    };

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

function createAsteroids(n, r, s, xStart, xEnd) {
    let asteroids = [];
    for (let i = 0; i < n; i++) {
        let cercle = new Cercle(xStart + Math.random() * ((xEnd - xStart) + 1), Math.random() * h, r);
        cercle.vitesseX = -s;
        cercle.couleur = "grey";
        asteroids.push(cercle);
    }
    return asteroids;
}