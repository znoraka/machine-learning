#include <iostream>
#include <functional>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include "neuron.h"
#include "network.h"

int main(int argc, char **argv) {
  std::srand(std::time(0));
  // std::srand(1);

  std::vector<int> dimensions{3, 4, 1};
  std::vector<Network*> networks;

  for (int i = 0; i < 50; i++) {
    networks.push_back(new Network(dimensions));
  }

  for(auto i : networks) {
    i->compute();
  }

  std::vector<std::vector<float> > inputs = {{0, 0, 1}, {1, 1, 1}, {1, 0, 1}, {0, 1, 1}};
  std::vector<std::vector<float> > outputs  {{0}, {1}, {1}, {0}};

  int bestNetworkIndex = 0;
  float bestNetworkScore = 999;
  
  for (int i = 0; i < 10000 && bestNetworkScore != 0; i++) {
    for (int k = 0; k < networks.size(); k++) {
      float score = 0;
      for (int j = 0; j < inputs.size(); j++) {
  	networks[k]->setInputs(inputs[j]);
  	networks[k]->compute();
  	score +=  fabs(networks[k]->getOutputs()[0]->getOutput() - outputs[j][0]);
      }
      if(score < bestNetworkScore) {
  	bestNetworkScore = score;
  	bestNetworkIndex = k;
      }
    }
    for (int i = 0; i < networks.size(); i++) {
      if(i != bestNetworkIndex) {
  	networks[i]->copyNetworkValues(networks[bestNetworkIndex]);
  	networks[i]->mutate(0.05f);
      }
    }
      
  }

  
  // Network n(dimensions);
  // n.setInputs(inputs[0]);
  // n.compute();
  // std::cout << "output = " << n.getOutputs()[0]->getOutput() << "\n";

  // for (int i = 0;; i++) {
  //   n.mutate(0.1f);
  //   n.compute();
  //   std::cout << "output = " << n.getOutputs()[0]->getOutput() << "          " << "\r";
  // }

  // std::vector<std::vector<float> > inputs = {{0, 0, 1}, {1, 1, 1}, {1, 0, 1}, {0, 1, 1}};
  // std::vector<std::vector<float> > outputs  {{0}, {1}, {1}, {0}};

  // std::vector<std::vector<float> > inputs = {{0, 0, 1}, {1, 1, 1}, {0, 1, 1}, {0, 0, 1}};
  // std::vector<std::vector<float> > outputs  {{0}, {1}, {1}, {0}};

  // std::vector<std::vector<float> > inputs = {{0, 0, 0}, {1, 1, 1}, {0, 1, 1}, {0, 1, 0}};
  // std::vector<std::vector<float> > outputs  {{0}, {1}, {1}, {0}};


  // for (int i = 0; i < 100000; i++) {
  //   for (int j = 0; j < inputs.size(); j++) {
  //     n.train(inputs[j], outputs[j]);
  //   }
  //   // n.getOutputs()[0]->getOutput();
  // }

  networks[bestNetworkIndex]->setInputs({1, 1, 0});
  networks[bestNetworkIndex]->compute();
  std::cout << "result = " << networks[bestNetworkIndex]->getOutputs()[0]->getOutput() << "\n";
  
}
