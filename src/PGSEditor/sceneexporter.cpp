#include "sceneexporter.h"
#include "scenedata.h"
#include "mesh.h"

SceneExporter::SceneExporter()
{
}

void SceneExporter::createEmptyScene(const QString& dir, const QStringList& systems)
{

}

bool SceneExporter::save(const boost::shared_ptr<SceneData> &scene, const QString &dir)
{
    std::string path(dir.toStdString() + "/scene.graphics");

    out.reset(new std::fstream(path.c_str(), std::ios::out));

    if(!(*out))
    {
        return false;
    }

    unsigned char sizeofNumber = sizeof(double);
    write(sizeofNumber);

    // textures
    // materials
    // meshes
    unsigned int numMeshes = scene->meshes.size();
    write(numMeshes);

    for(unsigned int i = 0; i < scene->meshes.size(); ++i)
    {
        Mesh* mesh = scene->meshes.at(i).get();

        bool hasPositions = !mesh->positions.empty();
        bool hasNormals = !mesh->normals.empty();
        bool hasTangents = !mesh->tangents.empty();
        bool hasBitangents = !mesh->bitangents.empty();

        bool hasTexCoords = !mesh->texCoords.empty();
        unsigned char numUVChannels = mesh->texCoords.size();

        write(hasPositions);
        write(hasNormals);
        write(hasTangents);
        write(hasBitangents);
        write(hasTexCoords);
        write(numUVChannels);

        const unsigned int numVertices = mesh->positions.size();
        write(numVertices);

        for(unsigned int v = 0; v < numVertices; ++v)
        {
            if(hasPositions)
            {
                write(mesh->positions[v]);
            }

            if(hasNormals)
            {
                write(mesh->normals[v]);
            }

            if(hasTangents)
            {
                write(mesh->tangents[v]);
            }

            if(hasBitangents)
            {
                write(mesh->bitangents[v]);
            }

            if(hasTexCoords)
            {
                for(unsigned int c = 0; c < numUVChannels; ++c)
                {
                    write(mesh->texCoords[c][v]);
                }
            }
        }
    }

    // cameras
    // scene graph

    out.reset();

    return true;
}
