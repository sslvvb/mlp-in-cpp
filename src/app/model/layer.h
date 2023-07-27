#ifndef CPP7_MLP_0_SRC_MODEL_LAYER_H_
#define CPP7_MLP_0_SRC_MODEL_LAYER_H_

#include "neuron.h"

namespace s21 {

class Layer {
 public:
  Layer(int layer_size, int weight_size);
  ~Layer() {}

  int get_layer_size();
  int get_weight_size();

  void set_neuron_value(int i, double value);
  void set_neuron_weight(int i, int w, double value);
  void set_nueron_bias(int i, double value);
  void set_neuron_error(int i, double error);

  double get_neuron_value(int i);
  double get_neuron_weight(int i, int w);
  double get_neuron_bias(int i);
  double get_neuron_error(int i);

  void VectorToLayerNeuronValue(std::vector<double>);
  std::vector<double> LayerNeuronValueToVector();

 private:
  std::vector<Neuron> layer_;
  int layer_size_;
  int weight_size_;
};

}  // namespace s21

#endif  // CPP7_MLP_0_SRC_MODEL_LAYER_H_
