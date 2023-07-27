#include "network.h"

namespace s21 {

// ______________ TRAINING ______________ //

void Network::StartEpochTrain() {
  report_error_for_learning_.clear();
  interface_->MemClear();
  interface_->MemAlloc();
  int max_percent_count =
      data_storage_->get_file_size() * data_storage_->get_epochs_count();
  int cur_percent_count = 1;
  for (int e = 0; e < data_storage_->get_epochs_count(); ++e) {
    success_find_letters_ = 0;
    std::ifstream in(data_storage_->get_file_name());
    while (in) {
      std::string line;
      while (getline(in, line) && !data_storage_->get_is_canceled()) {
        auto pair = CollectLearningPair(line);
        interface_->ImputToNetwork(pair.first);
        interface_->ForwardPropagation();
        int max_in_output_layer = interface_->FindMaxLetter();
        success_find_letters_ +=
            CalculateSuccessfulCase(max_in_output_layer, pair.second);
        interface_->BackPropagation(pair.second);
        CalculatePercentage(max_percent_count, cur_percent_count);
        ++cur_percent_count;
      }
    }
    report_error_for_learning_.push_back(
        100 - ((double)success_find_letters_ /
               (double)data_storage_->get_file_size()) *
                  100);
  }
  if (data_storage_->get_is_canceled()) {
    interface_->MemClear();
    report_error_for_learning_.clear();
    data_storage_->set_cancel_process(false);
    data_storage_->set_progress_percent(0);
  }
}

void Network::StartCrossValidationTrain() {
  report_error_for_learning_.clear();
  interface_->MemClear();
  interface_->MemAlloc();
  int end = data_storage_->get_file_size();
  int k = data_storage_->get_cross_validation_group();
  int part_size = end / k;
  int start = end - part_size;
  int max_percent = end * k;
  int cur_percent = 0;
  for (int i = 0; i < k && !data_storage_->get_is_canceled(); ++i) {
    success_find_letters_ = 0;
    LearnForCross(start, end, max_percent, cur_percent);
    TestForCross(start, end, max_percent, cur_percent);
    start -= part_size;
    end -= part_size;
    report_error_for_learning_.push_back(
        100 - ((double)success_find_letters_ / (double)part_size) * 100);
  }
  if (data_storage_->get_is_canceled()) {
    interface_->MemClear();
    data_storage_->set_cancel_process(false);
    data_storage_->set_progress_percent(0);
  }
}

void Network::LearnForCross(int start, int end, int max_percent,
                            int &cur_percent) {
  std::ifstream in(data_storage_->get_file_name());
  int i = 0;
  while (in) {
    std::string line;
    while (getline(in, line) && !data_storage_->get_is_canceled()) {
      if (i < start || i > end) {
        auto pair = CollectLearningPair(line);
        interface_->ImputToNetwork(pair.first);
        interface_->ForwardPropagation();
        interface_->BackPropagation(pair.second);
        ++cur_percent;
      }
      CalculatePercentage(max_percent, cur_percent);
      ++i;
    }
  }
}

void Network::TestForCross(int start, int end, int max_percent,
                           int &cur_percent) {
  std::ifstream in(data_storage_->get_file_name());
  int i = 0;
  while (in) {
    std::string line;
    while (getline(in, line) && !data_storage_->get_is_canceled()) {
      if (i >= start && i <= end) {
        auto pair = CollectLearningPair(line);
        interface_->ImputToNetwork(pair.first);
        interface_->ForwardPropagation();
        int max_in_output_layer = interface_->FindMaxLetter();
        success_find_letters_ +=
            CalculateSuccessfulCase(max_in_output_layer, pair.second);
        ++cur_percent;
      }
      CalculatePercentage(max_percent, cur_percent);
      ++i;
    }
  }
}

std::pair<std::vector<double>, int> Network::CollectLearningPair(
    std::string line) {
  int target = strtod(&line[0], nullptr);
  std::vector<double> input_vector;
  size_t n = line.find(',');
  while (n != std::string::npos) {
    if (n + 1 < line.size() && std::isdigit(line.at(n + 1))) {
      input_vector.push_back(std::stod(line.substr(n + 1), nullptr) / 255);
    }
    n = line.find(',', n + 1);
  }
  return std::make_pair(input_vector, target);
}

void Network::StartEpochTrainForTetsss() {
  for (int e = 0; e < data_storage_->get_epochs_count(); ++e) {
    std::ifstream in(data_storage_->get_file_name());
    while (in) {
      std::string line;
      while (getline(in, line)) {
        auto pair = CollectLearningPair(line);
        interface_->ImputToNetwork(pair.first);
        interface_->ForwardPropagation();
        interface_->BackPropagation(pair.second);
      }
    }
  }
}

// ______________ TESTING ______________ //

Metrics Network::StartTesting(double test_sample) {
  Metrics result_metrics;
  int cases_count = data_storage_->get_file_size() * test_sample;
  auto start = std::chrono::high_resolution_clock::now();
  int cur_percent_count = 0;
  std::ifstream in(data_storage_->get_file_name());
  int i = 0;
  while (in) {
    std::string line;
    while (getline(in, line) && i < cases_count &&
           !data_storage_->get_is_canceled()) {
      auto pair = CollectLearningPair(line);
      interface_->ImputToNetwork(pair.first);
      interface_->ForwardPropagation();
      int max_in_output_layer = interface_->FindMaxLetter();
      if (CalculateSuccessfulCase(max_in_output_layer, pair.second)) {
        ++result_metrics.accuracy;
      }
      std::vector<double> output_vector = interface_->OutputLayerToVector();
      CollectMetrics(output_vector, result_metrics, pair.second);
      CalculatePercentage(cases_count, cur_percent_count);
      ++cur_percent_count;
      ++i;
    }
  }
  if (data_storage_->get_is_canceled()) {
    data_storage_->set_cancel_process(false);
    data_storage_->set_progress_percent(0);
  } else {
    auto end = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    result_metrics.time = time.count();
    result_metrics.accuracy = result_metrics.accuracy / cases_count;
    CalculateMetrics(result_metrics);
    data_storage_->set_progress_percent(100);
  }
  return result_metrics;
}

int Network::GetPredictedValue(std::vector<double> pixel_vector) {
  interface_->ImputToNetwork(pixel_vector);
  interface_->ForwardPropagation();
  int predict_letter = interface_->FindMaxLetter();
  return predict_letter;
}

// ______________ WEIGHTS ______________ //

void Network::LoadWeights(std::string file_name) {
  std::ifstream in(file_name);
  if (!in) {
    throw std::invalid_argument("You should choose file with weights");
  }
  interface_->MemClear();
  std::string line;
  std::getline(in, line);
  auto vector_weights = CollectStringToVector(line);
  std::getline(in, line);
  auto vector_bias = CollectStringToVector(line);
  int hidden_size =
      (vector_weights.size() - (kLayerInputSize * kLayerHiddenSize) -
       (kLayerHiddenSize * kLayerOutputSize)) /
          (kLayerHiddenSize * kLayerHiddenSize) +
      1;
  data_storage_->set_hidden_layers(hidden_size);
  interface_->MemAlloc();
  interface_->LoadWeights(vector_weights, vector_bias);
}

void Network::SaveWeights(std::string file_name) {
  return interface_->SaveWeights(file_name);
}

// ______________ FOR REPORT ______________ //

void Network::CalculatePercentage(int max, int cur) {
  int progress_percent = cur * 100 / max;
  data_storage_->set_progress_percent(progress_percent);
}

int Network::CalculateSuccessfulCase(int max_in_output_layer,
                                     int target_value) {
  return max_in_output_layer == target_value ? 1 : 0;
}

void Network::CollectMetrics(std::vector<double> vector,
                             Metrics &result_metrics, int target_value) {
  for (int i = 0; i < kLayerOutputSize; ++i) {
    if (i == target_value - 1) {
      if (vector[i] > 0.5) {
        ++result_metrics.tp;
      } else {
        ++result_metrics.fp;
      }
    } else {
      if (vector[i] > 0.5) {
        ++result_metrics.fn;
      } else {
        ++result_metrics.tn;
      }
    }
  }
}

void Network::CalculateMetrics(Metrics &result_metrics) {
  result_metrics.precision = (double)result_metrics.tp /
                             (double)(result_metrics.tp + result_metrics.fp);
  result_metrics.recall = (double)result_metrics.tp /
                          (double)(result_metrics.tp + result_metrics.fn);
  result_metrics.fmeasure = 2 *
                            (result_metrics.precision * result_metrics.recall) /
                            (result_metrics.precision + result_metrics.recall);
}

std::vector<double> Network::CollectStringToVector(std::string line) {
  std::vector<double> vector;
  vector.push_back(std::stod(&line[0], nullptr));
  size_t n = line.find(',');
  while (n != std::string::npos) {
    if (n + 1 < line.size()) {
      vector.push_back(std::stod(line.substr(n + 1), nullptr));
    }
    n = line.find(',', n + 1);
  }
  return vector;
}

std::vector<double> Network::get_report_vector_for_learning() {
  return report_error_for_learning_;
}

// ______________ NetworkInterface ______________ //

double NetworkInterface::ActivationFunction(double res) {
  return 1.0 / (1.0 + exp(-res));
}

double NetworkInterface::DerivativeFunction(double value) {
  return value * (1.0 - value);
}

double NetworkInterface::GenerateRandomWeight() {
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution<double> dist(0.5, -0.5);
  return dist(mt);
}

}  // namespace s21
