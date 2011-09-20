#ifndef SCENEEXPORTER_H
#define SCENEEXPORTER_H

#include <QString>
#include <boost/shared_ptr.hpp>

class SceneData;

class SceneExporter
{
public:
    SceneExporter();

    void createEmptyScene(const QString& dir, const QStringList& systems);
    void save(const boost::shared_ptr<SceneData>& scene, const QString& dir);
};

#endif // SCENEEXPORTER_H
