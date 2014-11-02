#version 330

layout (location = 0) out vec4 outputF;

in Data {
    vec2 texCoord;
    vec2 blurTexCoord[14];
} DataIn;

uniform sampler2D diffuseTex;
uniform sampler2D normalTex;
uniform sampler2D specularTex;
uniform float depth;

void main()
{
    float wc = 1.0/1366;
    float hc = 1.0/750;
    float dist = 0.5;
    vec4 texColor = texture(diffuseTex, DataIn.texCoord);
    vec4 texDepth = vec4(1.0)-texture(specularTex, DataIn.texCoord);
    float depthFromShader = (vec4(1.0)-texture(specularTex, vec2(0.5, 0.5))).r;
    float weight = 1.0-abs(texDepth.r-depthFromShader)*1.0;
    //weight = min(max(1.0-abs(1.0-(texDepth.rgb-depthFromShader)*20.0), 0.0), 1.0);
    float sharpness = 0.7;
    vec4 Color  = texture(diffuseTex, sharpness*DataIn.texCoord + (1.0-sharpness)*DataIn.blurTexCoord[ 0])*0.0044299121055113265
                + texture(diffuseTex, sharpness*DataIn.texCoord + (1.0-sharpness)*DataIn.blurTexCoord[ 1])*0.00895781211794
                + texture(diffuseTex, sharpness*DataIn.texCoord + (1.0-sharpness)*DataIn.blurTexCoord[ 2])*0.0215963866053
                + texture(diffuseTex, sharpness*DataIn.texCoord + (1.0-sharpness)*DataIn.blurTexCoord[ 3])*0.0443683338718
                + texture(diffuseTex, sharpness*DataIn.texCoord + (1.0-sharpness)*DataIn.blurTexCoord[ 4])*0.0776744219933
                + texture(diffuseTex, sharpness*DataIn.texCoord + (1.0-sharpness)*DataIn.blurTexCoord[ 5])*0.115876621105
                + texture(diffuseTex, sharpness*DataIn.texCoord + (1.0-sharpness)*DataIn.blurTexCoord[ 6])*0.147308056121
                + texture(diffuseTex, DataIn.texCoord        )*0.159576912161
                + texture(diffuseTex, sharpness*DataIn.texCoord + (1.0-sharpness)*DataIn.blurTexCoord[ 7])*0.147308056121
                + texture(diffuseTex, sharpness*DataIn.texCoord + (1.0-sharpness)*DataIn.blurTexCoord[ 8])*0.115876621105
                + texture(diffuseTex, sharpness*DataIn.texCoord + (1.0-sharpness)*DataIn.blurTexCoord[ 9])*0.0776744219933
                + texture(diffuseTex, sharpness*DataIn.texCoord + (1.0-sharpness)*DataIn.blurTexCoord[10])*0.0443683338718
                + texture(diffuseTex, sharpness*DataIn.texCoord + (1.0-sharpness)*DataIn.blurTexCoord[11])*0.0215963866053
                + texture(diffuseTex, sharpness*DataIn.texCoord + (1.0-sharpness)*DataIn.blurTexCoord[12])*0.00895781211794
                + texture(diffuseTex, sharpness*DataIn.texCoord + (1.0-sharpness)*DataIn.blurTexCoord[13])*0.0044299121055113265;

    //float weight = min(1.0, (1.0-abs(texDepth.r-0.01))*20);
    ///outputF = vec4(weight*texColor.rgb + (1.0-weight)*Color.rgb, 1.0);
    ///outputF = vec4(weight*vec3(1.0),1.0);
    outputF = vec4(pow(Color.rgb*3.0, vec3(2.0)),1.0);
    ///outputF = vec4(abs(texDepth.r-depthFromShader)*vec3(10.0), 1.0);
}
