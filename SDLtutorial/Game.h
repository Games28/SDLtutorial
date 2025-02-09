
#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Entity.h"
#include "Component.h"
#include "EntityManager.h"




class AssetManager;


class Game
{
public:
	Game();
	~Game();
	static SDL_Renderer* renderer;
	static AssetManager* assetManager;
	static SDL_Window* window;
	static SDL_Surface* screenSurface;
	static SDL_Event event;
	static SDL_Rect camera;
	void LoadLevel(int levelNumber);
	bool IsRunning() const;
	void Initialize(int width, int height);
	void ProcessInput();
	void Update();
	void Render();
	void Destroy();
	void HandleCameraMovement();
	void CheckCollisions();
	void ProcessNextLevel(int levelNumber);
	void ProcessGameOver();
	int ticksLastFrame;
	
private:
	bool isRunning;
	
	
};

#endif // !GAME_H