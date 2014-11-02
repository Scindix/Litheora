#version 330

in vec3 TexCoord;
in vec3 Position;
in vec3 Normal;
in vec3 Tangent;

uniform bool axis;

out Data {
    vec2 texCoord;
    vec2 blurTexCoord[14];
} DataOut;

void main () {
    vec2 offsetX = vec2(0.01, 0);
    vec2 offsetY = vec2(0, 0.01);
    vec2 offset;
    if(axis)
        offset = offsetY;
    else
        offset = offsetX;
    DataOut.texCoord = TexCoord.xy;
    DataOut.blurTexCoord[ 0] = DataOut.texCoord + offset*-7.0;
    DataOut.blurTexCoord[ 1] = DataOut.texCoord + offset*-6.0;
    DataOut.blurTexCoord[ 2] = DataOut.texCoord + offset*-5.0;
    DataOut.blurTexCoord[ 3] = DataOut.texCoord + offset*-4.0;
    DataOut.blurTexCoord[ 4] = DataOut.texCoord + offset*-3.0;
    DataOut.blurTexCoord[ 5] = DataOut.texCoord + offset*-2.0;
    DataOut.blurTexCoord[ 6] = DataOut.texCoord + offset*-1.0;
    DataOut.blurTexCoord[ 7] = DataOut.texCoord + offset* 1.0;
    DataOut.blurTexCoord[ 8] = DataOut.texCoord + offset* 2.0;
    DataOut.blurTexCoord[ 9] = DataOut.texCoord + offset* 3.0;
    DataOut.blurTexCoord[10] = DataOut.texCoord + offset* 4.0;
    DataOut.blurTexCoord[11] = DataOut.texCoord + offset* 5.0;
    DataOut.blurTexCoord[12] = DataOut.texCoord + offset* 6.0;
    DataOut.blurTexCoord[13] = DataOut.texCoord + offset* 7.0;
    gl_Position = vec4(Position.xy, 0.5, 1.0);
}
