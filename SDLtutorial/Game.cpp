#include "Game.h"
#include <iostream>
#include "Constants.h"
#include "TransformComponent.h"
#include "KeyboardControlComponent.h"
#include "SpriteComponent.h"
#include "AssetManager.h"



EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;
SDL_Surface* Game::screenSurface;
SDL_Window* Game::window;
SDL_Event Game::event;

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
	
	assetManager->AddTexture("tank-image", std::string("./assets/images/tank-big-right.png").c_str());
	assetManager->AddTexture("chopper-image", std::string("./assets/images/chopper-spritesheet.png").c_str());
	assetManager->AddTexture("radar-image", std::string("./assets/images/radar.png").c_str());

	//include entities and components
	Entity& chopperEntity(manager.AddEntity("chopper"));
	chopperEntity.AddComponent<TransformComponent>(vi2d{ 240, 105 }, vi2d{ 0, 0 }, 32, 32, 1);
	chopperEntity.AddComponent<SpriteComponent>("chopper-image", 2, 90, true, false);
	chopperEntity.AddComponent<KeyboardControlComponent>("up", "right", "down", "left","shoot");

    Entity& tankEntity(manager.AddEntity("tank"));
    tankEntity.AddComponent<TransformComponent>(vi2d{ 0,0 }, vi2d{ 20,20 }, 32, 32, 1);
	tankEntity.AddComponent<SpriteComponent>("tank-image");



	Entity& raderEntity(manager.AddEntity("Radar"));
	raderEntity.AddComponent<TransformComponent>(vi2d{ 720,15 }, vi2d{ 0,0 }, 64, 64, 1);
	raderEntity.AddComponent<SpriteComponent>("radar-image", 8, 150, false, true);
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
	
	

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return;
	}
	
	LoadLevel(0);

	isRunning = true;
	return; 

}

void Game::ProcessInput()
{
	
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
