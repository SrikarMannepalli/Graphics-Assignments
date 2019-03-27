/// <reference path="webgl.d.ts" />

let Tunnel = class {
    constructor(gl, trackFree, pos) {
        this.positions = [];
        this.pos = [];
        this.positionCollCheck = [];
        this.positionCollCheck.push(pos[0]);
        this.positionCollCheck.push(pos[1]);
        this.positionCollCheck.push(pos[2]);
        var temp = pos;
        this.width = 3;
        this.height = 1.7;
        this.depth = 0.2;
        this.trackFree = trackFree;
        this.positions.push(getCube(this.width, this.height, this.depth));
        this.pos.push([temp[0], temp[1]+0.96, temp[2]]);
        if(trackFree!=1) {
          this.positions.push(getCube(this.width/3, 1.0, this.depth));
          this.pos.push([temp[0]-1, temp[1]-0.4, temp[2]]);
        }
        if(trackFree!=2) {
          this.positions.push(getCube(this.width/3, 1.0, this.depth));
          this.pos.push([temp[0], temp[1]-0.4, temp[2]]);
        }
        if(trackFree!=3) {
          this.positions.push(getCube(this.width/3, 1.0, this.depth));
          this.pos.push([temp[0]+1, temp[1]-0.4, temp[2]]);
        }
        this.rotation = 0;
        this.positionBuffer= [];
        for(var i=0;i<this.pos.length;i++) {
        this.positionBuffer.push(gl.createBuffer());
        gl.bindBuffer(gl.ARRAY_BUFFER, this.positionBuffer[i]);
        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(this.positions[i]), gl.STATIC_DRAW);
      }
        var colors = [];

     // for (var j = 0; j < 6; ++j) {
     //     const c = [100.0/255.0, 149.0/255.0, 237.0/255.0, 1.0];
     //
     //     // Repeat each color four times for the four vertices of the face
     //     colors = colors.concat(c, c, c, c);
     // }
     //
     // const colorBuffer = gl.createBuffer();
     // gl.bindBuffer(gl.ARRAY_BUFFER, colorBuffer);
     // gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(colors), gl.STATIC_DRAW);

        const indexBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, indexBuffer);

        // This array defines each face as two triangles, using the
        // indices into the vertex array to specify each triangle's
        // position.

        const indices = getIndicesCuboids();

        // Now send the element array to GL

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
            textureCoord: textureBuffer,
            indices: indexBuffer,
            // color: colorBuffer,
        });
      }
      this.texture = [];
      this.texture.push(loadTexture(gl, 'wall.jpg'));
      this.texture.push(loadTexture(gl, 'wall.jpg'));
      this.texture.push(loadTexture(gl, 'wall.jpg'));
    }
    drawTunnel(gl, projectionMatrix, programInfo, deltaTime) {
      this.rotation = Math.PI;

      for(var i=0;i<this.pos.length;i++) {
        const modelViewMatrix = mat4.create();
        mat4.translate(
            modelViewMatrix,
            modelViewMatrix,
            this.pos[i],
        );

        //this.rotation += Math.PI / (((Math.random()) % 100) + 50);

        mat4.rotate(modelViewMatrix,
            modelViewMatrix,
            this.rotation,
            [0, 0, -1]);

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
        // Tell WebGL how to pull out the colors from the color buffer
        // into the vertexColor attribute.
        // tell webgl how to pull out the texture coordinates from buffer
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


            // Tell WebGL we want to affect texture unit 0
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
