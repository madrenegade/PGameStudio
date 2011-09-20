#ifndef SCENEEXPORTER_H
#define SCENEEXPORTER_H

#include <QString>
#include <fstream>
#include <boost/shared_ptr.hpp>

#include "Math/Vector2.h"
#include "Math/Vector3.h"

class SceneData;
class SceneNode;

class SceneExporter
{
public:
    SceneExporter();

    void createEmptyScene(const QString& dir, const QStringList& systems);
    bool save(const boost::shared_ptr<SceneData>& scene, const QString& dir);

private:
    template<typename T>
    void write(const T& data)
    {
        out->write(reinterpret_cast<const char*>(&data), sizeof(T));
    }

    void writeString(const std::string& s);
    void writeNode(const SceneNode* node);

    boost::shared_ptr<std::fstream> out;
};

#endif // SCENEEXPORTER_H
