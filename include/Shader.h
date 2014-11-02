#ifndef SHADER_H
#define SHADER_H

#include <include.h>
#include <gl_inc_hs.h>

class Shader
{
    public:
        Shader(std::string);
        Shader();
        virtual ~Shader();
        void use() const;
        GLuint loadShader(GLenum, std::string);
        void loadShaders(std::string);
        GLint attribute(std::string);
        GLint uniform(std::string);
        static const std::string TRANSFORMATION_BLOCK_NAME;
        static const GLuint TRANSFORMATION_BLOCK_BINDING_POINT;
        static const std::string MATERIAL_BLOCK_NAME;
        static const GLuint MATERIAL_BLOCK_BINDING_POINT;
        static Shader* mergeLayerPipeline;
        static Shader* simplePipeline;
        static Shader* displayPipeline;
        static Shader* backgroundPipeline;
        static Shader* shadowPipeline;
        static const Shader fixedPipeline;
        static void init();

        void uniform(GLint, GLfloat);
        void uniform(GLint, GLfloat, GLfloat);
        void uniform(GLint, GLfloat, GLfloat, GLfloat);
        void uniform(GLint, GLfloat, GLfloat, GLfloat, GLfloat);
        void uniform(GLint, std::vector<GLfloat>);

        void uniform(GLint, GLint);
        void uniform(GLint, GLint, GLint);
        void uniform(GLint, GLint, GLint, GLint);
        void uniform(GLint, GLint, GLint, GLint, GLint);
        void uniform(GLint, std::vector<GLint>);
    protected:
    private:
        static std::string getShaderName(GLenum);
        static bool checkProgram(GLint, GLint);
        static bool checkShader(GLint, GLint, GLenum);
        GLuint program;
};

#endif // SHADER_H
