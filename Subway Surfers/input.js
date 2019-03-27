document.addEventListener('keyup', function(event) {
    if(event.keyCode == 37 && player1.track!=0 && player1.track!=4) {
      if(player1.track == 1 && player1.flyPowerupTaken==0) {
        player1.direction = -1;
        player1.track = 0;
      }
      else if (player1.track == 2 || player1.track == 3) {
        player1.positionCollCheck[0]-=1;
        var collision = detectCollTrainPlayer();
        player1.positionCollCheck[0]+=1;
        if(collision == -1) {
          player1.positionCollCheck[0] -= 1;
          player1.track -= 1;
        }
        else {
          player1.prevTrack = player1.track;
          player1.track  = -1;
          player1.collLeftPos = [];
          player1.collLeftPos.push(player1.positionCollCheck[0]);
          player1.collLeftPos.push(player1.positionCollCheck[1]);
          player1.collLeftPos.push(player1.positionCollCheck[2]);
          player1.direction = -1;
        }

      }
    }
    else if(event.keyCode == 39 && player1.track!=0 && player1.track!=4) {
      if(player1.track == 3 && player1.flyPowerupTaken==0) {
        player1.direction = 1;
        player1.track = 4;
      }
      else if (player1.track == 1 || player1.track == 2) {
        player1.positionCollCheck[0]+=1;
        var collision = detectCollTrainPlayer();
        player1.positionCollCheck[0]-=1;
        if(collision == -1) {
          player1.positionCollCheck[0] += 1;
          player1.track += 1;
        }
        else {
          player1.prevTrack = player1.track;
          player1.track  = 5;
          player1.collLeftPos = [];
          player1.collLeftPos.push(player1.positionCollCheck[0]);
          player1.collLeftPos.push(player1.positionCollCheck[1]);
          player1.collLeftPos.push(player1.positionCollCheck[2]);
          player1.direction = 1;
        }
      }
  }
  else if(event.keyCode == 32) {
    player1.jump = 1;
  }
  else if(event.keyCode == 40 && player1.duck ==0) {
    player1.duck = 1;
    player1.positionCollCheck[1]-=0.1;
    var d = new Date();
    player1.duckTaken = d.getTime();
  }
  else if(event.keyCode == 71) {
    if(greyScale == 0) {
      greyScale = 1;
    }
    else {
      greyScale = 0;
    }
  }
  else if(event.keyCode == 70) {
    // if(flash == 0) {
    //   flash = 1;
    //   var d = new Date();
    //   flashStartTime = d.getTime();
    //   count = 0;
    // }
    // else {
    //   flash = 0;
    // }
  }
});
