#ifndef CPP7_MLP_0_SRC_MODEL_GRAPH_NETWORK_H_
#define CPP7_MLP_0_SRC_MODEL_GRAPH_NETWORK_H_

#include "layer.h"
#include "network.h"

namespace s21 {

class GraphNetwork : public NetworkInterface {
 public:
  GraphNetwork() = delete;
  GraphNetwork(DataStorage* data_storage) : data_storage_(data_storage) {}
  GraphNetwork(const GraphNetwork& other) = delete;
  GraphNetwork(GraphNetwork&& other) = delete;
  ~GraphNetwork() override {}

  void MemClear() override;
  void MemAlloc() override;
  void ImputToNetwork(std::vector<double>) override;
  std::vector<double> OutputLayerToVector() override;
  void ForwardPropagation() override;
  void BackPropagation(int target) override;
  int FindMaxLetter() override;
  void LoadWeights(std::vector<double>, std::vector<double>) override;
  void SaveWeights(std::string file_name) override;

 private:
  DataStorage* data_storage_;
  std::vector<Layer> layers_{};

  void CalculateGradientErrors(int);
  void UpdateWeights();
};

}  // namespace s21

#endif  // CPP7_MLP_0_SRC_MODEL_GRAPH_NETWORK_H_
