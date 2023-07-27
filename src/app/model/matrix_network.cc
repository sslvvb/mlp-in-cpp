#include "matrix_network.h"

namespace s21 {

// ______________ TRAINING ______________ //

void MatrixNetwork::ImputToNetwork(std::vector<double> vector) {
  neuron_values_[0].VectorToMatrix(vector);
}

std::vector<double> MatrixNetwork::OutputLayerToVector() {
  return neuron_values_[data_storage_->get_hidden_layers() + 1]
      .OutputMatrixToVector();
}

void MatrixNetwork::ForwardPropagation() {
  for (size_t l = 0; l < weights_.size(); ++l) {
    for (int n = 0; n < weights_[l].get_columns(); ++n) {
      double sum = 0;
      for (int w = 0; w < weights_[l].get_rows(); ++w) {
        sum += neuron_values_[l](w, 0) * weights_[l](w, n);
      }
      sum += bias_[l](0, n);
      neuron_values_[l + 1](n, 0) = ActivationFunction(sum);
    }
  }
}

void MatrixNetwork::BackPropagation(int target) {
  S21Matrix target_matrix(kLayerOutputSize, 1);
  target_matrix.FillTargetMatrix(target);
  CalculateGradientErrors(target_matrix);
  UpdateWeights();
}

void MatrixNetwork::CalculateGradientErrors(S21Matrix target_matrix) {
  int hidden_layers = data_storage_->get_hidden_layers();
  S21Matrix tmp_error = target_matrix - neuron_values_[hidden_layers + 1];
  for (int i = 0; i < kLayerOutputSize; ++i) {
    errors_[hidden_layers](i, 0) =
        tmp_error(i, 0) *
        DerivativeFunction(neuron_values_[hidden_layers + 1](i, 0));
  }
  for (int l = hidden_layers; l > 0; --l) {
    for (int n = 0; n < errors_[l - 1].get_rows(); ++n) {
      double sum = 0;
      for (int w = 0; w < errors_[l].get_rows(); ++w) {
        sum += errors_[l](w, 0) * weights_[l](n, w);
      }
      errors_[l - 1](n, 0) = sum * DerivativeFunction(neuron_values_[l](n, 0));
    }
  }
}

void MatrixNetwork::UpdateWeights() {
  for (size_t l = 0; l < weights_.size(); ++l) {
    for (int n = 0; n < weights_[l].get_rows(); ++n) {
      for (int w = 0; w < weights_[l].get_columns(); ++w) {
        weights_[l](n, w) +=
            kLearningRate * errors_[l](w, 0) * neuron_values_[l](n, 0);
        if (n == 0) {
          bias_[l](0, w) += kLearningRate * errors_[l](w, 0);
        }
      }
    }
  }
}

// ______________ WEIGHTS ______________ //

void MatrixNetwork::LoadWeights(std::vector<double> vector_weights,
                                std::vector<double> vector_bias) {
  int i = 0, j = 0;
  for (size_t l = 0; l < weights_.size(); ++l) {
    for (int n = 0; n < weights_[l].get_columns(); ++n) {
      for (int w = 0; w < weights_[l].get_rows(); ++w) {
        weights_[l](w, n) = vector_weights[i++];
      }
      bias_[l](0, n) = vector_bias[j++];
    }
  }
}

void MatrixNetwork::SaveWeights(std::string file_name) {
  std::ofstream out(file_name);
  for (size_t l = 0; l < weights_.size(); ++l) {
    for (int n = 0; n < weights_[l].get_columns(); ++n) {
      for (int w = 0; w < weights_[l].get_rows(); ++w) {
        out << weights_[l](w, n) << ",";
      }
    }
  }
  out << std::endl;
  for (size_t l = 0; l < weights_.size(); ++l) {
    for (int n = 0; n < weights_[l].get_columns(); ++n) {
      out << bias_[l](0, n) << ",";
    }
  }
}

// ______________ FOR REPORT ______________ //

int MatrixNetwork::FindMaxLetter() {
  int index = 0;
  int fin_layer = data_storage_->get_hidden_layers() + 1;
  for (size_t i = 1; i < kLayerOutputSize; ++i) {
    if (neuron_values_[fin_layer](index, 0) <=
        neuron_values_[fin_layer](i, 0)) {
      index = i;
    }
  }
  return index + 1;
}

// ______________ FOR MEMORY ______________ //

void MatrixNetwork::MemAlloc() {
  WeightsAlloc();
  BiasAlloc();
  FillRamdomWeights(weights_);
  FillRamdomWeights(bias_);
  NeuronValuesAlloc();
  ErrorsAlloc();
}

void MatrixNetwork::WeightsAlloc() {
  S21Matrix input_weights(kLayerInputSize, kLayerHiddenSize);
  weights_.push_back(input_weights);
  for (int i = 0; i < data_storage_->get_hidden_layers() - 1; ++i) {
    S21Matrix hidden_weights(kLayerHiddenSize, kLayerHiddenSize);
    weights_.push_back(hidden_weights);
  }
  S21Matrix out_weights(kLayerHiddenSize, kLayerOutputSize);
  weights_.push_back(out_weights);
}

void MatrixNetwork::BiasAlloc() {
  for (int i = 0; i < data_storage_->get_hidden_layers(); ++i) {
    S21Matrix bias_weights(1, kLayerHiddenSize);
    bias_.push_back(bias_weights);
  }
  S21Matrix bias_weights(1, kLayerOutputSize);
  bias_.push_back(bias_weights);
}

void MatrixNetwork::FillRamdomWeights(std::vector<S21Matrix> &vector_matrix) {
  for (size_t i = 0; i < vector_matrix.size(); ++i) {
    for (int j = 0; j < vector_matrix[i].get_rows(); ++j) {
      for (int k = 0; k < vector_matrix[i].get_columns(); ++k) {
        vector_matrix[i](j, k) = GenerateRandomWeight();
      }
    }
  }
}

void MatrixNetwork::NeuronValuesAlloc() {
  S21Matrix input_neurons(kLayerInputSize, 1);
  neuron_values_.push_back(input_neurons);
  for (int i = 0; i < data_storage_->get_hidden_layers(); ++i) {
    S21Matrix hidden_neurons(kLayerHiddenSize, 1);
    neuron_values_.push_back(hidden_neurons);
  }
  S21Matrix output_neurons(kLayerOutputSize, 1);
  neuron_values_.push_back(output_neurons);
}

void MatrixNetwork::ErrorsAlloc() {
  for (int i = 0; i < data_storage_->get_hidden_layers(); ++i) {
    S21Matrix hidden_errors(kLayerHiddenSize, 1);
    errors_.push_back(hidden_errors);
  }
  S21Matrix output_errors(kLayerOutputSize, 1);
  errors_.push_back(output_errors);
}

void MatrixNetwork::MemClear() {
  weights_.clear();
  bias_.clear();
  neuron_values_.clear();
  errors_.clear();
}

}  // namespace s21
