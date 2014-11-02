#include <include.h>

#ifndef BACKGROUNDMAP_H
#define BACKGROUNDMAP_H

#include <Mesh.h>


class BackgroundMap : public Mesh
{
    public:
        BackgroundMap();
        BackgroundMap(Texture*);
        virtual ~BackgroundMap();
    protected:
    private:
};

#endif // BACKGROUNDMAP_H
