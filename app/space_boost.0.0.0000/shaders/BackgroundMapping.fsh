#version 330

out vec4 colorAt[2];
uniform int useTex;

in Data {
    vec3 position;
    vec3 texCoord;
} DataIn;

uniform sampler2D environmentTex;
uniform sampler2D diffuseTex;
uniform sampler2D normalTex;
uniform sampler2D specularTex;

void main()
{
    //if(sign(DataIn.position.y) == -1.0)
        //colorAt[0] = vec4(0.0, 0.0, 0.8, 1.0);
    //else
        //colorAt[0] = vec4(pow(abs(1.0-DataIn.position.y), 100.0)*vec3(0.0, 0.2, 0.0)+vec3(0.0,0.2,1.0), 1.0);
    colorAt[0] = texture(environmentTex, DataIn.texCoord.xy);
    ///colorAt[0] = vec4(1.0);
    colorAt[1] = vec4(0.0, 0.0, 0.0, 1.0);
}
