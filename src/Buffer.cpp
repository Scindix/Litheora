#include "Buffer.h"



int printOglError(char *file, int line)
{

    GLenum glErr;
    int    retCode = 0;

    glErr = glGetError();
    if (glErr != GL_NO_ERROR)
    {
        printf("glError in file %s @ line %d [%d]: %s\n",
			     file, line, (int)glErr, gluErrorString(glErr));
        retCode = 1;
    }
    return retCode;
}
Buffer::Buffer(Shader* sh)
{
    shader = sh;
}

Buffer::~Buffer()
{
    ///glDeleteProgram(Program);
    glDeleteBuffers(BufferSize, BufferName);
}

void Buffer::render(bool filterEmissive)
{
    render(shader, filterEmissive);
}
Buffer& Buffer::operator<<(Mesh* m)
{
    groupID = m->groupID;
    texCoordSize = m->texCoord.size() * sizeof(std::vector<Vector>::value_type);
    positionSize = m->vertex.size() * sizeof(std::vector<Vector>::value_type);
    normalSize = m->normal.size() * sizeof(std::vector<Vector>::value_type);

    vertexCount = m->vertex.size();

    std::vector<Vector> tangents;

    computeTangentBasis(m->vertex, m->texCoord, m->normal, tangents);

    texCoordData = (GLubyte*)m->texCoord.data();
    positionData = (GLfloat*)m->vertex.data();
    normalData = (GLfloat*)m->normal.data();
    tangentData = (GLfloat*)tangents.data();
    AttributIndex[TEXCOORD_OBJECT] = shader->attribute("TexCoord");
    AttributIndex[POSITION_OBJECT] = shader->attribute("Position");
    AttributIndex[NORMAL_OBJECT] = shader->attribute("Normal");
    AttributIndex[TANGENT_OBJECT] = shader->attribute("Tangent");

    glGenBuffers(BufferSize, BufferName);

    glBindBuffer(GL_ARRAY_BUFFER, BufferName[TEXCOORD_OBJECT]);
    glBufferData(GL_ARRAY_BUFFER, texCoordSize, texCoordData, GL_STREAM_DRAW);
    glVertexAttribPointer(AttributIndex[TEXCOORD_OBJECT], 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, BufferName[POSITION_OBJECT]);
    glBufferData(GL_ARRAY_BUFFER, positionSize, positionData, GL_STREAM_DRAW);
    glVertexAttribPointer(AttributIndex[POSITION_OBJECT], 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, BufferName[NORMAL_OBJECT]);
    glBufferData(GL_ARRAY_BUFFER, normalSize, normalData, GL_STREAM_DRAW);
    glVertexAttribPointer(AttributIndex[NORMAL_OBJECT], 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, BufferName[TANGENT_OBJECT]);
    glBufferData(GL_ARRAY_BUFFER, normalSize, tangentData, GL_STREAM_DRAW);
    glVertexAttribPointer(AttributIndex[TANGENT_OBJECT], 3, GL_FLOAT, GL_FALSE, 0, 0);



    material = new Material(
    {
        {
            m->diffuse[0], m->diffuse[1], m->diffuse[2], m->diffuse[3]
        },
        {
            m->emission[0], m->emission[1], m->emission[2], m->emission[3]
        },
        {
            m->specular[0], m->specular[1], m->specular[2], m->specular[3]
        },
        {
            m->shininess[0], 0.0, 0.0, 1.0
        },
        m->useTex
    });

    useTex = m->useTex;

    diffTex = m->diffuseTex;
    normTex = m->normalTex;
    specTex = m->specularTex;
    envTex = m->environmentTex;

    if(material->shininess[0] > 99.0)
    {
        mirrorMap = new MirrorCube(1024);
    }
    midPoint = Vector(0.0, 0.0, 0.0);

    for(Vector vpos : m->vertex)
    {
        midPoint += vpos;
    }
    midPoint /= vertexCount;

    return *this;
}

void Buffer::update(std::vector<Buffer*> fg, std::vector<Buffer*> bg)
{
    if(material->shininess[0] > 99.0)
    {
        mirrorMap->update(fg, bg, midPoint, this);
    }
}

