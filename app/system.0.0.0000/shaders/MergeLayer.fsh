#version 330

layout (location = 0) out vec4 outputF;

in Data {
    vec2 texCoord;
} DataIn;

uniform sampler2D diffuseTex;
uniform sampler2D normalTex;
uniform sampler2D specularTex;
uniform sampler2D environmentTex;

void main()
{
    outputF = vec4(texture(diffuseTex, DataIn.texCoord)+texture(specularTex, DataIn.texCoord));
}
