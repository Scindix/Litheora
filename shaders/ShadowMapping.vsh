#version 330

layout (std140) uniform Transformation
{
    mat4 view;
    mat4 model;
    mat4 projection;
    vec3 camera;
};

in vec3 TexCoord;
in vec3 Position;

out Data
{
    vec3 position;
    vec3 texCoord;
} DataOut;

void main ()
{
    DataOut.texCoord = TexCoord;
    DataOut.position = Position - camera;
    gl_Position = projection * view * vec4(Position, 1.0);
}
