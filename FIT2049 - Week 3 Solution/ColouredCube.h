/*
 * ColouredCube.h
 * Created by M. Skelley
 */

#ifndef COLOUREDCUBE_H
#define COLOUREDCUBE_H

#include "Mesh.h"

class ColouredCube {

private:
	Mesh* m_mesh;
	Shader* m_shader;

	Matrix m_cubeMatrix;
	Texture* m_colourCubeTexture;

	float xPos;
	float yPos;

public:

	ColouredCube();
	ColouredCube(Mesh* mesh, Shader* shader, float xPosIn, float yPosIn);
	~ColouredCube();

	void Render(Direct3D* render, Camera* currentCamera);

	void SetMatrixCube(Matrix& worldIn);
	void SetCubeTexture(const char* identifier);
	void SetMeshToNULL();
	Matrix GetMatrixCube();
	Texture* GetCubeTexture();
	Mesh* GetMesh();

	float GetXPos();
	float GetYPos();

};

#endif