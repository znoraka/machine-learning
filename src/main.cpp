#include <iostream>
#include <functional>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <ncurses.h>
#include <chrono>
#include <thread>
#include "neuron.h"
#include "network.h"
#include "game.h"

int main(int argc, char **argv) {
  std::srand(std::time(0));

  std::vector<int> dimensions{2, 4, 1};
  std::vector<Network*> networks;

  for (int i = 0; i < 50; i++) {
    networks.push_back(new Network(dimensions));
  }

  for(auto i : networks) {
    i->compute();
  }

  initscr();
  cbreak();
  printw("hello world");
  game->connectNetworks(networks);
  for(;;) {
    refresh();
    game->update();
    refresh();
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    clear();
  }

  /*******************/
  // std::vector<std::vector<float> > inputs = {{0, 0, 1}, {1, 1, 1}, {1, 0, 1}, {0, 1, 1}};
  // std::vector<std::vector<float> > outputs  {{0}, {1}, {1}, {0}};
  // int bestNetworkIndex = 0;
  // float bestNetworkScore = 9999999999;
  
  // for (int i = 0; i < 1000 && bestNetworkScore != 0; i++) {
  //   // std::cout << "iteration : " << i << " --- " << "best score = " << bestNetworkScore << "\n";
  //   for (int k = 0; k < networks.size(); k++) {
  //     float score = 0;
  //     for (int j = 0; j < inputs.size(); j++) {
  // 	networks[k]->setInputs(inputs[j]);
  // 	networks[k]->compute();
  // 	score +=  fabs(networks[k]->getOutputs()[0]->getOutput() - outputs[j][0]);
  //     }
  //     if(score < bestNetworkScore) {
  // 	bestNetworkScore = score;
  // 	bestNetworkIndex = k;
  //     }
  //   }
  //   for (int a = 0; a < networks.size(); a++) {
  //     if(i != bestNetworkIndex) {
  // 	networks[a]->copyNetworkValues(networks[bestNetworkIndex]);
  // 	networks[a]->mutate(0.05f);
  //     }
  //   }
  // }
  /*******************/
  
  
  // std::vector<std::vector<float> > inputs = {{0, 0, 1}, {1, 1, 1}, {1, 0, 1}, {0, 1, 1}};
  // std::vector<std::vector<float> > outputs  {{0}, {1}, {1}, {0}};

  // std::vector<std::vector<float> > inputs = {{0, 0, 1}, {1, 1, 1}, {0, 1, 1}, {0, 0, 1}};
  // std::vector<std::vector<float> > outputs  {{0}, {1}, {1}, {0}};

  // std::vector<std::vector<float> > inputs = {{0, 0, 0}, {1, 1, 1}, {0, 1, 1}, {0, 1, 0}};
  // std::vector<std::vector<float> > outputs  {{0}, {1}, {1}, {0}};

  // networks[bestNetworkIndex]->setInputs({1, 0, 0});
  // networks[bestNetworkIndex]->compute();
  // std::cout << "result = " << networks[bestNetworkIndex]->getOutputs()[0]->getOutput() << "\n";
  endwin();
}
