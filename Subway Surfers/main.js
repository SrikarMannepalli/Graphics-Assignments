var player1;
var tracks_left = [];
var tracks_middle = [];
var tracks_right = [];
var wall = [];
var powerups = [];
var tunnels = [];
var score = 0;
var trains = [];
var greyScale = 0;
var flash = 0;
var flashWhite = 1;
var obstacles = [];
var gameOver = 0;
var firstTime = 0;
var flashStartTime= 0;
var count = 0;
var count1 = 0;
var scoredis = []
var check = 0;
// var obstacle2;
main();

//
// Start here
//

function main() {

    const canvas = document.querySelector('#glcanvas');
    const gl = canvas.getContext('webgl') || canvas.getContext('experimental-webgl');

    //Initiating objects:
    createMap(gl);
    // If we don't have a GL context, give up now

    if (!gl) {
        alert('Unable to initialize WebGL. Your browser or machine may not support it.');
        return;
    }

    const programInfoColor = getInfoColor(gl);
    const programInfoTexture = getInfoTexture(gl);
    const programInfoTextureColor = getInfoTextureColor(gl);
    const programInfoTextureGreyScale = getInfoTextureGreyScale(gl);
    const programInfoTextureColorGreyScale = getInfoTextureColorGreyScale(gl);
    const programInfoColorGreyScale = getInfoColorGreyScale(gl);
    // Here's where we call the routine that builds all the


    var then = 0;

    // Draw the scene repeatedly
    function render(now) {
        now *= 0.001; // convert to seconds
        const deltaTime = now - then;
        then = now;
        //updating tracks
        document.getElementById('score').innerHTML = score;
        for (var i = 0; i < powerups.length; i++) {
            if (!powerups[i].destroyed) {
                detectCollPlayerPowerups(i);
            }
        }
        for (var i = 0; i < tunnels.length; i++) {
            if (tunnels[i].positionCollCheck[2] <= player1.positionCollCheck[2]) {
                detectCollTunnelPlayer(i);
            }
        }
        for (var i = 0; i < obstacles.length; i++) {
            if (obstacles[i].positionCollCheck[2] <= player1.positionCollCheck[2]) {
                detectCollObstaclePlayer(i);
            }
        }

        for (var i = 0; i < trains.length; i++) {
            trains[i].positionCollCheck[2] += 0.01;
        }
        if (player1.jumpPowerupTaken) {
            var d = new Date();
            if (d.getTime() - player1.jumpPowerupStart >= 7000) {
                player1.jumpPowerupTaken = 0;
                player1.max_jump_height = 1.2;
                player1.jumpPowerupStart = 0;
            }
        }
        if (player1.flyPowerupTaken) {
            var d = new Date();
            if (d.getTime() - player1.flyPowerupStart >= 7000) {
                player1.flyPowerupTaken = 0;
                player1.flyPowerupStart = 0;
            }
        }
        if (player1.duck) {
            var d = new Date();
            if (d.getTime() - player1.duckTaken >= 500) {
                player1.duckTaken = 0;
                player1.duck = 0;
                player1.positionCollCheck[1]+=0.1;

            }
        }

        if(firstTime>=2) {
          gameOver = 1;
        }
        if(player1.positionCollCheck[2]<=-70) {
          gameOver = 1;
        }
        if(gameOver == 1) {
          check = 1;
          showScore();
          // alert("Score:" +score);
          // quit();
          // var scoredis = [];
          // while(score>0) {
          //   console.log("here to make 0");
          //   scoredis.push(new Score(gl,score%10,[2,0,1]));
          //   score = score/10;
          //   score = Math.floor(score);

        }
        drawScene(gl, programInfoColor, programInfoTexture, programInfoTextureColor, programInfoColorGreyScale, programInfoTextureGreyScale, programInfoTextureColorGreyScale, deltaTime);

        requestAnimationFrame(render);
    }
    requestAnimationFrame(render);

}

