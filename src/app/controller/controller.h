#ifndef CPP7_MLP_0_SRC_CONTROLLER_CONTROLLER_H_
#define CPP7_MLP_0_SRC_CONTROLLER_CONTROLLER_H_

#include "../model/facade.h"

namespace s21 {

class Controller {
 public:
  Controller() : facade_(new Facade) {}
  Controller(const Controller& other) = delete;
  Controller(Controller&& other) = delete;
  ~Controller() {}

  void set_hidden_layers(int);
  void set_epochs_count(int);
  void set_cross_validation_group(int);
  void set_cancel_process(bool);
  void set_progress_percent(int);

  int get_hidden_layers();
  int get_progress_percent();
  std::vector<double> get_report_vector_for_learning();

  void InitNetwork(bool network_type);
  void CountFileItems(std::string file_name);
  void StartEpochTrain();
  void StartCrossValidationTrain();
  Metrics StartTesting(double);
  int GetPredictedValue(std::vector<double> pixel_array);
  void LoadWeights(std::string file_name);
  void SaveWeights(std::string file_name);

 private:
  Facade* facade_;
};

}  // namespace s21

#endif  // CPP7_MLP_0_SRC_CONTROLLER_CONTROLLER_H_
