#version 330

layout (location = 0) out vec4 outputF;

in Data {
    vec2 texCoord;
    vec2 blurTexCoord[14];
} DataIn;

uniform sampler2D diffuseTex;
uniform sampler2D normalTex;
uniform sampler2D specularTex;

void main()
{
    float wc = 0.5/1366;
    float hc = 0.5/750;
    float dist = 0.5;
    vec4 texColor = texture(diffuseTex, DataIn.texCoord);

    vec4 Color  = texture(diffuseTex, DataIn.blurTexCoord[ 0])*0.0044299121055113265
                + texture(diffuseTex, DataIn.blurTexCoord[ 1])*0.00895781211794
                + texture(diffuseTex, DataIn.blurTexCoord[ 2])*0.0215963866053
                + texture(diffuseTex, DataIn.blurTexCoord[ 3])*0.0443683338718
                + texture(diffuseTex, DataIn.blurTexCoord[ 4])*0.0776744219933
                + texture(diffuseTex, DataIn.blurTexCoord[ 5])*0.115876621105
                + texture(diffuseTex, DataIn.blurTexCoord[ 6])*0.147308056121
                + texture(diffuseTex, DataIn.texCoord        )*0.159576912161
                + texture(diffuseTex, DataIn.blurTexCoord[ 7])*0.147308056121
                + texture(diffuseTex, DataIn.blurTexCoord[ 8])*0.115876621105
                + texture(diffuseTex, DataIn.blurTexCoord[ 9])*0.0776744219933
                + texture(diffuseTex, DataIn.blurTexCoord[10])*0.0443683338718
                + texture(diffuseTex, DataIn.blurTexCoord[11])*0.0215963866053
                + texture(diffuseTex, DataIn.blurTexCoord[12])*0.00895781211794
                + texture(diffuseTex, DataIn.blurTexCoord[13])*0.0044299121055113265;

    vec4 texDepth = vec4(1.0)-texture(specularTex, DataIn.texCoord);
    //float weight = min(1.0, (1.0-abs(texDepth.r-0.01))*20);
    float weight = abs(texDepth.r*10.0-0.4); weight =1.0;
    outputF = vec4((1.0-weight)*texColor.rgb + weight*Color.rgb, 1.0);
    //outputF = vec4((texture(diffuseTex, DataIn.blurTexCoord[ 7]        )).rgb,1.0);
    //outputF = vec4(Color.rgb, 1.0);
}
