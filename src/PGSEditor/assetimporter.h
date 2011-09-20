#ifndef ASSETIMPORTER_H
#define ASSETIMPORTER_H

#include <QString>
#include <boost/shared_ptr.hpp>

namespace Assimp
{
class Importer;
}

class aiScene;
class SceneData;

class AssetImporter
{
public:
    AssetImporter();

    bool run(const QString& file);

    boost::shared_ptr<SceneData> getImportedData() const;

    QString getError() const;

private:
    void processScene(const aiScene* scene);

    boost::shared_ptr<Assimp::Importer> importer;
    boost::shared_ptr<SceneData> importedData;
};

#endif // ASSETIMPORTER_H
