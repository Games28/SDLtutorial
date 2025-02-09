#include "Game.h"
#include <iostream>
#include "Constants.h"
#include "TransformComponent.h"
#include "KeyboardControlComponent.h"
#include "SpriteComponent.h"
#include "ColliderComponent.h"
#include "TextLabelComponent.h"
#include "AssetManager.h"
#include "ProjectileEmitterComponent.h"
#include "Map.h"



EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;
SDL_Surface* Game::screenSurface;
SDL_Window* Game::window;
SDL_Event Game::event;
SDL_Rect Game::camera = { 0,0,WINDOW_WIDTH,WINDOW_HEIGHT };
Map* map;

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
	assetManager->AddTexture("jungle-tiletexture", std::string("jungle.png").c_str());
	assetManager->AddTexture("hellport-image",  std::string("./assets/images/heliport.png").c_str());
	assetManager->AddTexture("projectile-image", std::string("./assets/images/bullet-enemy.png").c_str());
	assetManager->AddFont("charriot-font", std::string("./assets/fonts/charriot.ttf").c_str(),14);

	map = new Map("jungle-tiletexture", 2, 32);
	map->LoadMap("jungle.map", 25, 20);

	//include entities and components
	Entity& player(manager.AddEntity("chopper", PLAYER_LAYER));
	player.AddComponent<TransformComponent>(vi2d{ 240, 105 }, vi2d{ 0, 0 }, 32, 32, 1);
	player.AddComponent<SpriteComponent>("chopper-image", 2, 90, true, false);
	player.AddComponent<KeyboardControlComponent>("up", "right", "down", "left","shoot");
	player.AddComponent<ColliderComponent>("player", 240,105,32,32);

    Entity& tankEntity(manager.AddEntity("tank",ENEMY_LAYER));
    tankEntity.AddComponent<TransformComponent>(vi2d{ 150,495 }, vi2d{ 0,0 }, 32, 32, 1);
	tankEntity.AddComponent<SpriteComponent>("tank-image");
	tankEntity.AddComponent<ColliderComponent>("enemy", 150, 495,32,32);

	Entity& projectile(manager.AddEntity("projectile", PROJECTILE_LAYER));
	projectile.AddComponent<TransformComponent>(vi2d{ 150 + 16,495 + 16 }, vi2d{ 0,0 }, 4, 4, 1);
	projectile.AddComponent<SpriteComponent>("projectile-image");
	projectile.AddComponent<ColliderComponent>("projectile", 150 + 16, 495 + 16, 4, 4);
	projectile.AddComponent<ProjectileEmitterComponent>(50,270,200,true);


	Entity& hellport(manager.AddEntity("hellport", OBSTACLE_LAYER));
	hellport.AddComponent<TransformComponent>(vi2d(470, 420),vi2d( 0, 0), 32, 32,1);
	hellport.AddComponent<SpriteComponent>("hellport-image");
	hellport.AddComponent<ColliderComponent>("level_complete", 470, 420, 32, 32);



	Entity& raderEntity(manager.AddEntity("Radar",UI_LAYER));
	raderEntity.AddComponent<TransformComponent>(vi2d{ 720,15 }, vi2d{ 0,0 }, 64, 64, 1);
	raderEntity.AddComponent<SpriteComponent>("radar-image", 8, 150, false, true);

	Entity& labelLevelName(manager.AddEntity("LabelLevelName", UI_LAYER));
	labelLevelName.AddComponent<TextLabelComponent>(10, 10, "first level...", "charriot-font", WHITE_COLOR);
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

	if (TTF_Init() != 0)
	{
		std::cerr << "error init ttf" << std::endl;
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
	
	HandleCameraMovement();
	
	CheckCollisions();
}

void Game::HandleCameraMovement()
{
	Entity* player = manager.GetEntity("chooper",PLAYER_LAYER);

	TransformComponent* mainPlayerTransform = player->GetComponent<TransformComponent>();

	camera.x = mainPlayerTransform->position.x - (WINDOW_WIDTH / 2);
	camera.y = mainPlayerTransform->position.y - (WINDOW_HEIGHT / 2);

	camera.x = camera.x < 0 ? 0 : camera.x;
	camera.y = camera.y < 0 ? 0 : camera.y;

	camera.x = camera.x > camera.w ? camera.w : camera.x;
	camera.y = camera.y > camera.h ? camera.h : camera.y;
}

void Game::CheckCollisions()
{
	CollisionType collisionType = manager.CheckCollisions();
	if (collisionType == PLAYER_ENEMY_COLLISION)
	{
		ProcessGameOver();
	}

	if (collisionType == PLAYER_LEVEL_COMPLETE_COLLISION)
	{
		ProcessNextLevel(1);
	}

	if (collisionType == PLAYER_PROJECTILE_COLLISION)
	{
		ProcessGameOver();
	}

}

void Game::ProcessNextLevel(int levelNumber)
{
	std::cout << "next Level" << std::endl;
	isRunning = false;
}

void Game::ProcessGameOver()
{
	std::cout << "Game Over" << std::endl;
	isRunning = false;
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