void Buffer::render(Shader* sh, bool filterEmissive)
{
    if(filterEmissive && material->emission[0] < 0.1)
        return;

    if(diffTex)
        diffTex->bind(GL_TEXTURE0);
    if(normTex)
        normTex->bind(GL_TEXTURE1);
    if(specTex)
        specTex->bind(GL_TEXTURE2);

    if(material->shininess[0] > 99.0)
    {
        mirrorMap->cubeMap.colorAttachment->bind(GL_TEXTURE3);
    } else if(envTex)
        envTex->bind(GL_TEXTURE3);

	////printOpenGLError();
    sh->use();
	////printOpenGLError();

	////printOpenGLError();

    //glBindBuffer(GL_UNIFORM_BUFFER, materialBuffer);
    sh->uniform(sh->uniform("shininess"), material->shininess);
    sh->uniform(sh->uniform("specular"), material->specular);
    sh->uniform(sh->uniform("emission"), material->emission);
    sh->uniform(sh->uniform("diffuse"), material->diffuse);
    sh->uniform(sh->uniform("midPoint"), midPoint.homogenousCoord(0.0));


    //glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(material), (void*)&material);
    sh->uniform(sh->uniform("useTex"), useTex);
	////printOpenGLError();

    glBindBuffer(GL_ARRAY_BUFFER, BufferName[TEXCOORD_OBJECT]);
    glVertexAttribPointer(AttributIndex[TEXCOORD_OBJECT], 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[POSITION_OBJECT]);
    glVertexAttribPointer(AttributIndex[POSITION_OBJECT], 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[NORMAL_OBJECT]);
    glVertexAttribPointer(AttributIndex[NORMAL_OBJECT], 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[TANGENT_OBJECT]);
    glVertexAttribPointer(AttributIndex[TANGENT_OBJECT], 3, GL_FLOAT, GL_FALSE, 0, 0);
	////printOpenGLError();

    glEnableVertexAttribArray(AttributIndex[TEXCOORD_OBJECT]);
    glEnableVertexAttribArray(AttributIndex[POSITION_OBJECT]);
    glEnableVertexAttribArray(AttributIndex[NORMAL_OBJECT]);
    glEnableVertexAttribArray(AttributIndex[TANGENT_OBJECT]);
	////printOpenGLError();

    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	////printOpenGLError();

    glDisableVertexAttribArray(AttributIndex[TANGENT_OBJECT]);
    glDisableVertexAttribArray(AttributIndex[NORMAL_OBJECT]);
    glDisableVertexAttribArray(AttributIndex[POSITION_OBJECT]);
    glDisableVertexAttribArray(AttributIndex[TEXCOORD_OBJECT]);

    Shader::fixedPipeline.use();
	////printOpenGLError();

	////printOpenGLError();
}

void Buffer::computeTangentBasis(
    // inputs
    std::vector<Vector> vertices,
    std::vector<Vector> uvs,
    std::vector<Vector> normals,
    // outputs
    std::vector<Vector> & tangents
)
{
    for ( int i=0; i<vertices.size(); i+=3){

        // Shortcuts for vertices
        Vector & v0 = vertices[i+0];
        Vector & v1 = vertices[i+1];
        Vector & v2 = vertices[i+2];

        // Shortcuts for UVs
        Vector & uv0 = uvs[i+0];
        Vector & uv1 = uvs[i+1];
        Vector & uv2 = uvs[i+2];


        // Edges of the triangle : postion delta
        Vector deltaPos1 = v1-v0;
        Vector deltaPos2 = v2-v0;

        // UV delta
        Vector deltaUV1 = uv1-uv0;
        Vector deltaUV2 = uv2-uv0;

        Vector vf1 = (deltaPos2 * deltaUV1.y);
        Vector vf2 = (deltaPos1 * deltaUV2.y);

        float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
        Vector tangent = (vf2   - vf1)*r;

        // Set the same tangent for all three vertices of the triangle.
        // They will be merged later, in vboindexer.cpp
        tangents.push_back(tangent);
        tangents.push_back(tangent);
        tangents.push_back(tangent);

    }
}