//
// Draw the scene.
//
function drawScene(gl, programInfoColor, programInfoTexture, programInfoTextureColor, programInfoColorGreyScale, programInfoTextureGreyScale, programInfoTextureColorGreyScale, deltaTime) {
    gl.clearColor(0.0, 0.0, 0.0, 1.0); // Clear to black, fully opaque
    gl.clearDepth(1.0); // Clear everything
    gl.enable(gl.DEPTH_TEST); // Enable depth testing
    gl.depthFunc(gl.LEQUAL); // Near things obscure far things

    // Clear the canvas before we start drawing on it.

    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

    // Create a perspective matrix, a special matrix that is
    // used to simulate the distortion of perspective in a camera.
    // Our field of view is 45 degrees, with a width/height
    // ratio that matches the display size of the canvas
    // and we only want to see objects between 0.1 units
    // and 100 units away from the camera.

    const fieldOfView = 45 * Math.PI / 180; // in radians
    const aspect = gl.canvas.clientWidth / gl.canvas.clientHeight;
    const zNear = 0.1;
    const zFar = 100.0;
    const projectionMatrix = mat4.create();

    // note: glmatrix.js always has the first argument
    // as the destination to receive the result.
    mat4.perspective(projectionMatrix,
        fieldOfView,
        aspect,
        zNear,
        zFar);

    // Set the drawing position to the "identity" point, which is
    // the center of the scene.
    var cameraMatrix = mat4.create();
    mat4.translate(cameraMatrix, cameraMatrix, [0, 0, 0]);
    if (!player1.flyPowerupTaken) {
        var cameraPosition = [
            player1.positionCollCheck[0], player1.positionCollCheck[1] + 0.5, player1.positionCollCheck[2] + 3
        ];
        var up = [0, 1, 0];
        var target = player1.positionCollCheck;
    } else {
        var cameraPosition = [
            player1.positionCollCheck[0], player1.positionCollCheck[1] + 0.5, player1.positionCollCheck[2] + 3
        ];
        var up = [0, 1, 0];
        var target = player1.positionCollCheck;
    }


    mat4.lookAt(cameraMatrix, cameraPosition, target, up);

    var viewMatrix = cameraMatrix; //mat4.create();

    //mat4.invert(viewMatrix, cameraMatrix);

    var viewProjectionMatrix = mat4.create();
    mat4.multiply(viewProjectionMatrix, projectionMatrix, viewMatrix);
if(gameOver == 0){
    if (greyScale == 0) {
        for (var i = 0; i < powerups.length; i++) {
            if (!powerups[i].destroyed) {
                powerups[i].drawPowerups(gl, viewProjectionMatrix, programInfoColor, deltaTime);
            }
        }
        for (var i = 0; i < tracks_left.length; i++) {
            tracks_left[i].drawTrack(gl, viewProjectionMatrix, programInfoTexture, deltaTime);
        }
        for (var i = 0; i < tracks_middle.length; i++) {
            tracks_middle[i].drawTrack(gl, viewProjectionMatrix, programInfoTexture, deltaTime);
        }
        for (var i = 0; i < tracks_right.length; i++) {
            tracks_right[i].drawTrack(gl, viewProjectionMatrix, programInfoTexture, deltaTime);
        }
        draw_wall(gl);
        for (var i = 0; i < wall.length; i++) {
            wall[i].drawWall(gl, viewProjectionMatrix, programInfoTextureColor, deltaTime);
        }
        player1.drawPlayer(gl, viewProjectionMatrix, programInfoTexture, deltaTime);
        police1.drawPolice(gl, viewProjectionMatrix, programInfoTexture, deltaTime);
        for (var i = 0; i < trains.length; i++) {
            trains[i].drawTrain(gl, viewProjectionMatrix, programInfoTexture, deltaTime);
        }
        for (var i = 0; i < obstacles.length; i++) {
            obstacles[i].drawObstacles(gl, viewProjectionMatrix, programInfoTexture, deltaTime);
        }
        for (var i = 0; i < tunnels.length; i++) {
            tunnels[i].drawTunnel(gl, viewProjectionMatrix, programInfoTexture, deltaTime);
        }
    } else {
        for (var i = 0; i < powerups.length; i++) {
            if (!powerups[i].destroyed) {
                powerups[i].drawPowerups(gl, viewProjectionMatrix, programInfoColorGreyScale, deltaTime);
            }
        }
        for (var i = 0; i < tracks_left.length; i++) {
            tracks_left[i].drawTrack(gl, viewProjectionMatrix, programInfoTextureGreyScale, deltaTime);
        }
        for (var i = 0; i < tracks_middle.length; i++) {
            tracks_middle[i].drawTrack(gl, viewProjectionMatrix, programInfoTextureGreyScale, deltaTime);
        }
        for (var i = 0; i < tracks_right.length; i++) {
            tracks_right[i].drawTrack(gl, viewProjectionMatrix, programInfoTextureGreyScale, deltaTime);
        }

        draw_wall(gl);
        for (var i = 0; i < wall.length; i++) {
            wall[i].drawWall(gl, viewProjectionMatrix, programInfoTextureColorGreyScale, deltaTime);
        }
        player1.drawPlayer(gl, viewProjectionMatrix, programInfoTextureGreyScale, deltaTime);
        police1.drawPolice(gl, viewProjectionMatrix, programInfoTextureGreyScale, deltaTime);
        for (var i = 0; i < trains.length; i++) {
            trains[i].drawTrain(gl, viewProjectionMatrix, programInfoTextureGreyScale, deltaTime);
        }
        for (var i = 0; i < obstacles.length; i++) {
            obstacles[i].drawObstacles(gl, viewProjectionMatrix, programInfoTextureGreyScale, deltaTime);
        }
        for (var i = 0; i < tunnels.length; i++) {
            tunnels[i].drawTunnel(gl, viewProjectionMatrix, programInfoTextureGreyScale, deltaTime);
        }
    }
  }
  else  {
    if(check == 1) {
    for(var i=0;i<scoredis.length;i++) {
        scoredis[i].drawScore(gl, viewProjectionMatrix, programInfoTexture, deltaTime);
    }
  }
  }
}

