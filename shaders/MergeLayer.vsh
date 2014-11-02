#version 330

in vec3 TexCoord;
in vec3 Position;
in vec3 Normal;
in vec3 Tangent;

uniform bool axis;

out Data {
    vec2 texCoord;
} DataOut;

void main () {
    DataOut.texCoord = TexCoord.xy;
    gl_Position = vec4(Position.xy, 0.5, 1.0);
}
