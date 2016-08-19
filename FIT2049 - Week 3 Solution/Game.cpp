/*	FIT2049 - Example Code
*	Game.cpp
*	Created by Elliott Wilson & Mike Yeates - 2016 - Monash University
*/

#include "Game.h"
#include "DirectXTK/CommonStates.h"

Game::Game()
{
	m_renderer = NULL;
	m_currentCam = NULL;
	m_input = NULL;
	m_unlitShader = NULL;
	m_texturedShader = NULL;
	m_cube = NULL;
	m_spriteBatch = NULL;
	m_arialFont = NULL;

	m_cubeMatrix = Matrix::Identity;

	m_cubePos = Vector3::Zero;
	m_moveSpeed = 5.0f;

	// Initialise ColouredCube object pointer
	m_testCube = NULL;

	// Initialise SelectionArrow object pointer
	m_testArrow = NULL;

	// Initialise m_rows and m_columns
	m_rows = 10;
	m_columns = 10;

}

Game::~Game() {}

bool Game::Initialise(Direct3D* renderer, InputController* input)
{
	m_renderer = renderer;	
	m_input = input;

	if (!InitShaders())
		return false;

	if (!LoadTextures())
		return false;

	if (!LoadMeshes())
		return false;

	LoadFonts();
	InitUI();

	m_currentCam = new Camera();

	// Initialise the ColouredCube object pointer here
	//m_testCube = new ColouredCube(1.0,0.0);

	// Initialise the ColouredCube object pointer array
	/*
	float xPos = -2.0;
	for (int i = 0; i < 5; i++) {
		m_testCubeArray[i] = new ColouredCube(xPos,0.0);
		xPos += 1.0;
	}
	*/

	float xPos = -2.0;
	float zPos = -5.0;

	// Initialise m_testCubeMatrix with ColouredCube objects
	// The position is initialise here too
	for (int i = 0; i < m_rows; i++) {
		xPos = -5.0;
		for (int j = 0; j < m_rows; j++) {
			m_testCubeMatrix[i][j] = new ColouredCube(Mesh::GetMesh("GridCell"), m_texturedShader, xPos, zPos);
			m_testCubeMatrix[i][j]->SetCubeTexture(m_textureArray[std::rand() % m_textureArray.size()]);
			xPos += 1.0;
		}
		zPos += 1.0;
	}

	// Set ColouredCube texture
	//m_testCube->SetCubeTexture("CubeBlue");

	// Initialise the SelectionPointer object
	m_testArrow = new SelectionArrow();

	//Initialise the textures
	//m_blueCubeTexture = new Texture();

	// Initialise m_nextColour
	int nextColourIndex = std::rand() % m_textureArray.size();
	m_nextCubeColour = m_textureArray[nextColourIndex]; 
	m_nextColour = m_nextColourArray[nextColourIndex];

	return true;
}

bool Game::InitShaders()
{
	m_unlitShader = new Shader();
	if (!m_unlitShader->Initialise(m_renderer->GetDevice(), L"Assets/Shaders/VertexShader.vs", L"Assets/Shaders/VertexColourPixelShader.ps"))
	{
		return false;
	}

	m_texturedShader = new TexturedShader();
	if (!m_texturedShader->Initialise(m_renderer->GetDevice(), L"Assets/Shaders/VertexShader.vs", L"Assets/Shaders/TexturedPixelShader.ps"))
	{
		return false;
	}

	return true;
}

