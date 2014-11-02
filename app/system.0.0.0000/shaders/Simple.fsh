#version 330

out vec4[2] colorAt;

uniform vec4 diffuse;
uniform vec4 ambient;
uniform vec4 specular;
uniform vec4 shininess;
uniform vec4 midPoint;
uniform int useTex;

in Data {
    vec3 normal;
    vec3 eye;
    vec3 position;
    vec3 lightDir;
    vec3 texCoord;
    vec3 tangent;
} DataIn;

uniform sampler2D diffuseTex;
uniform sampler2D normalTex;
uniform sampler2D specularTex;
uniform samplerCube environmentTex;
uniform samplerCube shadowTex;

vec2 raytrace(in vec3 eye, in vec2 texCoord, in sampler2D text)
{
    if(abs(dot(eye, vec3(0.0, 0.0, 1.0))) < 0.1)
    {
        return vec2(0.0);
    }
    return vec2(0.0);

    float maxheight = 0.05* sqrt(abs(dot(eye, vec3(0.0, 0.0, 1.0))));
    float increment = -0.005;
    float param = 0.0;
    vec3 testVec = vec3(0.0);
    for(int i = 0; i < 200; i++)
    {
        testVec = param*(eye);
        float height = texture(normalTex, texCoord + testVec.xy).a;
        if(abs(testVec.z) > height*maxheight)
        {
            param -= increment;
            increment /= 50.0;
            for(int i = 0; i < 200; i++)
            {
                testVec = param*(eye);
                float height = texture(normalTex, texCoord + testVec.xy).a;
                if(abs(testVec.z) > height*maxheight)
                {
                    return testVec.xy;
                }
                param += increment;
            }
            return testVec.xy;
        }
        param += increment;
    }
    return vec2(0.0);
}

void main()
{
    vec4 spec = vec4(0.0);
    vec2 texCoord = DataIn.texCoord.xy;
    vec3 n;
    vec2 displacement;

        mat3 normal2view;
        normal2view[0] = normalize(DataIn.tangent);
        normal2view[1] = normalize(cross(DataIn.normal, DataIn.tangent));
        normal2view[2] = normalize(DataIn.normal);
        mat3 view2normal = inverse(normal2view);

    vec3 l = normalize(DataIn.lightDir);
    vec3 e = normalize(DataIn.eye);

    if((useTex & 4)==0)
        n = normalize(DataIn.normal);
    else
    {

        //float height = texture(normalTex, texCoord).a;
        //vec3 displacement = view2normal * (DataIn.eye - DataIn.position);
        //displacement *= height/displacement.z;
        displacement = raytrace(normalize(view2normal * (DataIn.eye - DataIn.position)), texCoord, normalTex);
        texCoord += displacement;

        vec2 texNormal = -2*texture(normalTex, texCoord).xy+vec2(1.0);
        n = normalize(normal2view*vec3(texNormal, 1.0));
    }

    float maxDistance = 50.0;
    float lightDepth = texture(shadowTex, -DataIn.lightDir).r*maxDistance;
    float dist2light = length(DataIn.lightDir);
    float shadow = 1.0-max(dist2light-lightDepth, 0.0);
    if(shadow > 0.8)
        shadow = 1.0;
    else
        shadow = 0.0;
    float attenuation = 50.0*(1.0/pow(dist2light, 2));

    float intensity = max(dot(n,l), 0.0)*shadow;

    if (intensity > 0.0) {
        float intSpec = max(dot(normalize(e+l), n), 0.0);
        spec = specular * pow(intSpec, shininess.r*10);
    }

    vec4 texColor = texture(diffuseTex, texCoord);
    float texSpec = texture(specularTex, texCoord).r;
    if((useTex & 1)==0)
        texColor = vec4(1.0);
    if((useTex & 2)==0)
        texSpec = vec4(1.0);

    vec3 reflectionVec = -reflect(DataIn.eye - DataIn.position, n);
    vec4 envColor = texture(environmentTex, reflectionVec);//DataIn.position-midPoint.xyz);
    vec3 reflectionCol = vec3(0.0);
    vec3 outCol = vec3(intensity *  diffuse * texColor*attenuation*(1.0-spec) + spec*texSpec*attenuation + ambient * diffuse * texColor);

    if(shininess.r > 99.0)
    {
        float fresnel = 0.9-dot(n,normalize(DataIn.eye - DataIn.position))*0.8;
        reflectionCol = envColor.rgb*(fresnel)*texSpec;
        colorAt[0] = vec4(reflectionCol + spec.rgb*texSpec*attenuation + ambient.rgb * diffuse.rgb * texColor.rgb * (1.0-fresnel), texColor.a);
        if(length(ambient.rgb) > 0.8)
            colorAt[1] = vec4((ambient * diffuse).rgb, texColor.a);
        else
            colorAt[1] = vec4(0, 0, 0, texColor.a);
        ///colorAt0 = vec4(-reflectionVec, 1.0);
    } else
    {
        colorAt[0] = vec4(outCol, texColor.a);
        if(length(ambient.rgb) > 0.8)
            colorAt[1] = vec4((ambient * diffuse).rgb, texColor.a);
        else
            colorAt[1] = vec4(0, 0, 0, texColor.a);
    }
    ///colorAt0 = vec4(DataIn.tangent, 1.0);
}
