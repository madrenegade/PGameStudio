#include "assetimporter.h"
#include "scenedata.h"
#include "mesh.h"
#include "material.h"
#include "scenenode.h"
#include "camera.h"

#include "Math/Vector4.h"
#include "Math/Matrix4.h"

#include <assimp/assimp.hpp>
#include <assimp/aiScene.h>
#include <assimp/aiPostProcess.h>

#include <iostream>
#include <glog/logging.h>

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
    processCameras(scene->mCameras, scene->mNumCameras);
    processNodes(scene->mRootNode);
}

void AssetImporter::processTextures(aiTexture** /*textures*/, unsigned int numTextures)
{
    for(unsigned int i = 0; i < numTextures; ++i)
    {
        //aiTexture* texture = textures[i];

        // TODO
    }
}

void AssetImporter::addTextureToMaterial(Material* material, aiMaterial* aiMat, aiTextureType type)
{
    const unsigned int numTextures = aiMat->GetTextureCount(type);
    std::cout << "numTextures: " << numTextures << std::endl;
    for(unsigned int j = 0; j < numTextures; ++j)
    {
        aiString path;
        aiMat->GetTexture(type, j, &path);

        std::string s(path.data, path.length);
        size_t lastSlash = s.find_last_of('/');

        material->textures.push_back(s.substr(lastSlash + 1));
    }
}

void AssetImporter::processMaterials(aiMaterial** materials, unsigned int numMaterials)
{
    for(unsigned int i = 0; i < numMaterials; ++i)
    {
        aiMaterial* material = materials[i];

        boost::shared_ptr<Material> mat(new Material);

        aiString name;
        material->Get(AI_MATKEY_NAME, name);

        aiColor3D diffuse;
        material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);

        aiColor3D specular;
        material->Get(AI_MATKEY_COLOR_SPECULAR, specular);

        float opacity;
        material->Get(AI_MATKEY_OPACITY, opacity);

        float shininess;
        material->Get(AI_MATKEY_SHININESS, shininess);

        mat->name.assign(name.data, name.length);
        mat->diffuse = Math::Vector4(diffuse.r, diffuse.g, diffuse.b, opacity);
        mat->specular = Math::Vector4(specular.r, specular.g, specular.b, shininess);

        addTextureToMaterial(mat.get(), material, aiTextureType_NONE);
        addTextureToMaterial(mat.get(), material, aiTextureType_DIFFUSE);
        addTextureToMaterial(mat.get(), material, aiTextureType_SPECULAR);
        addTextureToMaterial(mat.get(), material, aiTextureType_AMBIENT);
        addTextureToMaterial(mat.get(), material, aiTextureType_EMISSIVE);
        addTextureToMaterial(mat.get(), material, aiTextureType_HEIGHT);
        addTextureToMaterial(mat.get(), material, aiTextureType_NORMALS);
        addTextureToMaterial(mat.get(), material, aiTextureType_SHININESS);
        addTextureToMaterial(mat.get(), material, aiTextureType_OPACITY);
        addTextureToMaterial(mat.get(), material, aiTextureType_DISPLACEMENT);
        addTextureToMaterial(mat.get(), material, aiTextureType_LIGHTMAP);
        addTextureToMaterial(mat.get(), material, aiTextureType_REFLECTION);
        addTextureToMaterial(mat.get(), material, aiTextureType_UNKNOWN);

        std::cout << "Textures: " << mat->textures.size() << std::endl;

        importedData->materials.push_back(mat);
    }
}

void AssetImporter::processMeshes(aiMesh** meshes, unsigned int numMeshes)
{
    for(unsigned int i = 0; i < numMeshes; ++i)
    {
        aiMesh* mesh = meshes[i];
        boost::shared_ptr<Mesh> m(new Mesh());

        m->material = importedData->materials.at(mesh->mMaterialIndex).get();

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
                m->texCoords[t][v] = Math::Vector2(mesh->mTextureCoords[t][v].x, mesh->mTextureCoords[t][v].y);
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

void AssetImporter::processCameras(aiCamera** cameras, unsigned int numCameras)
{
    LOG(INFO) << "Importing " << numCameras << " cameras";

    for(unsigned int i = 0; i < numCameras; ++i)
    {
        const aiCamera* camera = cameras[i];

        boost::shared_ptr<Camera> cam(new Camera);
        cam->name = std::string(camera->mName.data, camera->mName.length);
        cam->position = Math::Vector3(camera->mPosition.x, camera->mPosition.y, camera->mPosition.z);
        cam->lookAt = Math::Vector3(camera->mLookAt.x, camera->mLookAt.y, camera->mLookAt.z);
        cam->up = Math::Vector3(camera->mUp.x, camera->mUp.y, camera->mUp.z);

        importedData->cameras.push_back(cam);
    }
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

    // transform
    aiVector3D scaling;
    aiQuaternion rotation;
    aiVector3D position;
    node->mTransformation.Decompose(scaling, rotation, position);

    Math::Matrix4 S(Math::Matrix4::Scale(Math::Vector3(scaling.x, scaling.y, scaling.z)));
    Math::Matrix4 T(Math::Matrix4::CreateTranslation(Math::Vector3(position.x, position.y, position.z)));
    Math::Matrix4 R(Math::Matrix4::CreateRotation(Math::Quaternion(rotation.x, rotation.y, rotation.z, rotation.w)));

    sceneNode->transform.reset(new Math::Matrix4(S * T.Transpose() * R));

    for(unsigned int i = 0; i < node->mNumMeshes; ++i)
    {
        unsigned int meshIndex = node->mMeshes[i];

        sceneNode->meshes.push_back(importedData->meshes.at(meshIndex).get());
    }

    for(unsigned int i = 0; i < node->mNumChildren; ++i)
    {
        sceneNode->children.push_back(processNode(node->mChildren[i]));
    }

    return sceneNode;
}
