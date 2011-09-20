#include "assetimporter.h"
#include "scenedata.h"
#include "mesh.h"
#include "scenenode.h"

#include <assimp/assimp.hpp>
#include <assimp/aiScene.h>
#include <assimp/aiPostProcess.h>

#include <iostream>

AssetImporter::AssetImporter()
    : importer(new Assimp::Importer)
{
}

bool AssetImporter::run(const QString& file)
{
    const aiScene* scene = importer->ReadFile(file.toAscii(), aiProcess_CalcTangentSpace | aiProcess_Triangulate);

    if(!scene)
    {
        return false;
    }

    processScene(scene);

    return true;
}

boost::shared_ptr<SceneData> AssetImporter::getImportedData() const
{
    return importedData;
}

QString AssetImporter::getError() const
{
    return QString::fromStdString(importer->GetErrorString());
}

void AssetImporter::processScene(const aiScene *scene)
{
    importedData.reset(new SceneData());

    processTextures(scene->mTextures, scene->mNumTextures);
    processMaterials(scene->mMaterials, scene->mNumMaterials);
    processMeshes(scene->mMeshes, scene->mNumMeshes);
    processCameras();
    processNodes(scene->mRootNode);
}

void AssetImporter::processTextures(aiTexture** textures, unsigned int numTextures)
{
    for(unsigned int i = 0; i < numTextures; ++i)
    {
        aiTexture* texture = textures[i];

        // TODO
    }
}

void AssetImporter::processMaterials(aiMaterial** materials, unsigned int numMaterials)
{
    for(unsigned int i = 0; i < numMaterials; ++i)
    {
        aiMaterial* material = materials[i];

        // TODO
    }
}

void AssetImporter::processMeshes(aiMesh** meshes, unsigned int numMeshes)
{
    for(unsigned int i = 0; i < numMeshes; ++i)
    {
        aiMesh* mesh = meshes[i];
        boost::shared_ptr<Mesh> m(new Mesh());

        if(mesh->HasPositions())
        {
            m->positions.resize(mesh->mNumVertices);
        }

        if(mesh->HasNormals())
        {
            m->normals.resize(mesh->mNumVertices);
        }

        if(mesh->HasTangentsAndBitangents())
        {
            m->tangents.resize(mesh->mNumVertices);
            m->bitangents.resize(mesh->mNumVertices);
        }

        if(mesh->GetNumUVChannels() > 0)
        {
            m->texCoords.resize(mesh->GetNumUVChannels());

            for(unsigned int t = 0; t < mesh->GetNumUVChannels(); ++t)
            {
                m->texCoords[t].resize(mesh->mNumVertices);
            }
        }

        for(unsigned int v = 0; v < mesh->mNumVertices; ++v)
        {
            if(mesh->HasPositions())
            {
                m->positions[v] = Math::Vector3(mesh->mVertices[v].x, mesh->mVertices[v].y, mesh->mVertices[v].z);
            }

            if(mesh->HasNormals())
            {
                m->normals[v] = Math::Vector3(mesh->mNormals[v].x, mesh->mNormals[v].y, mesh->mNormals[v].z);
            }

            if(mesh->HasTangentsAndBitangents())
            {
                m->tangents[v] = Math::Vector3(mesh->mTangents[v].x, mesh->mTangents[v].y, mesh->mTangents[v].z);
                m->bitangents[v] = Math::Vector3(mesh->mBitangents[v].x, mesh->mBitangents[v].y, mesh->mBitangents[v].z);
            }

            for(unsigned int t = 0; t < mesh->GetNumUVChannels(); ++t)
            {
                m->texCoords[t][v] = Math::Vector2(mesh->mTextureCoords[t]->x, mesh->mTextureCoords[t]->y);
            }
        }

        m->faces.resize(mesh->mNumFaces);

        for(unsigned int f = 0; f < mesh->mNumFaces; ++f)
        {
            aiFace& face = mesh->mFaces[f];
            m->faces[f].indexes.resize(face.mNumIndices);

            for(unsigned int index = 0; index < face.mNumIndices; ++index)
            {
                m->faces[f].indexes[index] = face.mIndices[index];
            }
        }

        importedData->meshes.push_back(m);
    }
}

void AssetImporter::processCameras()
{

}

void AssetImporter::processNodes(const aiNode* rootNode)
{
    importedData->rootNode = processNode(rootNode);
}

boost::shared_ptr<SceneNode> AssetImporter::processNode(const aiNode *node)
{
    std::string name(node->mName.data, node->mName.length);

    boost::shared_ptr<SceneNode> sceneNode(new SceneNode());
    sceneNode->name = name;

    for(unsigned int i = 0; i < node->mNumChildren; ++i)
    {
        sceneNode->children.push_back(processNode(node->mChildren[i]));
    }

    return sceneNode;
}
