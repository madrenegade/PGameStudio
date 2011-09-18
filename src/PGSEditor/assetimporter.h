#ifndef ASSETIMPORTER_H
#define ASSETIMPORTER_H

#include <QString>
#include <boost/shared_ptr.hpp>

namespace Assimp
{
class Importer;
}

class aiScene;

class AssetImporter
{
public:
    AssetImporter();

    bool run(const QString& file);

    QString getError() const;

private:
    boost::shared_ptr<Assimp::Importer> importer;

    void processScene(const aiScene* scene);
};

#endif // ASSETIMPORTER_H
