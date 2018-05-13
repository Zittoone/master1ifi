class Triangle {
  constructor(x, y, l, h, sprites, scale) {
    this.x = x;
    this.y = y;
    this.scale = scale || 1;
    this.l = l * this.scale;
    this.h = h * this.scale;
    this.vx = 0;
    this.vy = 0;
    this.ax = 0;
    this.ay = 0;
    this.r = 0;
    this.shield_activated = false;
    this.shield_cooldown = 7;
    this.shield_last_ativated = performance.now() - this.shield_cooldown * 1000;
    this.shield_sprite = [];
    this.sprites = sprites;
    this.explosion = [];
    this.state = entityStates.alive;
  }

  explode() {
    this.state = entityStates.exploding;
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
    if (this.state != entityStates.alive) return;

    this.vx += this.ax;
    this.vy += this.ay;

    this.applyFriction();

    this.x += this.vx;
    this.y += this.vy;

    if (inputStates.right) {
      this.r = 0;
      this.ax = Math.cos(this.r) * 0.2;
    } else if (inputStates.left) {
      this.r = Math.PI;
      this.ax = Math.cos(this.r) * 0.2;
    } else {
      this.ax = 0;
    }

    if (inputStates.up) {
      this.r = Math.PI + Math.PI / 2;
      this.ay = Math.sin(this.r) * 0.2;
    } else if (inputStates.down) {
      this.r = Math.PI / 2;
      this.ay = Math.sin(this.r) * 0.2;
    } else {
      this.ay = 0;
    }
  }

  draw(ctx) {
    ctx.save();

    if (this.state == entityStates.alive) {
      this.sprites[0].draw(ctx, this.x, this.y, this.scale, 0);
      let timeLeft = performance.now() - this.shield_last_ativated;
      if (timeLeft <= this.shield_cooldown * 1000) {
        let offset = this.l * 0.4;
        ctx.fillRect(
          this.x + offset / 2,
          this.y - this.h / 2,
          this.l - offset / 2,
          5
        );
        ctx.fillStyle = "green";
        ctx.fillRect(
          this.x + offset / 2,
          this.y - this.h / 2,
          (this.l - offset / 2) * timeLeft / (this.shield_cooldown * 1000),
          5
        );
      }

      if (this.shield_activated == true) {
        this.shield_sprite[0].draw(
          ctx,
          this.x - this.l / 5,
          this.y - this.h * 1.2,
          0.4
        );
      }
    }

    if (this.state == entityStates.exploding) {
      this.explosion[0].draw(
        ctx,
        this.x - this.l / 2,
        this.y - this.h,
        this.scale,
        0
      );
      if (
        this.explosion[0].spriteArray.length - 1 ==
        this.explosion[0].currentFrame
      )
        this.state = entityStates.dead;
    }

    ctx.restore();
  }

  activateShield() {
    let now = performance.now();
    if (now - this.shield_last_ativated >= this.shield_cooldown * 1000) {
      this.shield_last_ativated = now;
      this.shield_activated = true;
      var self = this;
      setTimeout(function() {
        self.shield_activated = false;
      }, 2000);
    }
  }

  resetSpeed() {
    this.vx = 0;
    this.vy = 0;
    this.ax = 0;
    this.ay = 0;
  }
}
