/*	FIT2049 - Example Code
*	Game.h
*	Created by Elliott Wilson & Mike Yeates - 2016 - Monash University
*	This class is the heart of our game and is also where our game logic will reside
*	It contains the overall Update and Render method for the whole game
*	You should eventually split some game logic into other objects which Game will manage
*	Watch the size of this class - it can grow out of control very fast!
*/

#ifndef GAME_H
#define GAME_H

#include "Direct3D.h"
#include "InputController.h"
#include "Mesh.h"
#include "Camera.h"
#include "Button.h"
#include "TexturedShader.h"

#include "ColouredCube.h"
#include "SelectionArrow.h"

#include "DirectXTK/SpriteBatch.h"
#include "DirectXTK/SpriteFont.h"

#include <vector>
#include <algorithm>

class Game
{
private:

	int m_rows;
	int m_columns;

	Camera* m_currentCam;		
	Direct3D* m_renderer;
	InputController* m_input;

	// These are to draw sprites and text over our game. We'll talk about this next week.
	SpriteBatch* m_spriteBatch;
	SpriteFont* m_arialFont;
	
	Shader* m_unlitShader;
	Shader* m_texturedShader;

	Texture* m_blueCubeTexture;
	Texture* m_selectionArrowTexture;
	Texture* m_blueNextSprite;
	Texture* m_colourNextSprite;

	const char* m_identifierArray;
	const char* m_nextColour;
	const char* m_nextCubeColour;

	Mesh* m_cube;
	Matrix m_cubeMatrix;
	Vector3 m_cubePos;
	float m_moveSpeed;

	// Create a ColouredCube to test
	ColouredCube* m_testCube;

	// Create an array of ColouredCube pointers
	ColouredCube* m_testCubeArray[5];

	// Matrix of ColouredCube pointers
	ColouredCube* m_testCubeMatrix[10][10];

	// Create a SelectionArrow to test
	SelectionArrow* m_testArrow;

	// m_cubeArray will store the Mesh objects for each of the coloured blocks
	Mesh* m_cubeArray[5];
	Mesh* m_arrow;

	// m_textureArray stores the identifiers for different available colours
	std::vector<const char*> m_textureArray;
	std::vector<const char*> m_nextColourArray;

	// Splitting initialisation up into several steps
	bool InitShaders();
	bool LoadTextures();
	bool LoadMeshes();
	void LoadFonts();
	void InitUI();

	void DrawUI();

	// Test our object
	void TestColouredCube();

	// Start my new Exercise methods
	void Exercise1(Matrix & world, float timestep);

	// Check if the player has changes the colour
	void CheckForColourChange();

	// When the player changes the colour of a square
	void ExecuteColourChange();

public:
	Game();	
	~Game();

	bool Initialise(Direct3D* renderer, InputController* input); //The initialise method loads all of the content for the game (meshes, textures, etc.)

	void Update(float timestep);	//The overall Update method for the game. All gameplay logic will be done somewhere within this method
	void Render();					//The overall Render method for the game. Here all of the meshes that need to be drawn will be drawn

	// Responsible for updating the arrow matrix on user input
	void UpdateArrowMatrix();
	
	void Shutdown(); //Cleanup everything we initialised

	void UpdateAdjacentSquares(); // Checks if adjacent squares are the same colour and removes them if they are
};

#endif