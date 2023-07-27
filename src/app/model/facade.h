#ifndef CPP7_MLP_0_SRC_MODEL_FACADE_H_
#define CPP7_MLP_0_SRC_MODEL_FACADE_H_

#include "graph_network.h"
#include "matrix_network.h"
#include "network.h"

namespace s21 {

class Facade {
 public:
  Facade() : data_storage_(new DataStorage), network_(nullptr) {}
  ~Facade() {}

  void set_hidden_layers(int hidden_layers);
  void set_network_type(bool network_type);
  void set_cross_validation_group(int cross_validation_group);
  void set_epochs_count(int epochs_count);
  void set_test_sample_value(double test_sample_value);
  void set_cancel_process(bool is_canceled);
  void set_progress_percent(int);

  bool get_network_type();
  double get_cross_validation_group();
  double get_test_sample_value();
  int get_hidden_layers();
  int get_progress_percent();
  std::vector<double> get_report_vector_for_learning();

  void InitNetwork(bool network_type);
  void CountFileItems(std::string file_name);
  void StartEpochTrain();
  void StartCrossValidationTrain();
  Metrics StartTesting(double);
  void StartEpochTrainForTetsss();
  std::vector<double> CollectStringToVector(std::string);
  void LoadWeights(std::string file_name);
  void SaveWeights(std::string file_name);
  int GetPredictedValue(std::vector<double> pixel_vector);

 private:
  DataStorage* data_storage_;
  Network* network_;
};

}  // namespace s21

#endif  // CPP7_MLP_0_SRC_MODEL_FACADE_H_
