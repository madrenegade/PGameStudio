#ifndef SCENEEXPORTER_H
#define SCENEEXPORTER_H

#include <QString>

class SceneExporter
{
public:
    SceneExporter();

    void createEmptyScene(const QString& dir, const QStringList& systems);
};

#endif // SCENEEXPORTER_H
