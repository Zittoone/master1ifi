class Level {
    constructor(n) {
        this.portals = {};
        this.obstacles = {};
        this.length = 500;
        this.number = n;
    }

    addPortal(portal) {
        this.portals.push(portal);
    }

    addObstacle(obstacle) {
        this.obstacles.push(obstacle);
    }

}