bool Game::LoadTextures()
{
	if (!Texture::LoadFromFile(L"Assets/Textures/Cube-Blue.png", "CubeBlue", m_renderer))
	{
		return false;
	}
	m_textureArray.push_back("CubeBlue");

	if (!Texture::LoadFromFile(L"Assets/Textures/Next-Blue.png", "NextBlue", m_renderer))
	{
		return false;
	}
	m_nextColourArray.push_back("NextBlue");
	m_blueNextSprite = Texture::GetTexture("NextBlue");

	if (!Texture::LoadFromFile(L"Assets/Textures/Cube-Green.png", "CubeGreen", m_renderer))
	{
		return false;
	}
	m_textureArray.push_back("CubeGreen");

	if (!Texture::LoadFromFile(L"Assets/Textures/Next-Green.png", "NextGreen", m_renderer))
	{
		return false;
	}
	m_nextColourArray.push_back("NextGreen");

	if (!Texture::LoadFromFile(L"Assets/Textures/Cube-Orange.png", "CubeOrange", m_renderer))
	{
		return false;
	}
	m_textureArray.push_back("CubeOrange");

	if (!Texture::LoadFromFile(L"Assets/Textures/Next-Orange.png", "NextOrange", m_renderer))
	{
		return false;
	}
	m_nextColourArray.push_back("NextOrange");

	if (!Texture::LoadFromFile(L"Assets/Textures/Cube-Red.png", "CubeRed", m_renderer))
	{
		return false;
	}
	m_textureArray.push_back("CubeRed");

	if (!Texture::LoadFromFile(L"Assets/Textures/Next-Red.png", "NextRed", m_renderer))
	{
		return false;
	}
	m_nextColourArray.push_back("NextRed");

	if (!Texture::LoadFromFile(L"Assets/Textures/Cube-Purple.png", "CubePurple", m_renderer))
	{
		return false;
	}
	m_textureArray.push_back("CubePurple");

	if (!Texture::LoadFromFile(L"Assets/Textures/Next-Purple.png", "NextPurple", m_renderer))
	{
		return false;
	}
	m_nextColourArray.push_back("NextPurple");

	if (!Texture::LoadFromFile(L"Assets/Textures/Cube-Black.png", "CubeBlack", m_renderer))
	{
		return false;
	}
	m_textureArray.push_back("CubeBlack");

	if (!Texture::LoadFromFile(L"Assets/Textures/Next-Black.png", "NextBlack", m_renderer))
	{
		return false;
	}
	m_nextColourArray.push_back("NextBlack");

	if (!Texture::LoadFromFile(L"Assets/Textures/Cube-Yellow.png", "CubeYellow", m_renderer))
	{
		return false;
	}
	m_textureArray.push_back("CubeYellow");

	if (!Texture::LoadFromFile(L"Assets/Textures/Next-Yellow.png", "NextYellow", m_renderer))
	{
		return false;
	}
	m_nextColourArray.push_back("NextYellow");

	if (!Texture::LoadFromFile(L"Assets/Textures/Cube-White.png", "CubeWhite", m_renderer))
	{
		return false;
	}
	m_textureArray.push_back("CubeWhite");

	if (!Texture::LoadFromFile(L"Assets/Textures/Next-White.png", "NextWhite", m_renderer))
	{
		return false;
	}
	m_nextColourArray.push_back("NextWhite");

	if (!Texture::LoadFromFile(L"Assets/Textures/Button.png", "ButtonWhite", m_renderer))
	{
		return false;
	}

	// Load the texture for the arrow
	if (!Texture::LoadFromFile(L"Assets/Textures/Selection-Arrow.png", "SelectionArrowTexture", m_renderer)) {

		return false;
	}

	m_blueCubeTexture = Texture::GetTexture("CubeBlue");

	// Apply the Arrow Texture
	m_selectionArrowTexture = Texture::GetTexture("SelectionArrowTexture");

	return true;
}

bool Game::LoadMeshes()
{
	if (!Mesh::LoadFromFile(L"Assets/Meshes/cube.obj", "GridCell", m_renderer))
	{
		return false;
	}

	// Load the mesh for the selection arrow form the file
	if (!Mesh::LoadFromFile(L"Assets/Meshes/Selection-Arrow.obj", "SelectionArrowMesh", m_renderer)) {
		return false;
	}

	m_cube = Mesh::GetMesh("GridCell");

	// Load in our Meshs to the m_cubeArray
	/*
	for (int i = 0; i < 5; i++) {
		m_cubeArray[i] = Mesh::GetMesh("GridCell");
	}
	*/

	//m_cube = Mesh::CreateTriangle(m_renderer, "Triangle");

	// Exercise 2
	//m_cube = Mesh::CreateSquare2D(m_renderer, "Square");

	// Create the mesh for our arrow
	m_arrow = Mesh::GetMesh("SelectionArrowMesh");

	// Test function for ColouredCube object
	TestColouredCube();


	return true;

}

void Game::LoadFonts()
{
	// There's a few different size fonts in there, you know
	m_arialFont = new SpriteFont(m_renderer->GetDevice(), L"Assets/Fonts/Arial-12pt.spritefont");
}

void Game::InitUI()
{
	m_spriteBatch = new SpriteBatch(m_renderer->GetDeviceContext());
}

void Game::Update(float timestep)
{
	m_input->BeginUpdate();

	// Execute our exercises here
	//Exercise1(m_cubeMatrix, timestep);

	UpdateArrowMatrix();

	CheckForColourChange();
	
	m_currentCam->Update(timestep);

	m_input->EndUpdate();
}

