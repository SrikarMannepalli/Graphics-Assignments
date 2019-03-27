function detectCollPlayerPowerups(powerupNum) {
	if (0.5 * player1.width + 0.5 * powerups[powerupNum].width >= Math.abs(player1.positionCollCheck[0] - powerups[powerupNum].pos[0]) &&
		0.5 * player1.height + 0.5 * powerups[powerupNum].height >= Math.abs(player1.positionCollCheck[1] - powerups[powerupNum].pos[1]) &&
		0.5 * player1.depth + 0.5 * powerups[powerupNum].depth >= Math.abs(player1.positionCollCheck[2] - powerups[powerupNum].pos[2])) {
		powerups[powerupNum].destroyed = true;
		var d = new Date();
		var type = powerups[powerupNum].type;
		if (type == 1) {
			score += 10;
		} else if (type == 2) {
			player1.max_jump_height = 2.8;
			player1.jumpPowerupTaken = 1;
			player1.jumpPowerupStart = d.getTime();
		} else if (type == 3) {
			player1.flyPowerupTaken = 1;
			player1.positionCollCheck[1] += 3;
			player1.flyPowerupStart = d.getTime();

		}
	}
}

function detectCollTunnelPlayer(tunnelNum) {
	if (0.5 * player1.width + 0.5 * tunnels[tunnelNum].width >= Math.abs(player1.positionCollCheck[0] - tunnels[tunnelNum].positionCollCheck[0]) &&
		0.5 * player1.height + 0.5 * tunnels[tunnelNum].height >= Math.abs(player1.positionCollCheck[1] - tunnels[tunnelNum].positionCollCheck[1]) &&
		0.5 * player1.depth + 0.5 * tunnels[tunnelNum].depth >= Math.abs(player1.positionCollCheck[2] - tunnels[tunnelNum].positionCollCheck[2])) {
		if (player1.track != tunnels[tunnelNum].trackFree) {
			gameOver = 1;
		}
	}
}

function detectCollTrainPlayer() {
	for(var i=0;i<trains.length;i++) {
		if (0.5 * player1.width + 0.5 * trains[i].width >= Math.abs(player1.positionCollCheck[0] - trains[i].positionCollCheck[0]) &&
			0.5 * player1.height + 0.5 * trains[i].height >= Math.abs(player1.positionCollCheck[1] - trains[i].positionCollCheck[1]) &&
			0.5 * player1.depth + 0.5 * trains[i].depth >= Math.abs(player1.positionCollCheck[2] - trains[i].positionCollCheck[2])) {
				if(player1.positionCollCheck[1]>trains[i].positionCollCheck[1]+0.5*trains[i].height) {
					return -2;
				}
				return i;
			}
	}
	return -1;
}

function detectCollObstaclePlayer(obstacleNum) {
	if(obstacles[obstacleNum].type == 1){
	if (0.5 * player1.width + 0.5 * obstacles[obstacleNum].width >= Math.abs(player1.positionCollCheck[0] - obstacles[obstacleNum].positionCollCheck[0]) &&
		0.5 * player1.height+0.5*(obstacles[obstacleNum].height)>= Math.abs(player1.positionCollCheck[1] - obstacles[obstacleNum].positionCollCheck[1]) &&
		0.5 * player1.depth + 0.5 * obstacles[obstacleNum].depth >= Math.abs(player1.positionCollCheck[2] - obstacles[obstacleNum].positionCollCheck[2])) {
			if(player1.duck == 0) {
				gameOver = 1;

			}
		}
	}
	else {
		if (0.5 * player1.width + 0.5 * obstacles[obstacleNum].width >= Math.abs(player1.positionCollCheck[0] - obstacles[obstacleNum].positionCollCheck[0]) &&
			0.5 * player1.height + 0.5 * obstacles[obstacleNum].height >= Math.abs(player1.positionCollCheck[1] - obstacles[obstacleNum].positionCollCheck[1]) &&
			0.5 * player1.depth + 0.5 * obstacles[obstacleNum].depth >= Math.abs(player1.positionCollCheck[2] - obstacles[obstacleNum].positionCollCheck[2])) {
				player1.positionCollCheck[2]-=1.0;
				police1.positionCollCheck[2]=player1.positionCollCheck[2]+1;
				player1.vel = player1.initial_vel;
				firstTime +=1;
			}
	}
}
