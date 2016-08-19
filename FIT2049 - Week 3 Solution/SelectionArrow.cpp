#include "SelectionArrow.h"

SelectionArrow::SelectionArrow() {

	m_arrowPos = Vector3(0.0,0.0,0.0);
	m_arrowMatrix = Matrix::Identity;

	SetArrowMatrix(m_arrowMatrix);
	SetArrowTexture();
}

SelectionArrow::~SelectionArrow() {}

void SelectionArrow::SetArrowMatrix(Matrix& worldIn) {

	worldIn = Matrix::CreateTranslation(m_arrowPos);
}

void SelectionArrow::SetArrowTexture() {

	m_arrowTexture = Texture::GetTexture("SelectionArrowTexture");
}

Vector3 SelectionArrow::GetArrowPos() {

	return m_arrowPos;
}

Matrix SelectionArrow::GetArrowMatrix() {

	return m_arrowMatrix;
}

Texture* SelectionArrow::GetArrowTexture() {

	return m_arrowTexture;
}

void SelectionArrow::UpdateArrowPos(float xIn, float zIn) {

	m_arrowPos.x += xIn;
	m_arrowPos.z += zIn;

	UpdateArrowMatrix(m_arrowMatrix);

}

void SelectionArrow::UpdateArrowMatrix(Matrix& worldIn) {

	worldIn = Matrix::CreateTranslation(m_arrowPos);
}