void Game::TestColouredCube() {

	// Initialise a vector shifted to the right along the x axis
	Vector3 testVector = Vector3::Zero;
}

// Exercise 1 from Tut 3
void Game::Exercise1(Matrix &world, float timestep) {

	if (m_input->GetKeyHold(VK_RIGHT)) {
		
		m_cubePos.x += m_moveSpeed * timestep;
	}
	else if (m_input->GetKeyHold(VK_LEFT)) {

		m_cubePos.x -= m_moveSpeed * timestep;
	}
	else if (m_input->GetKeyHold(VK_UP)) {
		m_cubePos.y += m_moveSpeed * timestep;
	}
	else if (m_input->GetKeyHold(VK_DOWN)) {
		m_cubePos.y -= m_moveSpeed * timestep;
	}

	world = Matrix::CreateTranslation(m_cubePos);
}

void Game::CheckForColourChange() {

	if (m_input->GetKeyUp(VK_SPACE)) {
		ExecuteColourChange();
	}
}

void Game::ExecuteColourChange() {

	// Get the position of the arrow
	Vector3 arrowPos = m_testArrow->GetArrowPos();

	// Change the colour of a square based on the position of the arrow
	int xCoord = (int)arrowPos.x + 5;
	int yCoord = (int)arrowPos.z + 5;

	m_testCubeMatrix[yCoord][xCoord]->SetCubeTexture(m_nextCubeColour);

	// Check and change the adjacent squares
	UpdateAdjacentSquares();

	// Now we need to generate a new colour
	int nextColourIndex = std::rand() % m_textureArray.size();
	m_nextCubeColour = m_textureArray[nextColourIndex];
	m_nextColour = m_nextColourArray[nextColourIndex];
}

void Game::UpdateArrowMatrix() {

	if (m_input->GetKeyDown(VK_RIGHT)) {
		Vector3 tmpVector = m_testArrow->GetArrowPos();
		if (m_testArrow->GetArrowPos().x < 4) {
			m_testArrow->UpdateArrowPos(1.0, 0.0);
		}
	}
	else if (m_input->GetKeyDown(VK_LEFT)) {
		if (m_testArrow->GetArrowPos().x > -5) {
			m_testArrow->UpdateArrowPos(-1.0, 0.0);
		}
	}
	else if (m_input->GetKeyDown(VK_UP)) {
		if (m_testArrow->GetArrowPos().z < 4) {
			m_testArrow->UpdateArrowPos(0.0, 1.0);
		}
	}
	else if (m_input->GetKeyDown(VK_DOWN)) {
		if (m_testArrow->GetArrowPos().z > -5) {
			m_testArrow->UpdateArrowPos(0.0, -1.0);
		}
	}
}

void Game::Render()
{
	m_renderer->BeginScene(0.2f, 0.2f, 0.2f, 1.0f);

	// Render a mesh, using a matrix, taking into account the camera position / projection settings, using a shader, and optionally using a texture
	//m_cube->Render(m_renderer, m_cubeMatrix, m_currentCam, m_unlitShader, NULL);

	// Here's an example of how to use our textured shader
	//m_cube->Render(m_renderer, m_cubeMatrix, m_currentCam, m_texturedShader, m_blueCubeTexture);

	// Test
	//m_cube->Render(m_renderer, m_testCube->GetMatrixCube(), m_currentCam, m_texturedShader, m_testCube->GetCubeTexture());

	/*
	for (int i = 0; i < 5; i++) {
		m_cube->Render(m_renderer, m_testCubeArray[i]->GetMatrixCube(), m_currentCam, m_texturedShader, m_testCubeArray[i]->GetCubeTexture());
	}
	*/

	for (int i = 0; i < m_rows; i++) {
		for (int j = 0; j < m_columns; j++) {
			//m_cube->Render(m_renderer, m_testCubeMatrix[i][j]->GetMatrixCube(), m_currentCam, m_texturedShader, m_testCubeMatrix[i][j]->GetCubeTexture());
			
			if (m_testCubeMatrix[i][j]) {
				m_testCubeMatrix[i][j]->Render(m_renderer, m_currentCam);
			}
		}
	}

	// Render the SelectionArrow
	m_arrow->Render(m_renderer, m_testArrow->GetArrowMatrix(), m_currentCam, m_texturedShader, m_testArrow->GetArrowTexture());


	DrawUI();

	m_renderer->EndScene();		

}