function draw_wall(gl) {
  var d = new Date();
  var currtime = d.getTime();
  if(flash == 1) {
    count++;
  }
  else if(flash == 0) {
    count1++;
  }
  if(flash == 1 && count%60==0){
    count = 0;
    flash =0;
  }
  else if(flash == 0 && count1%60 == 0) {
    count1 = 0;
    flash = 1;
  }
    for (var i = 0; i < wall.length; i++) {
        if (flash == 1) {
                while (wall[i].colors.length > 0) {
                    wall[i].colors.pop();
                }
                for (var j = 0; j < 6; j++) {
                  // const c = [0.0 / 255.0, 0.0 / 255.0, 0.0 / 255.0, 1.0];
                    const c = [60.0 / 255.0, 60.0 / 255.0, 60.0 / 255.0, 1.0];
                    // Repeat each color four times for the four vertices of the face
                    wall[i].colors = wall[i].colors.concat(c, c, c, c);
                }

                const colorBuffer = gl.createBuffer();
                gl.bindBuffer(gl.ARRAY_BUFFER, colorBuffer);
                gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(wall[i].colors), gl.STATIC_DRAW);
                wall[i].buffer.color = colorBuffer;

        } else if(flash == 0) {
          // flash = 1;
            while (wall[i].colors.length > 0) {
                wall[i].colors.pop();
            }
            for (var j = 0; j < 6; ++j) {
                const c = [255.0 / 255.0, 255.0 / 255.0, 255.0 / 255.0, 1.0];
                // const c = [0 / 255.0, 0 / 255.0, 0 / 255.0, 1.0];

                // Repeat each color four times for the four vertices of the face
                wall[i].colors = wall[i].colors.concat(c, c, c, c);
            }
            const colorBuffer = gl.createBuffer();
            gl.bindBuffer(gl.ARRAY_BUFFER, colorBuffer);
            gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(wall[i].colors), gl.STATIC_DRAW);
            wall[i].buffer.color = colorBuffer;
        }
    }

}

