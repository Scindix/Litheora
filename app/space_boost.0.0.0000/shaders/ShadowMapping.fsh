#version 330

layout (location = 0) out vec4 outputF;

in Data
{
    vec3 position;
    vec3 texCoord;
} DataIn;

void main()
{
    float maxDistance = 50.0;
    outputF = vec4(vec3(length(DataIn.position)/maxDistance), 1.0);
}