void Game::DrawUI()
{
	// Sprites and text (and buttons) will be explained in week 4

	// Sprites don't use a shader 
	m_renderer->SetCurrentShader(NULL);

	// Render Buttons and Fonts
	CommonStates states(m_renderer->GetDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, states.NonPremultiplied());

	// Do UI drawing in here

	// Here's how we draw a sprite over our game
	//m_blueNextSprite = Texture::GetTexture("NextBlue");
	m_colourNextSprite = Texture::GetTexture(m_nextColour);
	m_spriteBatch->Draw(m_colourNextSprite->GetShaderResourceView(), Vector2(20, 100), Color(1.0f, 1.0f, 1.0f));

	m_spriteBatch->End();
}

void Game::Shutdown()
{
	if (m_currentCam)
	{
		delete m_currentCam;
		m_currentCam = NULL;
	}

	if (m_unlitShader)
	{
		m_unlitShader->Release();
		delete m_unlitShader;
		m_unlitShader = NULL;
	}

	if (m_texturedShader)
	{
		m_texturedShader->Release();
		delete m_texturedShader;
		m_texturedShader = NULL;
	}

	if (m_cube)
	{
		// Decrements reference count and deletes mesh if nothing else is using it
		Mesh::ReleaseMesh(m_cube);
	}

	if (m_blueCubeTexture)
	{
		Texture::ReleaseTexture(m_blueCubeTexture);
	}

}

void Game::UpdateAdjacentSquares() {

	// Get the position of the arrow
	Vector3 position = m_testArrow->GetArrowPos();

	// Get the x and y coordinates
	// Need to change into the correct coordinates for the matrix array
	int xGridPos = (int)position.x + 5;
	int yGridPos = (int)position.z + 5;

	// Create a set of explored Cubes in the matrix
	std::vector<ColouredCube*> visitedCubes;

	// A vector to represent our stack
	std::vector<ColouredCube*> cubeStack;

	// A vector to represent all the cubes we are going to delete
	std::vector<ColouredCube*> colourGroupCubes;

	// Get the cube texture as a reference
	Texture* referenceTexture = m_testCubeMatrix[yGridPos][xGridPos]->GetCubeTexture();

	// Create a 
	cubeStack.push_back(m_testCubeMatrix[yGridPos][xGridPos]);

	// Our main while loop for the DFS
	while (!cubeStack.empty()) {

		// Get the value of the last item in the stack
		ColouredCube* currentCube = cubeStack[cubeStack.size()-1];

		//Remove the last item in the stack
		cubeStack.pop_back();

		// Get the colour of currentCube
		// If it is the same as currentTexure add the neighbours to the stack
		if (currentCube->GetCubeTexture() == referenceTexture && currentCube->GetMesh()) {

			// If the colour is correct then we can add it to the colourGroupCubes vector
			colourGroupCubes.push_back(currentCube);

			int xCoord = (int)currentCube->GetXPos() + 5;
			int yCoord = (int)currentCube->GetYPos() + 5;


			// For each direction, if not at an edge then check if the new cube is in visited
			// If not in visited then we add to the stack

			if (xCoord - 1 >= 0) {
				if (std::find(visitedCubes.begin(), visitedCubes.end(), (m_testCubeMatrix[yCoord][xCoord - 1])) == visitedCubes.end()) {
					cubeStack.push_back(m_testCubeMatrix[yCoord][xCoord - 1]);
				}
			}
			if (xCoord + 1 < 10) {
				if (std::find(visitedCubes.begin(), visitedCubes.end(), m_testCubeMatrix[yCoord][xCoord + 1]) == visitedCubes.end()) {
					cubeStack.push_back(m_testCubeMatrix[yCoord][xCoord + 1]);
				}
			}
			if (yCoord - 1 >= 0) {
				if (std::find(visitedCubes.begin(), visitedCubes.end(), m_testCubeMatrix[yCoord - 1][xCoord]) == visitedCubes.end()) {
					cubeStack.push_back(m_testCubeMatrix[yCoord - 1][xCoord]);
				}
			}
			if (yCoord + 1 < 10) {
				if (std::find(visitedCubes.begin(), visitedCubes.end(), m_testCubeMatrix[yCoord + 1][xCoord]) == visitedCubes.end()) {
					cubeStack.push_back(m_testCubeMatrix[yCoord + 1][xCoord]);
				}
			}
		}

		// Add the current cube to the visited stack
		visitedCubes.push_back(currentCube);
	}

	// TODO
	// Need to check that colourGroupCubes is at least 3
	// If it is then we can nullify all items in the vector
	if (colourGroupCubes.size() >= 3) {
		for (ColouredCube* cube : colourGroupCubes) {
			cube->SetMeshToNULL();
		}
	}

}