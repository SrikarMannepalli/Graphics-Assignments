
function degreesToRadians(degrees) {
  return degrees * (Math.PI/180);
}

function getCube(width, height, depth) {
  // console.log(width, height, depth);
  var positions = [
       // Front face
       -0.5*width,  -0.5*height,  0.5*depth,
        0.5*width,  -0.5*height,  0.5*depth,
        0.5*width,   0.5*height,  0.5*depth,
       -0.5*width,   0.5*height,  0.5*depth,
       //back face
       -0.5*width,  -0.5*height, -0.5*depth,
        0.5*width,  -0.5*height, -0.5*depth,
        0.5*width,   0.5*height, -0.5*depth,
       -0.5*width,   0.5*height, -0.5*depth,
       //top face
       -0.5*width,   0.5*height, -0.5*depth,
        0.5*width,   0.5*height, -0.5*depth,
        0.5*width,   0.5*height,  0.5*depth,
       -0.5*width,   0.5*height,  0.5*depth,
       //bottom face
       -0.5*width,  -0.5*height, -0.5*depth,
        0.5*width,  -0.5*height, -0.5*depth,
        0.5*width,  -0.5*height,  0.5*depth,
       -0.5*width,  -0.5*height,  0.5*depth,
       //left face
       -0.5*width,  -0.5*height, -0.5*depth,
       -0.5*width,   0.5*height, -0.5*depth,
       -0.5*width,   0.5*height,  0.5*depth,
       -0.5*width,  -0.5*height,  0.5*depth,
       //right face
        0.5*width,  -0.5*height, -0.5*depth,
        0.5*width,   0.5*height, -0.5*depth,
        0.5*width,  -0.5*height,  0.5*depth,
        0.5*width,   0.5*height,  0.5*depth,
  ];
  return positions
}

function getIndicesCuboids() {
  const indices = [
      0, 1, 2,    0, 2, 3, // front
      4, 5, 6,    4, 6, 7,
      8, 9, 10,   8, 10, 11,
      12, 13, 14, 12, 14, 15,
      16, 17, 18, 16, 18, 19,
      20, 21, 22, 20, 22, 23,
  ];

  return indices;
}

function getTextureCoords() {
  const textureCoordinates = [
      // Front
      0.0, 0.0,
      1.0, 0.0,
      1.0, 1.0,
      0.0, 1.0,
      // Back
      0.0, 0.0,
      1.0, 0.0,
      1.0, 1.0,
      0.0, 1.0,
      // Top
      0.0, 0.0,
      1.0, 0.0,
      1.0, 1.0,
      0.0, 1.0,
      // Bottom
      0.0, 0.0,
      1.0, 0.0,
      1.0, 1.0,
      0.0, 1.0,
      // Right
      0.0, 0.0,
      1.0, 0.0,
      1.0, 1.0,
      0.0, 1.0,
      // Left
      0.0, 0.0,
      1.0, 0.0,
      1.0, 1.0,
      0.0, 1.0,
  ];
  return textureCoordinates;
}

function getCylinder(radius1, radius2, cylinderLength) {
  var positions = [];
  var n = 20,p,q;
  var l;

    // for(var i=0;i<360*18;i+=18) {
    //     positions.push(0.0);
    //     positions.push(radius1*Math.cos(degreesToRadians(i/18)));
    //     positions.push(-radius1*Math.sin(degreesToRadians(i/18)));
    //     positions.push(cylinderLength);
    //     positions.push(radius1*Math.cos(degreesToRadians(i/18)));
    //     positions.push(-radius1*Math.sin(degreesToRadians(i/18)));
    //     positions.push(0.0);
    //     positions.push(radius1*Math.cos(degreesToRadians(i/18+1)));
    //     positions.push(-radius1*Math.sin(degreesToRadians(i/18+1)));
    //     positions.push(positions[i+6]);
    //     positions.push(positions[i+7]);
    //     positions.push(positions[i+8]);
    //     positions.push(positions[i+3]);
    //     positions.push(positions[i+4]);
    //     positions.push(positions[i+5]);
    //     positions.push(cylinderLength);
    //     positions.push(positions[i+7]);
    //     positions.push(positions[i+8]);
    // }
    for(var k=0;k<1;k++) {
        if(k == 0) l = 0.0;
        else l = cylinderLength;
        for(var i=0;i<9*n;i+=9) {
                p = (i+1)/9;
                q = p+1;
                positions.push(l);
                positions.push(0.0);
                positions.push(0.0);
                positions.push(l);
                positions.push(radius1*(Math.sin((p*Math.PI*2)/n)));
                positions.push(radius1*(Math.cos((p*Math.PI*2)/n)));
                positions.push(l);
                positions.push(radius1*(Math.sin((q*Math.PI*2)/n)));
                positions.push(radius1*(Math.cos((q*Math.PI*2)/n)));
          }
      }
    return positions;
}

function getCylinderIndices() {
  var indices = [];
  for(var i=0;i<360*6*0+3*20*1;i++) {
    indices.push(i);
  }

  return indices;
}
