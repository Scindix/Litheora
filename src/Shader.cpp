#include "Shader.h"

const std::string Shader::TRANSFORMATION_BLOCK_NAME = "Transformation";
const GLuint Shader::TRANSFORMATION_BLOCK_BINDING_POINT = 1;

const std::string Shader::MATERIAL_BLOCK_NAME = "Material";
const GLuint Shader::MATERIAL_BLOCK_BINDING_POINT = 2;

Shader* Shader::mergeLayerPipeline;
Shader* Shader::simplePipeline;
Shader* Shader::displayPipeline;
Shader* Shader::backgroundPipeline;
Shader* Shader::shadowPipeline;
const Shader Shader::fixedPipeline = Shader();

Shader::Shader(std::string s)
{

	program = glCreateProgram();

	loadShaders(s);

}

void Shader::init()
{

    simplePipeline = new Shader("Simple");

    displayPipeline = new Shader("Display");

    mergeLayerPipeline = new Shader("MergeLayer");

    backgroundPipeline = new Shader("BackgroundMapping");

    shadowPipeline = new Shader("ShadowMapping");

}

Shader::Shader()
{
	program = 0;
}

Shader::~Shader()
{
    ///glDeleteProgram(program);
}

void Shader::use() const
{
    glUseProgram(program);
}

void Shader::loadShaders(std::string s)
{

    GLuint vs = 0, fs = 0, gs = 0, tes = 0, tcs = 0;

    try
    {

        vs = loadShader(GL_VERTEX_SHADER, s);

    } catch_err(Error::ShaderNoFile, Error::ShaderNoVertex)
    try
    {

        fs = loadShader(GL_FRAGMENT_SHADER, s);

    } catch_err(Error::ShaderNoFile, Error::ShaderNoFragment)
    try
    {

        gs = loadShader(GL_GEOMETRY_SHADER, s);

    } catch_ignore(Error::ShaderNoFile)
    try
    {

        tes = loadShader(GL_TESS_EVALUATION_SHADER, s);

    } catch_ignore(Error::ShaderNoFile)
    try
    {

        tcs = loadShader(GL_TESS_CONTROL_SHADER, s);

    } catch_ignore(Error::ShaderNoFile)


    glLinkProgram(program);


    if(vs != 0)
        glDeleteShader(vs);


    if(fs != 0)
        glDeleteShader(fs);


    if(gs != 0)
        glDeleteShader(gs);


    if(tes != 0)
        glDeleteShader(tes);


    if(tcs != 0)
        glDeleteShader(tcs);


    if(!checkProgram(program, GL_LINK_STATUS))
        throw Error::ShaderLinkerError;


    GLuint transBlockIndex = glGetUniformBlockIndex(program, TRANSFORMATION_BLOCK_NAME.c_str());

    if(transBlockIndex != GL_INVALID_INDEX)
        glUniformBlockBinding(program, transBlockIndex, TRANSFORMATION_BLOCK_BINDING_POINT);


    GLuint matBlockIndex = glGetUniformBlockIndex(program, MATERIAL_BLOCK_NAME.c_str());

    if(matBlockIndex != GL_INVALID_INDEX)
        glUniformBlockBinding(program, matBlockIndex, MATERIAL_BLOCK_BINDING_POINT);


    GLint texUnitLoc = glGetUniformLocation(program, "diffuseTex");
    if(texUnitLoc != -1)
        glProgramUniform1i(program, texUnitLoc , 0);


    texUnitLoc = glGetUniformLocation(program, "normalTex");

    if(texUnitLoc != -1)
        glProgramUniform1i(program, texUnitLoc , 1);


    texUnitLoc = glGetUniformLocation(program, "specularTex");

    if(texUnitLoc != -1)
        glProgramUniform1i(program, texUnitLoc , 2);


    texUnitLoc = glGetUniformLocation(program, "environmentTex");

    if(texUnitLoc != -1)
        glProgramUniform1i(program, texUnitLoc , 3);


    texUnitLoc = glGetUniformLocation(program, "shadowTex");

    if(texUnitLoc != -1)
        glProgramUniform1i(program, texUnitLoc , 4);

}

GLuint Shader::loadShader(GLenum i, std::string name)
{
    std::string shaderFileName;
    try
    {
        shaderFileName = (Config::app/"shader"%name/getShaderName(i)).valueSTRING();
    } catch_err(Error::ConfigAtSearchPropNotFound, Error::ShaderNoFile)
    File::Text file(shaderFileName);
    std::string shaderString;
    file >> shaderString;
    const char* shaderCString = shaderString.c_str();
	GLuint shader = glCreateShader(i);
	glShaderSource(shader, 1, &shaderCString, NULL);
	glCompileShader(shader);
    if(!checkShader(shader, GL_COMPILE_STATUS, i))
    {
        throw Error::ShaderCompileError;
        exit(-1);
    }
    glAttachShader(program, shader);
    return shader;
}

