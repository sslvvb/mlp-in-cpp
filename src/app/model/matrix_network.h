#ifndef CPP7_MLP_0_SRC_MODEL_MATRIX_NETWORK_H_
#define CPP7_MLP_0_SRC_MODEL_MATRIX_NETWORK_H_

#include "network.h"
#include "s21matrix.h"

namespace s21 {

class MatrixNetwork : public NetworkInterface {
 public:
  MatrixNetwork() = delete;
  MatrixNetwork(DataStorage *data_storage) : data_storage_(data_storage) {}
  MatrixNetwork(const MatrixNetwork &other) = delete;
  MatrixNetwork(MatrixNetwork &&other) = delete;
  ~MatrixNetwork() override {}

  void MemClear() override;
  void MemAlloc() override;
  void ImputToNetwork(std::vector<double>) override;
  void ForwardPropagation() override;
  void BackPropagation(int) override;
  int FindMaxLetter() override;
  std::vector<double> OutputLayerToVector() override;
  void LoadWeights(std::vector<double>, std::vector<double>) override;
  void SaveWeights(std::string file_name) override;

 private:
  DataStorage *data_storage_{};
  std::vector<S21Matrix> weights_{};
  std::vector<S21Matrix> bias_{};
  std::vector<S21Matrix> neuron_values_{};
  std::vector<S21Matrix> errors_{};

  void CalculateGradientErrors(S21Matrix);
  void UpdateWeights();

  void WeightsAlloc();
  void BiasAlloc();
  void NeuronValuesAlloc();
  void ErrorsAlloc();
  void FillRamdomWeights(std::vector<S21Matrix> &);
};

}  // namespace s21

#endif  // CPP7_MLP_0_SRC_MODEL_MATRIX_NETWORK_H_
