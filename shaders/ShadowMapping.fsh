#version 330

layout (location = 0) out vec4 outputF;

in Data
{
    vec3 position;
    vec3 texCoord;
} DataIn;

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


void main()
{
    vec3 sp = getSphere(DataIn.position);
    vec3 offsetCartesian0 = getCartChangeByTheta(sp.x, sp.y, sp.z, 0.001);
    //vec3 offsetCartesian1 = getCartChangeByPhi(sp.x, sp.y, sp.z, 0.001);
    outputF = vec4(length(DataIn.position), offsetCartesian0);
}