function createMap(gl) {
    player1 = new Player(gl, [0, 1.35, 0]);
    police1 = new Police(gl, [0, 1.35, 1]);
    trains.push(new Train(gl, [0.7, 0.7, 2.0], [-1, 0.5, -7], 2));
    trains.push(new Train(gl, [0.7, 0.7, 2.0], [-1, 0.5, -70], 1));
    trains.push(new Train(gl, [0.7, 0.7, 2.0], [1, 0.5, -80], 1));
    trains.push(new Train(gl, [0.7, 0.7, 2.0], [0, 0.5, -75], 1));
    trains.push(new Train(gl, [0.7, 0.7, 2.0], [0, 0.5, -25], 2));
    trains.push(new Train(gl, [0.7, 0.7, 2.0], [0, 0.5, -25], 2));
    trains.push(new Train(gl, [0.7, 0.7, 2.0], [-1, 0.5, -30], 2));

    obstacles.push(new Obstacles(gl, [0.5, 0.5, 0.1], [0, 0.3, -5], 1));
    obstacles.push(new Obstacles(gl, [0.5, 0.3, 0.1], [1, 0.3, -4], 2));
    obstacles.push(new Obstacles(gl, [0.5, 0.3, 0.1], [1, 0.3, -8], 2));
    tunnels.push(new Tunnel(gl, 3, [0, 1, -8]));
    tunnels.push(new Tunnel(gl, 2, [0, 1, -67]));
    for (var i = 0; i < 2; i++) {
        powerups.push(new Powerups(gl, [0.1, 0.1, 0.1], [-1, 0.2, -i * 1], 3));
    }
    for (var i = 0; i < 15; i++) {
        powerups.push(new Powerups(gl, [0.1, 0.1, 0.1], [-1, 0.2, -9-i * 1], 2));
    }
    for (var i = 0; i < 45; i++) {
      powerups.push(new Powerups(gl, [0.1, 0.1, 0.1], [-1, 3, -9-i * 1], 1));
      powerups.push(new Powerups(gl, [0.1, 0.1, 0.1], [0, 3, -9-i * 1], 1));
      powerups.push(new Powerups(gl, [0.1, 0.1, 0.1], [1, 3, -9-i * 1], 1));
    }
    for (var i = 0; i < 15; i++) {
      if(i%1 == 0) {
      powerups.push(new Powerups(gl, [0.1, 0.1, 0.1], [1, 3, -45-i * 1], 1));
    }
    if(i%1==1) {
      powerups.push(new Powerups(gl, [0.1, 0.1, 0.1], [1, 3, -45-i * 1], 2));
    }
    if(i%1==2) {
      powerups.push(new Powerups(gl, [0.1, 0.1, 0.1], [1, 3, -45-i * 1], 3));
    }
    }
    for (var i = 0; i < 15; i++) {
        powerups.push(new Powerups(gl, [0.1, 0.1, 0.1], [1, 0.2, -9-i * 1], 1));
    }
    for (var i = 0; i < 2; i++) {
        powerups.push(new Powerups(gl, [0.1, 0.1, 0.1], [0, 0.2, -12-i * 1], 3));
    }
    powerups.push(new Powerups(gl, [0.1, 0.1, 0.1], [-1, 1.0, -5], 1));
    powerups.push(new Powerups(gl, [0.1, 0.1, 0.1], [-1, 1.0, -6], 1));
    powerups.push(new Powerups(gl, [0.1, 0.1, 0.1], [-1, 1.0, -6.5], 1));
    for (var i = 0; i < 75; i++) {
        tracks_left.push(new Track(gl, [1, 0.1, 1], [-1, 0, 0 - i * 1], 'track.jpeg'));
    }
    for (var i = 0; i < 75; i++) {
        tracks_middle.push(new Track(gl, [1, 0.1, 1], [0, 0, 0 - i * 1], 'track.jpeg'));
    }
    for (var i = 0; i < 75; i++) {
        tracks_right.push(new Track(gl, [1, 0.1, 1], [1, 0, 0 - i * 1], 'track.jpeg'));
    }
    for (var i = 0; i < 75; i++) {
        wall.push(new Wall(gl, [0.1, 3.0, 1.0], [1.6, 1.4, -i], 'wall.jpg'));
    }
    for (var i = 0; i < 75; i++) {
        wall.push(new Wall(gl, [0.1, 3.0, 1.0], [-1.6, 1.4, -i], 'wall.jpg'));
    }
    obstacles.push(new Obstacles(gl, [0.5, 0.5, 0.1], [0, 0.3, -35], 1));
    obstacles.push(new Obstacles(gl, [0.5, 0.3, 0.1], [1, 0.3, -40], 2));
    obstacles.push(new Obstacles(gl, [0.5, 0.3, 0.1], [-1, 0.3, -65], 2));
    obstacles.push(new Obstacles(gl, [0.5, 0.5, 0.1], [0, 0.3, -55], 1));
    obstacles.push(new Obstacles(gl, [0.5, 0.3, 0.1], [-1, 0.3, -60], 2));
    obstacles.push(new Obstacles(gl, [0.5, 0.3, 0.1], [1, 0.3, -60], 2));
    for(var i=0;i<10;i++) {
      powerups.push(new Powerups(gl, [0.1, 0.1, 0.1], [0, 0.2, -55-i], 1));
      powerups.push(new Powerups(gl, [0.1, 0.1, 0.1], [-1, 0.2, -55-i], 1));
      powerups.push(new Powerups(gl, [0.1, 0.1, 0.1], [1, 0.2, -55-i], 1));
    }
}

function showScore() {
  console.log("game");
  var textCanvas  = document.getElementById('text');
  var ctx = textCanvas.getContext('2d');
  ctx.clearRect(0,0,ctx.canvas.width, ctx.canvas.height);
  ctx.font = "30px Arial";
  ctx.fillStyle = "white";
  var dis1 = "Game Over!!!!";
  var dis = "Score: " + score;
  ctx.fillText(dis1, 620, 330);
  ctx.fillText(dis, 630, 360);
}
