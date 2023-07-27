#include "graph_network.h"

namespace s21 {

// ______________ TRAINING ______________ //

void GraphNetwork::ImputToNetwork(std::vector<double> vector) {
  layers_[0].VectorToLayerNeuronValue(vector);
}

std::vector<double> GraphNetwork::OutputLayerToVector() {
  return layers_[data_storage_->get_hidden_layers() + 1]
      .LayerNeuronValueToVector();
}

void GraphNetwork::ForwardPropagation() {
  for (size_t l = 0; l < layers_.size() - 1; ++l) {
    for (int n = 0; n < layers_[l + 1].get_layer_size(); ++n) {
      double sum = 0;
      for (int w = 0; w < layers_[l].get_layer_size(); ++w) {
        sum +=
            layers_[l].get_neuron_value(w) * layers_[l].get_neuron_weight(w, n);
      }
      sum += layers_[l + 1].get_neuron_bias(n);
      layers_[l + 1].set_neuron_value(n, ActivationFunction(sum));
    }
  }
}

void GraphNetwork::BackPropagation(int target) {
  CalculateGradientErrors(target);
  UpdateWeights();
}

void GraphNetwork::CalculateGradientErrors(int target) {
  int hidden_layers = data_storage_->get_hidden_layers();
  std::vector<double> target_matrix(kLayerOutputSize);
  target_matrix[target - 1] = 1;
  for (int i = 0; i < kLayerOutputSize; ++i) {
    double neuron_output = layers_[hidden_layers + 1].get_neuron_value(i);
    double error =
        (target_matrix[i] - neuron_output) * DerivativeFunction(neuron_output);
    layers_[hidden_layers + 1].set_neuron_error(i, error);
  }
  for (int l = hidden_layers; l > 0; --l) {
    for (int n = 0; n < layers_[l].get_layer_size(); ++n) {
      double sum = 0;
      for (int w = 0; w < layers_[l].get_weight_size(); ++w) {
        sum += layers_[l + 1].get_neuron_error(w) *
               layers_[l].get_neuron_weight(n, w);
      }
      double error = sum * DerivativeFunction(layers_[l].get_neuron_value(n));
      layers_[l].set_neuron_error(n, error);
    }
  }
}

void GraphNetwork::UpdateWeights() {
  for (size_t l = 0; l < layers_.size() - 1; ++l) {
    for (int n = 0; n < layers_[l].get_layer_size(); ++n) {
      for (int w = 0; w < layers_[l].get_weight_size(); ++w) {
        double tmp = kLearningRate * layers_[l + 1].get_neuron_error(w);
        double tmp_weight = tmp * layers_[l].get_neuron_value(n);
        double new_weight = layers_[l].get_neuron_weight(n, w) + tmp_weight;
        layers_[l].set_neuron_weight(n, w, new_weight);
        if (n == 0) {
          double tmp_bias = layers_[l + 1].get_neuron_bias(w) + tmp;
          layers_[l + 1].set_nueron_bias(w, tmp_bias);
        }
      }
    }
  }
}

// ______________ WEIGHTS ______________ //

void GraphNetwork::LoadWeights(std::vector<double> vector_weights,
                               std::vector<double> vector_bias) {
  int i = 0, j = 0;
  for (size_t l = 0; l < layers_.size() - 1; ++l) {
    for (int n = 0; n < layers_[l].get_weight_size(); ++n) {
      for (int w = 0; w < layers_[l].get_layer_size(); ++w) {
        layers_[l].set_neuron_weight(w, n, vector_weights[i++]);
      }
      layers_[l + 1].set_nueron_bias(n, vector_bias[j++]);
    }
  }
}

void GraphNetwork::SaveWeights(std::string file_name) {
  std::ofstream out(file_name);
  for (size_t l = 0; l < layers_.size() - 1; ++l) {
    for (int n = 0; n < layers_[l].get_weight_size(); ++n) {
      for (int w = 0; w < layers_[l].get_layer_size(); ++w) {
        out << layers_[l].get_neuron_weight(w, n) << ",";
      }
    }
  }
  out << std::endl;
  for (size_t l = 0; l < layers_.size() - 1; ++l) {
    for (int n = 0; n < layers_[l].get_weight_size(); ++n) {
      out << layers_[l + 1].get_neuron_bias(n) << ",";
    }
  }
}

// ______________ FOR REPORT ______________ //

int GraphNetwork::FindMaxLetter() {
  int index = 0;
  int fin_layer = data_storage_->get_hidden_layers() + 1;
  for (size_t i = 1; i < kLayerOutputSize; ++i) {
    if (layers_[fin_layer].get_neuron_value(index) <=
        layers_[fin_layer].get_neuron_value(i)) {
      index = i;
    }
  }
  return index + 1;
}

// ______________ FOR MEMORY ______________ //

void GraphNetwork::MemAlloc() {
  Layer input_layer(kLayerInputSize, kLayerHiddenSize);
  layers_.push_back(input_layer);
  for (int i = 0; i < data_storage_->get_hidden_layers() - 1; ++i) {
    Layer hidden_layer(kLayerHiddenSize, kLayerHiddenSize);
    layers_.push_back(hidden_layer);
  }
  Layer hidden_layer(kLayerHiddenSize, kLayerOutputSize);
  layers_.push_back(hidden_layer);
  Layer output_layer(kLayerOutputSize, 0);
  layers_.push_back(output_layer);
}

void GraphNetwork::MemClear() { layers_.clear(); }

}  // namespace s21
