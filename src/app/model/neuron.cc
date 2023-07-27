#include "neuron.h"

namespace s21 {

Neuron::Neuron(int next_layer_size) {
  for (int i = 0; i < next_layer_size; ++i) {
    weights_.push_back(GenerateRandomWeight());
  }
  bias_ = GenerateRandomWeight();
}

double Neuron::GenerateRandomWeight() {
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution<double> dist(0.5, -0.5);
  return dist(mt);
}

}  // namespace s21