std::string Shader::getShaderName(GLenum i)
{
    switch(i)
    {
    case GL_VERTEX_SHADER:
        return "Vertex";
    case GL_FRAGMENT_SHADER:
        return "Fragment";
    case GL_GEOMETRY_SHADER:
        return "Geometry";
    case GL_TESS_EVALUATION_SHADER:
        return "TessEvaluation";
    case GL_TESS_CONTROL_SHADER:
        return "TessControl";
    default:
        throw Error::ShaderUnknownType;
    }
}

bool Shader::checkShader(GLint object, GLint type, GLenum shaderType)
{
    GLint success;
    glGetShaderiv(object, type, &success);
	if(success == GL_FALSE)
	{
        std::cout << ConsoleBlocks::Error << LP("ShaderCompileError", {getShaderName(shaderType)}) << std::endl;
        GLint infoLogSize;
        glGetShaderiv(object, GL_INFO_LOG_LENGTH, &infoLogSize);
        char* buffer = new char[infoLogSize];
		glGetShaderInfoLog(object, infoLogSize, NULL, buffer);
		std::cout << ConsoleBlocks::Info << buffer << "\n\n";
        delete[] buffer;
		return false;
	}
    return true;
}

bool Shader::checkProgram(GLint object, GLint type)
{
    GLint success;
    glGetProgramiv(object, type, &success);
	if(success == GL_FALSE)
	{
	    std::cout << ConsoleBlocks::Error << L("ShaderLinkerError") << std::endl;
        GLint infoLogSize;
        glGetProgramiv(object, GL_INFO_LOG_LENGTH, &infoLogSize);
        char* buffer = new char[infoLogSize];
		glGetProgramInfoLog(object, infoLogSize, NULL, buffer);
		std::cout << ConsoleBlocks::Info << buffer << "\n\n";
        delete[] buffer;
		return false;
	}
    return true;
}

GLint Shader::attribute(std::string s)
{
    GLint i = glGetAttribLocation(program, s.c_str());
    if(i==-1)
    {
        std::cout << ConsoleBlocks::Warning << "'" << s << "'" << L("ShaderAtrrUniNameNotFoundOrMalformed") << "\n";
        ///throw Error::ShaderAttribNotFound; @todo Need a better workaround for this problem
    }
    return i;
}

GLint Shader::uniform(std::string s)
{
    GLint i = glGetUniformLocation(program, s.c_str());
    if(i==-1)
    {
        ///std::cout << ConsoleBlocks::Warning << "'" << s << "'" << L("ShaderAtrrUniNameNotFoundOrMalformed") << "\n";
        ///throw Error::ShaderUniformNotFound; @todo drivers may optimize this out. Need a better workaround
    }
    return i;
}

void Shader::uniform(GLint i, GLfloat f1)
{
    use();
    glUniform1f(i, f1);
}

void Shader::uniform(GLint i, GLfloat f1, GLfloat f2)
{
    use();
    glUniform2f(i, f1, f2);
}

void Shader::uniform(GLint i, GLfloat f1, GLfloat f2, GLfloat f3)
{
    use();
    glUniform3f(i, f1, f2, f3);
}

void Shader::uniform(GLint i, GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4)
{
    use();
    glUniform4f(i, f1, f2, f3, f4);
}

void Shader::uniform(GLint i, std::vector<GLfloat> fv)
{
    use();
    switch(fv.size())
    {
    case 0:
        throw Error::ShaderNoUniforms;
    case 1:
        glUniform1fv(i, 1, fv.data());
        return;
    case 2:
        glUniform2fv(i, 1, fv.data());
        return;
    case 3:
        glUniform3fv(i, 1, fv.data());
        return;
    case 4:
        glUniform4fv(i, 1, fv.data());
        return;
    default:
        throw Error::ShaderTooMuchUniforms;
    }
}


void Shader::uniform(GLint i, GLint i1)
{
    use();
    glUniform1i(i, i1);
}

void Shader::uniform(GLint i, GLint i1, GLint i2)
{
    use();
    glUniform2i(i, i1, i2);
}

void Shader::uniform(GLint i, GLint i1, GLint i2, GLint i3)
{
    use();
    glUniform3i(i, i1, i2, i3);
}

void Shader::uniform(GLint i, GLint i1, GLint i2, GLint i3, GLint i4)
{
    use();
    glUniform4i(i, i1, i2, i3, i4);
}

void Shader::uniform(GLint i, std::vector<GLint> iv)
{
    use();
    switch(iv.size())
    {
    case 0:
        throw Error::ShaderNoUniforms;
    case 1:
        glUniform1iv(i, 1, iv.data());
        return;
    case 2:
        glUniform2iv(i, 1, iv.data());
        return;
    case 3:
        glUniform3iv(i, 1, iv.data());
        return;
    case 4:
        glUniform4iv(i, 1, iv.data());
        return;
    default:
        throw Error::ShaderTooMuchUniforms;
    }
}

