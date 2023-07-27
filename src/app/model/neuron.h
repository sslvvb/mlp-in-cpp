#ifndef CPP7_MLP_0_SRC_MODEL_NEURON_H_
#define CPP7_MLP_0_SRC_MODEL_NEURON_H_

#include <random>

namespace s21 {

class Neuron {
 public:
  Neuron(int next_layer_size);
  ~Neuron() {}

  void set_neuron_value(double value) { value_ = value; }
  void set_neuron_weight(int i, double value) { weights_[i] = value; }
  void set_error(double error) { error_ = error; }
  void set_bias(double bias) { bias_ = bias; }

  double get_neuron_weight(int i) { return weights_[i]; }
  double get_neuron_bias() { return bias_; }
  double get_neuron_value() { return value_; }
  double get_error() { return error_; }

 private:
  std::vector<double> weights_{};
  double bias_{};
  double value_{};
  double error_{};

  double GenerateRandomWeight();
};

}  // namespace s21

#endif  // CPP7_MLP_0_SRC_MODEL_NEURON_H_
