#include "Game.h"
#include <iostream>
#include "Constants.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "AssetManager.h"


EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;
SDL_Surface* Game::screenSurface;
SDL_Window* Game::window;

Game::Game()
{
	this->isRunning = false;
	this->ticksLastFrame = 0;
}

Game::~Game()
{

}

void Game::LoadLevel(int levelNumber)
{
	// include new  assets to assetmanager
	std::string textureFilePath = "./assets/images/tank-big-right.bmp";
	assetManager->AddTexture("tank-image", textureFilePath.c_str());


	//include entities and components
Entity& newEntity(manager.AddEntity("tank"));
    newEntity.AddComponent<TransformComponent>(vi2d{ 0,0 }, vi2d{ 20,20 }, 32, 32, 1);
	newEntity.AddComponent<SpriteComponent>("tank-image");
}

bool Game::IsRunning() const
{
	return this->isRunning;
}



void Game::Initialize(int width, int height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cerr << "error init sdl." << std::endl;
		return;
	}

	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_BORDERLESS
	);

	if (!window)
	{
		std::cerr << "error creating sdl window." << std::endl;
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);

	if (!renderer)
	{
		std::cerr << "error creating sdl renderer." << std::endl;
		return;
	}
	
	//SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	//
	//if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
	//
	//	printf("Failed to init sdl_image");
	//	return;
	//}
	//int imgFlags = IMG_INIT_PNG;
	//if (!(IMG_Init(imgFlags) & imgFlags))
	//{
	//	printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
	//	return;
	//}
	
	LoadLevel(0);

	isRunning = true;
	return;

}

void Game::ProcessInput()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			isRunning = false;

		}

	default:
		break;
	}
}

void Game::Update()
{
	int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - ticksLastFrame);
	if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME)
	{
		SDL_Delay(timeToWait);
	}
	//while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME ));
	float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;
	
	deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;
	
	ticksLastFrame = SDL_GetTicks();
	
	manager.Update(deltaTime); 
	
	

}

void Game::Render()
{
	SDL_SetRenderDrawColor(renderer, 0, 100, 255, 255);
	SDL_RenderClear(renderer);

	if (manager.HasNoEntities())
		return;

	manager.Render();

	SDL_RenderPresent(renderer);
}

void Game::Destroy()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
