#ifndef CPP7_MLP_0_SRC_MODEL_DATASTORAGE_H_
#define CPP7_MLP_0_SRC_MODEL_DATASTORAGE_H_

#include <atomic>
#include <fstream>

namespace s21 {

constexpr int kLayerInputSize = 784;
constexpr int kLayerHiddenSize = 140;
constexpr int kLayerOutputSize = 26;
constexpr double kLearningRate = 0.1;

class DataStorage {
 public:
  DataStorage() {}
  DataStorage(const DataStorage& other) = delete;
  DataStorage(DataStorage&& other) = delete;
  ~DataStorage() {}

  void set_hidden_layers(int);
  void set_epochs_count(int);
  void set_cross_validation_group(int);
  void set_progress_percent(int);
  void set_cancel_process(bool);

  int get_hidden_layers();
  int get_epochs_count();
  int get_cross_validation_group();
  int get_progress_percent();
  bool get_is_canceled();
  int get_file_size();
  std::string get_file_name();

  void CountFileItems(std::string);

 private:
  int file_size_{};
  std::string file_name_{};
  std::atomic<int> progress_percent_{};
  std::atomic<bool> is_canceled_{};
  int hidden_layers_ = 2, epochs_count_ = 1, cross_validation_group_ = 5;
};

}  // namespace s21

#endif  // CPP7_MLP_0_SRC_MODEL_DATASTORAGE_H_
