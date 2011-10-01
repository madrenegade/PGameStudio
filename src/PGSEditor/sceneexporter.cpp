#include "sceneexporter.h"
#include "scenedata.h"
#include "scenenode.h"
#include "mesh.h"
#include "camera.h"
#include "Math/Matrix4.h"

#include <iostream>

SceneExporter::SceneExporter()
{
}

void SceneExporter::createEmptyScene(const QString& /*dir*/, const QStringList& /*systems*/)
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
    unsigned int numMaterials = scene->materials.size();
    write(numMaterials);

    for(unsigned int i = 0; i < numMaterials; ++i)
    {
        Material* mat = scene->materials.at(i).get();
        mat->index = i;

        writeString(mat->name);
        write(mat->diffuse.X);
        write(mat->diffuse.Y);
        write(mat->diffuse.Z);
        write(mat->diffuse.W);
        std::cout << "Writing diffuse " << mat->diffuse.X << ", " << mat->diffuse.Y << ", " << mat->diffuse.Z << ", " << mat->diffuse.W << std::endl;
        write(mat->specular);

        unsigned int numTextures = mat->textures.size();
        write(numTextures);

        for(unsigned int j = 0; j < numTextures; ++j)
        {
            writeString(mat->textures.at(j));
        }
    }

    // meshes
    unsigned int numMeshes = scene->meshes.size();
    write(numMeshes);

    for(unsigned int i = 0; i < numMeshes; ++i)
    {
        Mesh* mesh = scene->meshes.at(i).get();
        mesh->index = i;

        unsigned int materialIndex = mesh->material->index;
        write(materialIndex);

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

            if(hasTexCoords)
            {
                for(unsigned int c = 0; c < numUVChannels; ++c)
                {
                    write(mesh->texCoords[c][v]);
                }
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
        }

        const unsigned int numFaces = mesh->faces.size();
        write(numFaces);

        for(unsigned int f = 0; f < numFaces; ++f)
        {
            const unsigned char numIndexes = mesh->faces.at(f).indexes.size();
            write(numIndexes);

            for(unsigned int index = 0; index < numIndexes; ++index)
            {
                const unsigned int vertexIndex = mesh->faces.at(f).indexes.at(index);
                write(vertexIndex);
            }
        }

    }

    // cameras
    const unsigned int numCameras = scene->cameras.size();
    write(numCameras);

    for(unsigned int i = 0; i < numCameras; ++i)
    {
        Camera* cam = scene->cameras.at(i).get();

        writeString(cam->name);
        write(cam->position);
        write(cam->lookAt);
        write(cam->up);
    }

    // scene graph
    writeNode(scene->rootNode.get());

    out.reset();

    return true;
}

void SceneExporter::writeString(const std::string& s)
{
    unsigned int len = s.size();
    write(len);
    out->write(s.c_str(), len);
}

void SceneExporter::writeNode(const SceneNode* node)
{
    writeString(node->name);

    const double* transform = *node->transform;

    out->write(reinterpret_cast<const char*>(transform), 16 * sizeof(double));

    unsigned int numMeshes = node->meshes.size();
    write(numMeshes);

    for(unsigned int i = 0; i < numMeshes; ++i)
    {
        unsigned int meshIndex = node->meshes.at(i)->index;
        write(meshIndex);
    }

    unsigned int numChildren = node->children.size();
    write(numChildren);

    for(unsigned int i = 0; i < numChildren; ++i)
    {
        writeNode(node->children.at(i).get());
    }
}
