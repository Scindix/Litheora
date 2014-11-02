#include <include.h>

#ifndef DISPLAYMESH_H
#define DISPLAYMESH_H

#include <Mesh.h>


class DisplayMesh : public Mesh
{
    public:
        DisplayMesh(Texture*, Texture*);
        DisplayMesh(Texture*, Texture*, Texture*, Texture*);
        virtual ~DisplayMesh();
    protected:
    private:
};

#endif // DISPLAYMESH_H
