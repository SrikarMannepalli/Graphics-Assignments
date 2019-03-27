let Powerups = class {
    constructor(gl, dim, pos, type) {
        this.positionBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, this.positionBuffer);

        this.width = 2*dim[0];
        this.height = 2*dim[1];
        this.depth = 2*dim[0];
        this.destroyed  = false;
        this.type = type;//1- coins, -2 - jumping boots,3 - fly over obstacles.
        this.positions = getCylinder(dim[0],dim[1],dim[2]);


        this.rotation = 0;
        this.pos = pos;


        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(this.positions), gl.STATIC_DRAW);
        var colors = [];



          for (var j = 0; j < 120; ++j) {
            if(type == 1) {
              var c = [1.0, 215.0/255.0, 0.0, 1.0];
            }
            else if (type == 2) {
                var c = [1.0, 0.0, 0.0, 1.0];
            }
            else if(type == 3) {
              var c = [0.0, 0.0, 1.0, 1.0];
            }



              // Repeat each color four times for the four vertices of the face
              colors = colors.concat(c, c, c);
          }

          const colorBuffer = gl.createBuffer();
          gl.bindBuffer(gl.ARRAY_BUFFER, colorBuffer);
          gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(colors), gl.STATIC_DRAW);

          // Build the element array buffer; this specifies the indices
          // into the vertex arrays for each face's vertices.

          const indexBuffer = gl.createBuffer();
          gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, indexBuffer);

          // This array defines each face as two triangles, using the
          // indices into the vertex array to specify each triangle's
          // position.
          var indices = getCylinderIndices();

          // Now send the element array to GL

          gl.bufferData(gl.ELEMENT_ARRAY_BUFFER,
              new Uint16Array(indices), gl.STATIC_DRAW);

          this.buffer = {
              position: this.positionBuffer,
              color: colorBuffer,
              indices: indexBuffer,
          };
        // this.texture = loadTexture(gl, pic)
    }

    drawPowerups(gl, projectionMatrix, programInfo, deltaTime) {
      const modelViewMatrix = mat4.create();
       this.rotation += 0.05
       mat4.translate(
           modelViewMatrix,
           modelViewMatrix,
           this.pos
       );

       //this.rotation += Math.PI / (((Math.random()) % 100) + 50);

       mat4.rotate(modelViewMatrix,
           modelViewMatrix,
           this.rotation,
           [0, 1, 0]);

       {
           const numComponents = 3;
           const type = gl.FLOAT;
           const normalize = false;
           const stride = 0;
           const offset = 0;
           gl.bindBuffer(gl.ARRAY_BUFFER, this.buffer.position);
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

       // Tell WebGL how to pull out the colors from the color buffer
       // into the vertexColor attribute.
       {
           const numComponents = 4;
           const type = gl.FLOAT;
           const normalize = false;
           const stride = 0;
           const offset = 0;
           gl.bindBuffer(gl.ARRAY_BUFFER, this.buffer.color);
           gl.vertexAttribPointer(
               programInfo.attribLocations.vertexColor,
               numComponents,
               type,
               normalize,
               stride,
               offset);
           gl.enableVertexAttribArray(
               programInfo.attribLocations.vertexColor);
       }

       // Tell WebGL which indices to use to index the vertices
       gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, this.buffer.indices);

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

       {
           const vertexCount = 120*18*0+60;
           const type = gl.UNSIGNED_SHORT;
           const offset = 0;
           gl.drawElements(gl.TRIANGLES, vertexCount, type, offset);
       }

   }
};
