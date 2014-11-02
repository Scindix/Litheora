#version 330

out vec4[2] colorAt;

uniform vec4 diffuse;
uniform vec4 emission;
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



mat3 getJacobian(float r, float theta, float phi)
{
    return mat3(   sin(theta)*cos(phi),   sin(theta)*sin(phi),    cos(theta),
                 r*cos(theta)*cos(phi), r*cos(theta)*sin(phi), -r*sin(theta),
                -r*sin(theta)*sin(phi), r*sin(theta)*cos(phi),            0);
}

mat3 getJacobianByCartesian(vec3 v)
{
    float r = length(v);
    float theta = acos(v.z/r);
    float phi = atan(v.y, v.x);
    return getJacobian(r, theta, phi);
}

vec3 getCartChangeByTheta(float r, float theta, float phi, float deltaTheta)
{
    return deltaTheta*vec3(r*cos(theta)*cos(phi), r*cos(theta)*sin(phi), -r*sin(theta));
}

vec3 getCartChangeByPhi(float r, float theta, float phi, float deltaPhi)
{
    return vec3(-deltaPhi*r*sin(theta)*sin(phi), deltaPhi*r*sin(theta)*cos(phi), 0);
}

vec3 getSphere(vec3 v)
{
    float r = length(v);
    return vec3(r, acos(v.z/r), atan(v.y, v.x));
}

float getShadow(vec2 offset)
{
    vec3 sp = getSphere(-DataIn.lightDir);

    float lightDepth = texture(shadowTex, -DataIn.lightDir).r;
    vec3 offsetCartesian0 = texture(shadowTex, -DataIn.lightDir).gba;
    vec3 offsetCartesian1 = cross(offsetCartesian0, normalize(DataIn.lightDir));

    float lightDepth1 = texture(shadowTex, -DataIn.lightDir + offsetCartesian0).r;
    float lightDepth2 = texture(shadowTex, -DataIn.lightDir + offsetCartesian1).r;
    float lightDepth3 = texture(shadowTex, -DataIn.lightDir - offsetCartesian0).r;
    float lightDepth4 = texture(shadowTex, -DataIn.lightDir - offsetCartesian1).r;
    float dist2light = length(DataIn.lightDir);
    float shadow0 = 1.0-max(dist2light-lightDepth, 0.0);
    float shadow1 = 1.0-max(dist2light-lightDepth1, 0.0);
    float shadow2 = 1.0-max(dist2light-lightDepth2, 0.0);
    float shadow3 = 1.0-max(dist2light-lightDepth3, 0.0);
    float shadow4 = 1.0-max(dist2light-lightDepth4, 0.0);
    if(shadow0 > 0.97)
        shadow0 = 1.0;
    else
        shadow0 = 0.0;

    if(shadow1 > 0.97)
        shadow1 = 1.0;
    else
        shadow1 = 0.0;

    if(shadow2 > 0.97)
        shadow2 = 1.0;
    else
        shadow2 = 0.0;

    if(shadow3 > 0.97)
        shadow3 = 1.0;
    else
        shadow3 = 0.0;

    if(shadow4 > 0.97)
        shadow4 = 1.0;
    else
        shadow4 = 0.0;
    return (shadow0 + shadow1 + shadow2 + shadow3 + shadow4)/5;
}

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

    float dist2light = length(DataIn.lightDir);
    /*float lightDepth = texture(shadowTex, -DataIn.lightDir).r;
    float shadow = 1.0-max(dist2light-lightDepth, 0.0);
    if(shadow > 0.97)
        shadow = 1.0;
    else
        shadow = 0.0;*/

    float shadow = getShadow(vec2(0.001, 0.001));

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
        texSpec = float(1.0);

    vec3 reflectionVec = -reflect(DataIn.eye - DataIn.position, n);
    vec4 envColor = texture(environmentTex, reflectionVec);//DataIn.position-midPoint.xyz);
    vec3 reflectionCol = vec3(0.0);
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
    vec4 outCol = vec4(intensity *  diffuse.rgb * texColor.rgb*attenuation + spec.rgb*texSpec*attenuation + emission.rgb * diffuse.rgb + ambient.rgb * diffuse.rgb * texColor.rgb, texColor.a * diffuse.a);

    if(shininess.r > 99.0)
    {
        float fresnel = 1.0-dot(n,normalize(DataIn.eye - DataIn.position));
        reflectionCol = envColor.rgb*(fresnel)*texSpec;
        colorAt[0] = vec4(reflectionCol + spec.rgb*texSpec*attenuation + emission.rgb * diffuse.rgb + ambient.rgb * diffuse.rgb * texColor.rgb * (1.0-fresnel), texColor.a * diffuse.a);
        if(length(emission.rgb) > 0.1)
            colorAt[1] = vec4((emission * diffuse).rgb, texColor.a);
        else
            colorAt[1] = vec4(0, 0, 0, texColor.a);
        ///colorAt0 = vec4(-reflectionVec, 1.0);
    } else
    {
        colorAt[0] = vec4(outCol);
        if(length(emission.rgb) > 0.1)
            colorAt[1] = vec4((emission * diffuse).rgb, texColor.a * diffuse.a);
        else
            colorAt[1] = vec4(0, 0, 0, texColor.a);
    }
    ///colorAt0 = vec4(DataIn.tangent, 1.0);
}
