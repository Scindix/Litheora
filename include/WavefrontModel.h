#include <include.h>

#ifndef WAVEFRONTMODEL_H
#define WAVEFRONTMODEL_H

#include <Mesh.h>
#include <Buffer.h>


class WavefrontModel
{
    public:
        WavefrontModel(std::string);
        virtual ~WavefrontModel();
        std::vector<Mesh> meshes;
        std::vector<Buffer*> buffers;
        void render();
    protected:
    private:
        std::map<std::string, Material> materials;
};

#endif // WAVEFRONTMODEL_H
