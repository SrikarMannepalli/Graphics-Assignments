let Score = class {
    constructor(gl, digit, pos) {
      console.log(digit);
        this.width = 0.1;
        this.height = 0.1;
        this.depth = 0.01;
        this.positionCollCheck = pos;
        this.pos = [];
        this.positions = [];
        var temp = pos;
        // console.log(pos);
        this.positions.push(getCube(0.01,this.width,this.depth));//top
        this.pos.push([temp[0], temp[1]+this.height,temp[2]]);
        // this.positions.push(getCube(0.01,this.width,this.depth));//middle
        // this.pos.push([temp[0], temp[1],temp[2]]);
        // this.positions.push(getCube(0.01,this.width,this.depth));//bottom
        // this.pos.push([temp[0], temp[1]-this.height,temp[2]]);
        // this.positions.push(getCube(this.height,0.01,this.depth));//rightup
        // this.pos.push([temp[0]+0.5*this.width, temp[1]+0.5*this.height,temp[2]]);
        // this.positions.push(getCube(this.height,0.01,this.depth));//rightdown
        // this.pos.push([temp[0]+0.5*this.width, temp[1]-0.5*this.height,temp[2]]);
        // this.positions.push(getCube(this.height,0.01,this.depth));//leftup
        // this.pos.push([temp[0]-0.5*this.width, temp[1]+0.5*this.height,temp[2]]);
        // this.positions.push(getCube(this.height,0.01,this.depth));//leftdown
        // this.pos.push([temp[0]-0.5*this.width, temp[1]-0.5*this.height,temp[2]]);

        this.positionBuffer = [];
        for (var i = 0; i < this.pos.length; i++) {
            this.positionBuffer.push(gl.createBuffer());
            gl.bindBuffer(gl.ARRAY_BUFFER, this.positionBuffer[i]);
            gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(this.positions[i]), gl.STATIC_DRAW);
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
        for (var i = 0; i < this.pos.length; i++) {
            this.buffer.push({
                position: this.positionBuffer[i],
                // color: colorBuffer,
                indices: indexBuffer,
                textureCoord: textureBuffer,
            });
        }
        this.texture = [];
        this.texture.push(loadTexture(gl, 'red.png'));
        this.texture.push(loadTexture(gl, 'red.png'));
        this.texture.push(loadTexture(gl, 'red.png'));
        this.texture.push(loadTexture(gl, 'red.png'));
        this.texture.push(loadTexture(gl, 'red.png'));
        this.texture.push(loadTexture(gl, 'red.png'));
        this.texture.push(loadTexture(gl, 'red.png'));

    }

    drawScore(gl, projectionMatrix, programInfo, deltaTime) {
        for (var i = 0; i < this.pos.length; i++) {
            const modelViewMatrix = mat4.create();
            mat4.translate(
                modelViewMatrix,
                modelViewMatrix,
                this.pos[i],
            );


            mat4.rotate(modelViewMatrix,
                modelViewMatrix,
                0 * Math.PI / 180,
                [1, 0, 0]);



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
