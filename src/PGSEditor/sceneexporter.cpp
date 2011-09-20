#include "sceneexporter.h"
#include <fstream>

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
    }

    // cameras
    // scene graph

    out.reset();

    return true;
}
