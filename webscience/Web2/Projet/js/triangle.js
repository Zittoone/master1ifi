class Triangle {
    constructor(x, y, l, h) {
        this.x = x;
        this.y = y;
        this.vx = 0;
        this.vy = 0;
        this.ax = 0;
        this.ay = 0;
        this.r = 0;
        this.current = 0;
        this.colors = ['#029DAF', '#E5D599', '#FFC219', '#F07C19', '#E32551'];

    }

    applyFriction() {
        let friction = 0.01;
        var speed = Math.sqrt(this.vx * this.vx + this.vy * this.vy),
            angle = Math.atan2(this.vy, this.vx);
        if (speed > friction) {
            speed -= friction;
        } else {
            speed = 0;
        }
        this.vx = Math.cos(angle) * speed;
        this.vy = Math.sin(angle) * speed;
    }


    move(delta, inputStates) {

        this.vx += this.ax;
        this.vy += this.ay;

        this.applyFriction();

        this.x += this.vx;
        this.y += this.vy;


        if (inputStates.right) {
            this.r = 0;
            this.ax = Math.cos(this.r) * 0.20;
        } else if (inputStates.left) {
            this.r = Math.PI;
            this.ax = Math.cos(this.r) * 0.20;
        } else {
            this.ax = 0;
        }

        if (inputStates.up) {
            this.r = Math.PI + Math.PI / 2;
            this.ay = Math.sin(this.r) * 0.20;
        } else if (inputStates.down) {
            this.r = Math.PI / 2;
            this.ay = Math.sin(this.r) * 0.20;
        } else {
            this.ay = 0;
        }

    }

    draw(ctx) {

        ctx.save();

        let rad = (this.rot * Math.PI) / 180;
        ctx.translate(this.x, this.y);
        ctx.rotate(rad);

        ctx.strokeStyle = this.colors[this.current];
        ctx.fillStyle = this.colors[this.current + 1];

        ctx.beginPath();
        ctx.moveTo(0, -60);
        ctx.lineTo(-20, 0);
        ctx.lineTo(20, 0);
        ctx.lineTo(0, -60);
        ctx.fill();
        ctx.stroke();

        if (this.r != Math.PI) {
            ctx.beginPath();
            ctx.moveTo(-10, 3);
            ctx.lineTo(-10, 10);
            ctx.lineTo(0, 6);
            ctx.lineTo(10, 10);
            ctx.lineTo(10, 3);
            ctx.lineTo(-10, 3);
            ctx.stroke();
        }

        ctx.restore();
    }

    nextColor() {
        if (this.current++ == this.colors.length - 1) {
            this.current = 0;
        }
    }
}