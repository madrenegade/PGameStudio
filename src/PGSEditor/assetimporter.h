#ifndef ASSETIMPORTER_H
#define ASSETIMPORTER_H

#include <QString>
#include <boost/shared_ptr.hpp>

#include <assimp/aiMaterial.h>

namespace Assimp
{
class Importer;
}

class aiScene;
class aiMesh;
class aiNode;
class aiTexture;

class SceneData;
class SceneNode;
class Material;

class AssetImporter
{
public:
    AssetImporter();

    bool run(const QString& file);

    boost::shared_ptr<SceneData> getImportedData() const;

    QString getError() const;

private:
    void processScene(const aiScene* scene);

    void processTextures(aiTexture** textures, unsigned int numTextures);
    void processMaterials(aiMaterial** materials, unsigned int numMaterials);
    void processMeshes(aiMesh** meshes, unsigned int numMeshes);
    void processCameras();
    void processNodes(const aiNode* rootNode);

    void addTextureToMaterial(Material* material, aiMaterial* aiMat, aiTextureType type);

    boost::shared_ptr<SceneNode> processNode(const aiNode* node);

    boost::shared_ptr<Assimp::Importer> importer;
    boost::shared_ptr<SceneData> importedData;
};

#endif // ASSETIMPORTER_H
