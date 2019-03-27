/// <reference path="webgl.d.ts" />

let Police = class {
    constructor(gl, pos) {

        this.bodywidth = 0.15;
        this.bodyheight = 0.20;
        this.bodydepth = 0.05;
        this.headheight = 0.05;
        this.headwidth = 0.07;
        this.headdepth = 0.09;
        this.handheight = 0.20;
        this.handwidth = 0.02;
        this.handdepth = 0.02;
        this.legheight = 0.15;
        this.legwidth = 0.06;
        this.legdepth = 0.05;
        this.width = this.bodywidth+this.handwidth;
        this.height = this.bodyheight+this.headheight+this.legheight;
        this.depth = this.bodydepth;
        this.max_jump_height = 1.8;
        this.vel = 0.02;
        this.positionCollCheck = [];
        this.positionCollCheck.push(pos[0]);
        this.positionCollCheck.push(pos[1]);
        this.positionCollCheck.push(pos[2]);
        this.positions = [];
        this.rotation = [];
        this.prevRotation = [];
        this.rotationDirection = [];
        this.pos = [];
        var temp = pos;
        // this.rotation = 0;
        this.direction = 1;
        this.jump = 0; // jump = 0 ->on ground, 1-> in air.
        this.track = 2; //tracks leftmost - 1 middle - 2 right - 3,0 - moving left from and crashing, 4 - moving right from rightmost and crashing
        var temp = pos;
        this.positions = [];
        this.positions.push(getCube(this.bodywidth, this.bodyheight, this.bodydepth));//body
        this.pos.push([temp[0], temp[1]+0.5*this.bodyheight, temp[2]]);
        this.positions.push(getCube(this.headwidth, this.headheight, this.headdepth));//face
        this.pos.push([temp[0], temp[1]+0.5*this.headheight+this.bodyheight, temp[2]]);
        this.positions.push(getCube(this.handwidth, this.handheight, this.handdepth));//hand1
        this.pos.push([temp[0]-0.5*this.bodywidth-0.5*this.handwidth, temp[1]+0.5*this.bodyheight-0.05, temp[2]]);
        this.positions.push(getCube(this.handwidth, this.handheight, this.handdepth));//hand2
        this.pos.push([temp[0]+0.5*this.bodywidth+0.5*this.handwidth, temp[1]+0.5*this.bodyheight-0.05, temp[2]]);
        this.positions.push(getCube(this.legwidth, this.legheight, this.legdepth));//leg1
        this.pos.push([temp[0]-0.5*this.bodywidth+0.5*this.legwidth, temp[1]-0.5*this.legheight, temp[2]]);
        this.positions.push(getCube(this.legwidth, this.legheight, this.legdepth));//leg2
        this.pos.push([temp[0]+0.5*this.bodywidth-0.5*this.legwidth, temp[1]-0.5*this.legheight, temp[2]]);
        this.positionBuffer = [];
        for(var i=0;i<this.pos.length;i++) {
          this.positionBuffer.push(gl.createBuffer());
          gl.bindBuffer(gl.ARRAY_BUFFER, this.positionBuffer[i]);
          gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(this.positions[i]), gl.STATIC_DRAW);
        }
        for(var i=0;i<this.pos.length;i++) {
          this.rotation.push(0);
          this.prevRotation.push(0);
        }
        for(var i=0;i<this.pos.length;i++) {
          this.rotationDirection.push(1);
        }


            const indexBuffer = gl.createBuffer();
            gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, indexBuffer);

            // This array defines each face as two triangles, using the
            // indices into the vertex array to specify each triangle's
            // position.

            const indices = getIndicesCuboids();
            gl.bufferData(gl.ELEMENT_ARRAY_BUFFER,
                new Uint16Array(indices), gl.STATIC_DRAW);
                const textureBuffer = gl.createBuffer();
                gl.bindBuffer(gl.ARRAY_BUFFER, textureBuffer);

                const textureCoordinates = getTextureCoords();

                gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(textureCoordinates),
                  gl.STATIC_DRAW);

                this.buffer = [];
                for(var i=0;i<this.pos.length;i++) {
                this.buffer.push({
                position: this.positionBuffer[i],
                // color: colorBuffer,
                indices: indexBuffer,
                textureCoord:textureBuffer,
                });
                }
                this.texture = [];
                this.texture.push(loadTexture(gl, 'blue.png'));
                this.texture.push(loadTexture(gl, 'black.png'));
                this.texture.push(loadTexture(gl, 'skin.png'));
                this.texture.push(loadTexture(gl, 'skin.png'));
                this.texture.push(loadTexture(gl, 'blue.jpeg'));
                this.texture.push(loadTexture(gl, 'blue.jpeg'));

    }

    drawPolice(gl, projectionMatrix, programInfo, deltaTime) {

        this.positionCollCheck[2] -= this.vel;
        this.positionCollCheck[1] = player1.positionCollCheck[1];
        this.positionCollCheck[0] = player1.positionCollCheck[0];
        if(this.positionCollCheck[0]<-1) this.positionCollCheck[0] = -1;
        if(this.positionCollCheck[0]>1) this.positionCollCheck[0] = 1;
        while(this.pos.length > 0) {
          this.pos.pop();
        }
        // trains.length = 0;
        var temp = this.positionCollCheck;
        // console.log(this.positionCollCheck);
        this.pos.push([temp[0], temp[1]+0.5*this.bodyheight, temp[2]]);
        this.pos.push([temp[0], temp[1]+0.5*this.headheight+this.bodyheight, temp[2]]);
        this.pos.push([temp[0]-0.5*this.bodywidth-0.5*this.handwidth, temp[1]+0.5*this.bodyheight-0.01, temp[2]]);
        this.pos.push([temp[0]+0.5*this.bodywidth+0.5*this.handwidth, temp[1]+0.5*this.bodyheight-0.01, temp[2]]);
        this.pos.push([temp[0]-0.5*this.bodywidth+0.5*this.legwidth, temp[1]-0.5*this.legheight, temp[2]]);
        this.pos.push([temp[0]+0.5*this.bodywidth-0.5*this.legwidth, temp[1]-0.5*this.legheight, temp[2]]);

        for(var i=0;i<this.pos.length;i++) {
          if(i == 2 || i == 4) {
            if(this.rotationDirection[i] == 1) {
            this.rotation[i]+=10;
          }
          else if(this.rotationDirection[i] == -1) {
            this.rotation[i] -=10;
          }

          if(this.rotation[i]>=90) {
            this.rotationDirection[i] = -1;
          }
          else if(this.rotation[i]<=-90) {
            this.rotationDirection[i] = 1;
          }
        }
        else if(i == 3 || i == 5) {
            if(this.rotationDirection[i] == 1) {
            this.rotation[i]-=10;
          }
          else if(this.rotationDirection[i] == -1) {
            this.rotation[i] +=10;
          }

          if(this.rotation[i]>=90) {
            this.rotationDirection[i] = 1;
          }
          else if(this.rotation[i]<=-90) {
            this.rotationDirection[i] = -1;
          }
        }
          const modelViewMatrix = mat4.create();


        mat4.translate (
              modelViewMatrix,
              modelViewMatrix,
              this.pos[i],
          );

          //this.rotation += Math.PI / (((Math.random()) % 100) + 50);
          mat4.translate (
                modelViewMatrix,
                modelViewMatrix,
                [0,0.5*this.handheight,0],
            );
            if(!player1.flyPowerupTaken) {
          mat4.rotate(modelViewMatrix,
              modelViewMatrix,
              this.rotation[i]*Math.PI/180,
              [1, 0, 0],);
            }
            else {
              mat4.rotate(modelViewMatrix,
                  modelViewMatrix,
                  0*Math.PI/180,
                  [1, 0, 0],);
            }
          mat4.translate (
                modelViewMatrix,
                modelViewMatrix,
                [0,-0.5*this.handheight,0],
            );

          {
              const numComponents = 3;
              const type = gl.FLOAT;
              const normalize = false;
              const stride = 0;
              const offset = 0;
              gl.bindBuffer(gl.ARRAY_BUFFER, this.buffer[i].position);
              gl.vertexAttribPointer(
                  programInfo.attribLocations.vertexPosition,
                  numComponents,
                  type,
                  normalize,
                  stride,
                  offset);
              gl.enableVertexAttribArray(
                  programInfo.attribLocations.vertexPosition);
          }
          {
              const num = 2; // every coordinate composed of 2 values
              const type = gl.FLOAT; // the data in the buffer is 32 bit float
              const normalize = false; // don't normalize
              const stride = 0; // how many bytes to get from one set to the next
              const offset = 0; // how many bytes inside the buffer to start from
              gl.bindBuffer(gl.ARRAY_BUFFER, this.buffer[i].textureCoord);
              gl.vertexAttribPointer(programInfo.attribLocations.textureCoord, num, type, normalize, stride, offset);
              gl.enableVertexAttribArray(programInfo.attribLocations.textureCoord);
          }
          // Tell WebGL how to pull out the colors from the color buffer
          // into the vertexColor attribute.
          // {
          //     const numComponents = 4;
          //     const type = gl.FLOAT;
          //     const normalize = false;
          //     const stride = 0;
          //     const offset = 0;
          //     gl.bindBuffer(gl.ARRAY_BUFFER, this.buffer.color);
          //     gl.vertexAttribPointer(
          //         programInfo.attribLocations.vertexColor,
          //         numComponents,
          //         type,
          //         normalize,
          //         stride,
          //         offset);
          //     gl.enableVertexAttribArray(
          //         programInfo.attribLocations.vertexColor);
          // }

          // Tell WebGL which indices to use to index the vertices
          gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, this.buffer[i].indices);

          // Tell WebGL to use our program when drawing

          gl.useProgram(programInfo.program);

          // Set the shader uniforms

          gl.uniformMatrix4fv(
              programInfo.uniformLocations.projectionMatrix,
              false,
              projectionMatrix);
          gl.uniformMatrix4fv(
              programInfo.uniformLocations.modelViewMatrix,
              false,
              modelViewMatrix);

            gl.activeTexture(gl.TEXTURE0);

            // Bind the texture to texture unit 0
            gl.bindTexture(gl.TEXTURE_2D, this.texture[i]);

            // Tell the shader we bound the texture to texture unit 0
            gl.uniform1i(programInfo.uniformLocations.uSampler, 0);

          {
              const vertexCount = 36;
              const type = gl.UNSIGNED_SHORT;
              const offset = 0;
              gl.drawElements(gl.TRIANGLES, vertexCount, type, offset);
          }
        }
      }

};
