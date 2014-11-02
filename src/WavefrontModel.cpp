#include "WavefrontModel.h"

WavefrontModel::WavefrontModel(std::string s)
{

    std::cout << ConsoleBlocks::Info << "Opening Mesh file: "<< s << "\n";
    File::Text file(s);
    std::string wave;
    file >> wave;
    std::vector<std::string> lines = StringHelper::explode(wave, '\n');
    size_t meshIndex = -1;
    size_t objID = -1;
    std::vector<std::vector<Vector>> loadedData;
    std::map<std::string, Material> materials;
    std::map<std::string, GLint> useTexs;
    std::map<std::string, Texture*> diffuseMaps;
    std::map<std::string, Texture*> specularMaps;
    std::map<std::string, Texture*> normalMaps;
    loadedData.insert(loadedData.begin(), 3, *new std::vector<Vector>);
    for(size_t i = 0; i < lines.size(); i++)
    {
        if(lines[i][lines[i].size()-1] == '\r')
        {
            lines[i] = lines[i].substr(0, lines[i].size()-1);
        }
        if(lines[i].substr(0,6) == "mtllib")
        {
            std::string libName = lines[i].substr(7);
            std::string parentPath = file.parent().path;
            std::cout << "Lib: " << S(parentPath + libName) << "\n";
            File::Text libFile(S(parentPath + libName));
            std::string mat;
            libFile >> mat;
            StringHelper::replaceAll(mat, "\r", "");
            std::vector<std::string> matLines = StringHelper::explode(mat, '\n');
            std::string matKey = "default";
            for(size_t i = 0; i < matLines.size(); i++)
            {
                if(matLines[i].substr(0,6) == "newmtl")
                    matKey = matLines[i].substr(7);
                if(matLines[i].substr(0,1) == "d")
                {
                    if(materials[matKey].diffuse.size() < 4)
                    {
                        materials[matKey].diffuse =
                        {
                            0.0,
                            0.0,
                            0.0,
                            StringHelper::toFloat(matLines[i].substr(2)),
                        };
                    } else
                    {
                        materials[matKey].diffuse[3] = StringHelper::toFloat(matLines[i].substr(2));
                    }
                }
                if(matLines[i].substr(0,2) == "Ns")
                {
                    materials[matKey].shininess =
                    {
                        StringHelper::toFloat(matLines[i].substr(3)),
                        0.0,
                        0.0,
                        1.0
                    };
                }
                if(matLines[i].substr(0,2) == "Kd")
                {
                    std::vector<std::string> vec = StringHelper::explode(matLines[i].substr(3), ' ');

                    if(materials[matKey].diffuse.size() < 4)
                    {
                        materials[matKey].diffuse =
                        {
                            StringHelper::toFloat(vec[0]),
                            StringHelper::toFloat(vec[1]),
                            StringHelper::toFloat(vec[2]),
                            1.0
                        };
                    } else
                    {
                        materials[matKey].diffuse[0] = StringHelper::toFloat(vec[0]);
                        materials[matKey].diffuse[1] = StringHelper::toFloat(vec[1]);
                        materials[matKey].diffuse[2] = StringHelper::toFloat(vec[2]);
                    }
                }
                if(matLines[i].substr(0,2) == "Ke")
                {
                    std::vector<std::string> vec = StringHelper::explode(matLines[i].substr(3), ' ');
                    materials[matKey].emission =
                    {
                        StringHelper::toFloat(vec[0]),
                        StringHelper::toFloat(vec[1]),
                        StringHelper::toFloat(vec[2]),
                        1.0
                    };
                    /**materials[matKey].ambient =
                    {
                        0.1,
                        0.1,
                        0.1,
                        1.0
                    };**/
                }
                if(matLines[i].substr(0,2) == "Ks")
                {
                    std::vector<std::string> vec = StringHelper::explode(matLines[i].substr(3), ' ');
                    materials[matKey].specular =
                    {
                        StringHelper::toFloat(vec[0]),
                        StringHelper::toFloat(vec[1]),
                        StringHelper::toFloat(vec[2]),
                        1.0
                    };
                }
                if(matLines[i].substr(0,6) == "map_Kd")
                {
                    diffuseMaps[matKey] = new Texture(parentPath + matLines[i].substr(7));
                    useTexs[matKey] |= DIFFUSE;
                }
                if(matLines[i].substr(0,6) == "map_Ks")
                {
                    specularMaps[matKey] = new Texture(parentPath + matLines[i].substr(7));
                    useTexs[matKey] |= SPECULAR;
                }
                if(matLines[i].substr(0,6) == "map_Kn")
                {
                    normalMaps[matKey] = new Texture(parentPath + matLines[i].substr(7));
                    useTexs[matKey] |= NORMAL;
                }
            }
        }
        if(lines[i].substr(0,1) == "#")
            std::cout << ConsoleBlocks::Info << lines[i].substr(1) << "\n";
        if(lines[i].substr(0,1) == "v")
        {
            std::string vert = lines[i].substr(1);
            BUFFER_TYPE vectorType = POSITION_OBJECT;
            if(vert.substr(0,1) == "n")
            {
                vectorType = NORMAL_OBJECT;
                vert = vert.substr(1);
            }
            if(vert.substr(0,1) == "t")
            {
                vectorType = TEXCOORD_OBJECT;
                vert = vert.substr(1);
            }
            vert = vert.substr(1);
            std::vector<std::string> verts = StringHelper::explode(vert, ' ');
            std::vector<float> vf;
            for(std::string v : verts)
            {
                vf.push_back(StringHelper::toFloat(v));
            }
            Vector bvf;
            if(vectorType == TEXCOORD_OBJECT)
                bvf = {vf[0], vf[1], 0.0f};
            else
                bvf = {vf[0], vf[1], vf[2]};
            loadedData[vectorType].push_back(bvf);
        }
        if(lines[i].substr(0,1) == "g")
        {
            meshIndex++;
            buffers.push_back(new Buffer(Shader::simplePipeline));
            std::cout << "Object: " << lines[i].substr(2) << "\n";
        }
        if(lines[i].substr(0,1) == "o")
        {
            objID++;
            std::cout << "Group " << objID << ": " << lines[i].substr(2) << "\n";
        }
        if(lines[i].substr(0,6) == "usemtl")
        {
            meshes.push_back(Mesh(
                                        materials[lines[i].substr(7)].diffuse,
                                        materials[lines[i].substr(7)].emission,
                                        materials[lines[i].substr(7)].specular,
                                        materials[lines[i].substr(7)].useTEX,
                                        materials[lines[i].substr(7)].shininess
                                      ));
            size_t index = meshes.size()-1;

            meshes[index].groupID = objID;
            meshes[index].useTex = useTexs[lines[i].substr(7)];
            meshes[index].diffuseTex = diffuseMaps[lines[i].substr(7)];
            meshes[index].specularTex = specularMaps[lines[i].substr(7)];
            meshes[index].normalTex = normalMaps[lines[i].substr(7)];
        }
        if(lines[i].substr(0,1) == "f")
        {
            std::string faceDef = lines[i].substr(1);
            std::vector<std::string> faces = StringHelper::explode(faceDef, ' ');
            for(std::string face : faces)
            {
                std::vector<std::string> vert = StringHelper::explode(face, '/');
                for(size_t i = 0; i < vert.size(); i++)
                {
                    size_t index = 0;
                    StringHelper::replaceAll(vert[i], "\n", "");
                    StringHelper::replaceAll(vert[i], " ", "");
                    index = StringHelper::to_int_strict(vert[i]);
                    if(i == 0)
                    {
                        if(loadedData[POSITION_OBJECT].size() > index-1)
                            meshes[meshIndex].vertex.push_back(loadedData[POSITION_OBJECT][index-1]);
                        else
                            meshes[meshIndex].vertex.push_back({0.0, 0.0, 0.0});
                    } else if(i == 1)
                    {
                        if(loadedData[TEXCOORD_OBJECT].size() > index-1)
                            meshes[meshIndex].texCoord.push_back(loadedData[TEXCOORD_OBJECT][index-1]);
                        else
                            meshes[meshIndex].texCoord.push_back({0.0, 0.0, 0.0});
                    } else if(i == 2)
                    {
                        if(loadedData[NORMAL_OBJECT].size() > index-1)
                            meshes[meshIndex].normal.push_back(loadedData[NORMAL_OBJECT][index-1]);
                        else
                            meshes[meshIndex].normal.push_back({0.0, 0.0, 0.0});
                    } else
                    {
                        std::cout << ConsoleBlocks::Warning << "Unsupported Vertex Data\n";
                    }
                }
            }
        }
    }
    for(size_t i = 0; i < meshes.size(); i++)
    {
        *buffers[i] << &meshes[i];
    }
}

WavefrontModel::~WavefrontModel()
{
    //dtor
}

void WavefrontModel::render()
{
    for(size_t i = 0; i < buffers.size(); i++)
    {
        buffers[i]->render(true);
    }
}
