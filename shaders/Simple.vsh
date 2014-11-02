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
in vec3 Normal;
in vec3 Tangent;

struct LightParam
{
    vec4 diffuse;
    vec4 position;
    vec4 direction;
    int flags;
    float distance;
};

layout (std140) uniform Lights
{
    LightParam light1;
    LightParam light2;
};

out Data
{
    vec3 normal;
    vec3 eye;
    vec3 position;
    vec3 lightDir;
    vec3 texCoord;
    vec3 tangent;
} DataOut;

void main ()
{
    DataOut.normal = normalize(Normal);
    DataOut.lightDir = (vec3(2.0, 3.0, 5.5) - Position);
    DataOut.eye = camera;
    DataOut.texCoord = TexCoord*10;
    DataOut.tangent = Tangent;
    DataOut.position = Position;

    gl_Position = projection * view * vec4(Position, 1.0);
}
