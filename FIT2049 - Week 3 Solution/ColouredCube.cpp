#include "ColouredCube.h"

ColouredCube::ColouredCube() {}

ColouredCube::ColouredCube(Mesh* mesh, Shader* shader, float xPosIn, float yPosIn) {

	m_mesh = mesh;
	m_shader = shader;

	xPos = xPosIn;
	yPos = yPosIn;
	m_cubeMatrix = Matrix::Identity;
	SetMatrixCube(m_cubeMatrix);
	//SetCubeTexture();
}

ColouredCube::~ColouredCube() {}

void ColouredCube::SetMatrixCube(Matrix& worldIn) {

	Vector3 vectorPos = Vector3::Zero;
	vectorPos.x += xPos;
	vectorPos.z += yPos;
	worldIn = Matrix::CreateTranslation(vectorPos);
}

void ColouredCube::SetCubeTexture(const char* identifier) {

	m_colourCubeTexture = Texture::GetTexture(identifier);
	//m_colourCubeTexture = textureIn;
}

void ColouredCube::SetMeshToNULL() {
	m_mesh = NULL;
}

Matrix ColouredCube::GetMatrixCube() {

	return m_cubeMatrix;
}

Texture* ColouredCube::GetCubeTexture() {

	return m_colourCubeTexture;
}

Mesh* ColouredCube::GetMesh() {
	return m_mesh;
}

void ColouredCube::Render(Direct3D* renderer, Camera* currentCamera) {

	if (m_mesh) {
		// Create our matrix using the vector positions we have input
		Vector3 vectorPos = Vector3::Zero;
		vectorPos.x += xPos;
		vectorPos.z += yPos;
		Matrix world = Matrix::CreateTranslation(vectorPos);

		m_mesh->Render(renderer, world, currentCamera, m_shader, m_colourCubeTexture);
	}

	
}

float ColouredCube::GetXPos() {
	return xPos;
}
float ColouredCube::GetYPos() {
	return yPos;
}

