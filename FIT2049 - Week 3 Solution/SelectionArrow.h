#ifndef SELECTIONARROW_A
#define SELECTIONARROW_A

#include "Mesh.h"

class SelectionArrow {

private:
	Vector3 m_arrowPos;
	Matrix m_arrowMatrix;
	Texture* m_arrowTexture;

public:

	SelectionArrow();
	~SelectionArrow();

	void SetArrowMatrix(Matrix& worldIn);
	void SetArrowTexture();
	void UpdateArrowPos(float xIn, float zIn);
	void UpdateArrowMatrix(Matrix& worldIn);
	Vector3 GetArrowPos();
	Matrix GetArrowMatrix();
	Texture* GetArrowTexture();
};

#endif