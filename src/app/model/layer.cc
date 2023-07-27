#include "layer.h"

namespace s21 {

Layer::Layer(int layer_size, int weight_size)
    : layer_size_(layer_size), weight_size_(weight_size) {
  for (int i = 0; i < layer_size_; ++i) {
    Neuron neuron(weight_size_);
    layer_.push_back(neuron);
  }
}

int Layer::get_layer_size() { return layer_size_; }

int Layer::get_weight_size() { return weight_size_; }

void Layer::set_neuron_value(int i, double value) {
  layer_[i].set_neuron_value(value);
}

void Layer::set_neuron_weight(int i, int w, double value) {
  layer_[i].set_neuron_weight(w, value);
}

void Layer::set_nueron_bias(int i, double value) { layer_[i].set_bias(value); }

void Layer::set_neuron_error(int i, double error) {
  layer_[i].set_error(error);
}

double Layer::get_neuron_value(int i) { return layer_[i].get_neuron_value(); }

double Layer::get_neuron_weight(int i, int w) {
  return layer_[i].get_neuron_weight(w);
}

double Layer::get_neuron_bias(int i) { return layer_[i].get_neuron_bias(); }

double Layer::get_neuron_error(int i) { return layer_[i].get_error(); }

void Layer::VectorToLayerNeuronValue(std::vector<double> input_vector) {
  for (size_t i = 0; i < input_vector.size(); ++i) {
    layer_[i].set_neuron_value(input_vector[i]);
  }
}

std::vector<double> Layer::LayerNeuronValueToVector() {
  std::vector<double> res_vector;
  for (int i = 0; i < layer_size_; ++i) {
    res_vector.push_back(layer_[i].get_neuron_value());
  }
  return res_vector;
}

}  // namespace s21
