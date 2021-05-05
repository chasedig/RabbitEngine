#include <RBT/graphics/AssetLoader.h>
#include <RBT/graphics/Mesh.h>
#include <assimp/Importer.hpp>
#include <iostream>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

using namespace RBT;

Mesh* RBT::AssetLoader::LoadMeshFromPath(std::string filepath)
{
	Mesh* mesh = new Mesh();

	Assimp::Importer importer;

	const aiScene* m_scene = importer.ReadFile(filepath.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

	if (!m_scene)
	{
		std::cout << "Scene failed to load for mesh of filepath: " + filepath << std::endl;
		return nullptr;
	}

	std::vector<Vertex> verticesTemp;

	const int meshCount = m_scene->mNumMeshes;
	const aiVector3D aZeroV3 = aiVector3D(0.0f, 0.0f, 0.0f);

	for (int m_idx = 0; m_idx < meshCount; m_idx++)
	{
		aiMesh* mMesh = m_scene->mMeshes[m_idx];
		for (int v = 0; v < mMesh->mNumVertices; v++)
		{
			const aiVector3D* vPos = &mMesh->mVertices[v];
			const aiVector3D* vNormal = &mMesh->mNormals[v] ? &mMesh->mNormals[v] : &aZeroV3;
			const aiVector3D* vTexCoord = mMesh->HasTextureCoords(0) ? &mMesh->mTextureCoords[0][v] : &aZeroV3;

			Vertex vertex = Vertex(
				glm::vec3(vPos->x, vPos->y, vPos->z),
				glm::vec3(vNormal->x, vNormal->y, vNormal->z),
				glm::vec2(vTexCoord->x, vTexCoord->y)
			);

			verticesTemp.push_back(vertex);
		}

		for (int face_idx = 0; face_idx < mMesh->mNumFaces; face_idx++)
		{
			const aiFace* face = &mMesh->mFaces[face_idx];
			for (int faceIndice = 0; faceIndice < face->mNumIndices; faceIndice++)
			{
				if (face->mNumIndices == 3)
				{
					mesh->indices.push_back(face->mIndices[faceIndice]);
				}
			}
		}
	}

	mesh->vertices = verticesTemp;
	return mesh;
}
