#ifndef CPP7_MLP_0_SRC_MODEL_NETWORK_H_
#define CPP7_MLP_0_SRC_MODEL_NETWORK_H_

#include <chrono>
#include <random>

#include "datastorage.h"

namespace s21 {

struct Metrics {
  int tp{}, tn{}, fp{}, fn{};
  double time{}, accuracy{}, precision{}, recall{}, fmeasure{};
};

class NetworkInterface {
 public:
  NetworkInterface() {}
  NetworkInterface(const NetworkInterface& other) = delete;
  NetworkInterface(NetworkInterface&& other) = delete;
  virtual ~NetworkInterface() {}

  virtual void MemClear() = 0;
  virtual void MemAlloc() = 0;
  virtual void ImputToNetwork(std::vector<double>) = 0;
  virtual std::vector<double> OutputLayerToVector() = 0;
  virtual void ForwardPropagation() = 0;
  virtual void BackPropagation(int) = 0;
  virtual int FindMaxLetter() = 0;
  virtual void LoadWeights(std::vector<double>, std::vector<double>) = 0;
  virtual void SaveWeights(std::string) = 0;

  double ActivationFunction(double);
  double DerivativeFunction(double);
  double GenerateRandomWeight();
};

class Network {
 public:
  Network() = delete;
  Network(NetworkInterface* interface, DataStorage* data_storage)
      : interface_(interface), data_storage_(data_storage) {}
  Network(const Network& other) = delete;
  Network(Network&& other) = delete;
  ~Network() {}

  std::vector<double> get_report_vector_for_learning();

  void StartEpochTrain();
  void StartEpochTrainForTetsss();
  void StartCrossValidationTrain();
  Metrics StartTesting(double);
  int GetPredictedValue(std::vector<double>);
  void LoadWeights(std::string);
  void SaveWeights(std::string);
  std::vector<double> CollectStringToVector(std::string line);

 private:
  NetworkInterface* interface_;
  DataStorage* data_storage_;
  std::vector<double> report_error_for_learning_{};
  int success_find_letters_{};

  void LearnForCross(int, int, int, int&);
  void TestForCross(int, int, int, int&);
  std::pair<std::vector<double>, int> CollectLearningPair(std::string);
  void CalculatePercentage(int, int);
  int CalculateSuccessfulCase(int, int);
  void CollectMetrics(std::vector<double>, Metrics&, int);
  void CalculateMetrics(Metrics&);
};

}  // namespace s21

#endif  // CPP7_MLP_0_SRC_MODEL_NETWORK_H_
