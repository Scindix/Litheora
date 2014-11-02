#version 330

layout (std140) uniform Transformation
{
    mat4 view;
    mat4 model;
    mat4 projection;
    vec3 camera;
};

in vec3 Position;
in vec3 TexCoord;

out Data
{
    vec3 position;
    vec3 texCoord;
} DataOut;

void main ()
{
    DataOut.position = Position;
    DataOut.texCoord = TexCoord;

    gl_Position = projection * view * vec4((50.0 * Position)+camera, 1.0);
}
