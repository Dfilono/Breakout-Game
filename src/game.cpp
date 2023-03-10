#include "game.h"
#include "resource_manager.h"
#include "sprite_render.h"
#include "game_object.h"
#include "ball_collisions.h"

// Game-related State data
SpriteRenderer  *Renderer;
GameObject *Player;

Game::Game(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height){

    }

Game::~Game(){
    delete Renderer;
    delete Player;
}

// Initial velocity of the Ball
const glm::vec2 INITIAL_BALL_VELCOITY(100.0f, -350.0f);

// radius of the ball object
const float BALL_RADIUS = 12.5f;

BallObject *Ball;

void Game::Init(){
    // load shaders
    ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");

    // configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width), 
        static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

    // set render-specific controls
    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

    // load textures
    ResourceManager::LoadTexture("textures/background.jpg", false, "background");
    ResourceManager::LoadTexture("textures/awesomeface.png", true, "face");
    ResourceManager::LoadTexture("textures/block.png", false, "block");
    ResourceManager::LoadTexture("textures/block_solid.png", false, "block_solid");
    ResourceManager::LoadTexture("textures/paddle.png", true, "paddle");

    // load levels
    GameLevel one; one.Load("levels/one.level", this->Width, this->Height /2);
    GameLevel two; two.Load("levels/two.level", this->Width, this->Height /2);
    GameLevel three; three.Load("levels/three.level", this->Width, this->Height /2);
    GameLevel four; four.Load("levels/four.level", this->Width, this->Height /2);
    
    this->Levels.push_back(one);
    this->Levels.push_back(two);
    this->Levels.push_back(three);
    this->Levels.push_back(four);
    this->Level = 0;

    // configure game objects
    glm::vec2 playerPos = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height - PLAYER_SIZE.y);
    Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));

    // load ball
    glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -BALL_RADIUS * 2.0f);
    Ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELCOITY, ResourceManager::GetTexture("face"));
}

void Game::Update(float dt){
    Ball->Move(dt, this->Width);
}

void Game::ProcessInput(float dt){
    if (this->State == GAME_ACTIVE){
        float velocity = PLAYER_VELOCITY * dt;
        
        // move playerboard
        if (this->Keys[GLFW_KEY_A]){
            if (Player->Position.x >= 0.0f){
                Player->Position.x -= velocity;
                
                if (Ball->Stuck){
                    Ball->Position.x -= velocity;
                }
            }
        }
        if (this->Keys[GLFW_KEY_D]){
            if (Player->Position.x <= this->Width - Player->Size.x){
                Player->Position.x += velocity;

                if (Ball->Stuck){
                    Ball->Position.x += velocity;
                }
            }
        }
        if (this->Keys[GLFW_KEY_SPACE]){
            Ball->Stuck = false;
        }
    }
}

void Game::Render(){
    if (this->State == GAME_ACTIVE){
        // draw background
        Renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f);

        // draw level
        this->Levels[this->Level].Draw(*Renderer);

        // draw player
        Player->Draw(*Renderer);

        // draw ball
        Ball->Draw(*Renderer);
    }
}