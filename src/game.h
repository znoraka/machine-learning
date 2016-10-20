#pragma once

class Bird {
private:
  float x;

  float gravity = 1.0f;

  float upspeed = 0;

  float slowDown = 1.0f;

  Network *network;
  
public:
  bool alive = true;
  float y;
  int score = 0;

  void draw();
  Network *getNetwork();
  void setNetwork(Network *network);
  void jump();
  int getScore();
  void update();
  Bird(float x, float y);

};

class Pipe {
private:
  float x, yTop, yBot;

public:
  void draw();
  void update();
  void init(float x, float yTop);
  float getX();
  float getYTop();
  float getYBot();
  Pipe(float x, float yTop);
};

class Game {
private:
  std::vector<Bird*> birds;

  Pipe *pipe1, *pipe2;  
public:
  int bestScore = 0;
  int score = 0;
  void update();
  Game();

  int aliveBirds = 50;
  int generation = 0;

  Pipe *getPipe1();
  Pipe *getPipe2();
  void connectNetworks(std::vector<Network*> network);

};

static Game *game = new Game();

Bird::Bird(float x, float y) : x(x), y(y) {
  
}

Pipe::Pipe(float x, float yTop) {
  init(x, yTop);
}

void Pipe::init(float x, float yTop) {
  this->x = x;
  this->yTop = yTop;
  this->yBot = yTop + 4;
}

void Bird::draw() {
  if(alive)
    mvprintw(y, x, "0>");
}

void Pipe::draw() {
  for (int i = 0; i < yTop; i++) {
    mvprintw(i, x, "||||||||");
  }

  for (int i = yBot; i < 50; i++) {
    mvprintw(i, x, "||||||||");
  }
}

int Bird::getScore() {
  return score;
}

void Pipe::update() {
  x--;
}

float Pipe::getX() {
  return this->x;
}

float Pipe::getYTop() {
  return this->yTop;
}

float Pipe::getYBot() {
  return this->yBot;
}


void Bird::jump() {
  upspeed = -1;
}

void Bird::update() {
  if(alive) {
    y += gravity + ((upspeed < 0) ? -2 : 0);

    if(upspeed <= 0) 
      upspeed += slowDown;
  
    score++;

    if(game->getPipe1()->getX() <= 2 && game->getPipe1()->getX() > -1 && (y > game->getPipe1()->getYBot() || y < game->getPipe1()->getYTop())) {
      this->alive = false;
      game->aliveBirds--;
    }

    network->compute();
    if(network->getOutputs()[0]->getOutput() > 0.5) {
      jump();
    }
  }
}

Game::Game() {
  pipe1 = new Pipe(55, std::rand() % 10 + 5);
  pipe2 = new Pipe(95, std::rand() % 10 + 5);

  for (int i = 0; i < 50; i++) {
    birds.push_back(new Bird(1, std::rand() % 20 + 5));
  }
}

Pipe *Game::getPipe1() {
  return pipe1;
}

Pipe *Game::getPipe2() {
  return pipe2;
}

void Game::update() {
  score++;
  pipe1->update();
  pipe2->update();

  pipe1->draw();
  pipe2->draw();

  if(pipe1->getX() <= -5) {
    Pipe *tmp = pipe1;
    pipe1 = pipe2;
    pipe2 = tmp;
    pipe2->init(pipe1->getX() + 40, std::rand() % 20 + 2);
  }

  for(auto i : birds) {
    i->update();
    i->draw();
    i->getNetwork()->setInputs({i->y, pipe1->getYBot()});
  }

  if(aliveBirds == 0) {
    score = 0;
    generation++;
    pipe1->init(55, std::rand() % 20 + 2);
    pipe2->init(95, std::rand() % 20 + 2);
    aliveBirds = 50;
    int bestScore = 0;
    int index = 0;		  

    for (int i = 0; i < birds.size(); i++) {
      birds[i]->alive = true;
      birds[i]->y = std::rand() % 20 + 5;
      if(birds[i]->getScore() > bestScore) {
	bestScore = birds[i]->getScore();
	index = i;
      }
    }

    if(bestScore > this->bestScore)
      this->bestScore = bestScore;

    for (int i = 0; i < birds.size(); i++) {
      birds[i]->score = 0;
      if(i != index) {
	birds[i]->getNetwork()->copyNetworkValues(birds[index]->getNetwork());
	birds[i]->getNetwork()->mutate(0.005f);
      }
    }
  }

  mvprintw(0, 0, "score = %d", score);
  mvprintw(1, 0, "alive = %d", aliveBirds);
  mvprintw(2, 0, "generation = %d", generation);
}

void Game::connectNetworks(std::vector<Network*> networks) {
  for (int i = 0; i < networks.size(); i++) {
    birds[i]->setNetwork(networks[i]);
  }
}

void Bird::setNetwork(Network *network) {
  this->network = network;
}

Network *Bird::getNetwork() {
  return this->network;
}

