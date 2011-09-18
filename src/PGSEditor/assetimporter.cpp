#include "assetimporter.h"
#include <assimp/assimp.hpp>
#include <assimp/aiScene.h>
#include <assimp/aiPostProcess.h>

#include <QFile>
#include <QTextStream>

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

QString AssetImporter::getError() const
{
    return QString::fromStdString(importer->GetErrorString());
}

void AssetImporter::processScene(const aiScene *scene)
{
    QFile data("output.txt");

     if (data.open(QFile::WriteOnly | QFile::Truncate)) {
         QTextStream out(&data);

         out << "Meshes: " << scene->mNumMeshes << "\n";
         out << "Materials: " << scene->mNumMaterials << "\n";

         for(unsigned int i = 0; i < scene->mNumMeshes; ++i)
         {
             aiMesh* mesh = scene->mMeshes[i];

             out << "Mesh: " << i << "\n";
             out << "Vertices: " << mesh->mNumVertices << "\n";
             out << "Positions: " << mesh->HasPositions() << "\n";
             out << "Normals: " << mesh->HasNormals() << "\n";
             out << "TexCoords: " << mesh->HasTextureCoords(0) << "\n";
             out << "Tangents: " << mesh->HasTangentsAndBitangents() << "\n";
             out << "Bitangents: " << mesh->HasTangentsAndBitangents() << "\n";

             for(unsigned int v = 0; v < mesh->mNumVertices; ++v)
             {
                 out << "Vertex " << v << "\n";
                 out << "Position " << mesh->mVertices[v].x << " " << mesh->mVertices[v].y << " " << mesh->mVertices[v].z << "\n";
                 out << "Normal " << mesh->mNormals[v].x << " " << mesh->mNormals[v].y << " " << mesh->mNormals[v].z << "\n";
                 out << "TexCoord " << mesh->mTextureCoords[0][v].x << " " << mesh->mTextureCoords[0][v].y << "\n";
                 out << "Tangent " << mesh->mTangents[v].x << " " << mesh->mTangents[v].y << " " << mesh->mTangents[v].z << "\n";
                 out << "Bitangent " << mesh->mBitangents[v].x << " " << mesh->mBitangents[v].y << " " << mesh->mBitangents[v].z << "\n";
             }

             out << "Faces: " << mesh->mNumFaces << "\n";

             for(unsigned int f = 0; f < mesh->mNumFaces; ++f)
             {
                 aiFace& face = mesh->mFaces[f];

                 out << "Face " << f << "\n";
                 out << "Indexes: " << face.mNumIndices << "\n";

                 for(unsigned int j = 0; j < face.mNumIndices; ++j)
                 {
                     out << face.mIndices[j] << " ";
                 }

                 out << "\n";
             }
         }
     }
}
