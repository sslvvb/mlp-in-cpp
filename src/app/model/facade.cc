#include "facade.h"

namespace s21 {

// ______________ SETTERS ______________ //

void Facade::set_hidden_layers(int hidden_layers) {
  data_storage_->set_hidden_layers(hidden_layers);
}

void Facade::set_cross_validation_group(int cross_validation_group) {
  data_storage_->set_cross_validation_group(cross_validation_group);
}

void Facade::set_epochs_count(int epochs_count) {
  data_storage_->set_epochs_count(epochs_count);
}

void Facade::set_cancel_process(bool is_canceled) {
  data_storage_->set_cancel_process(is_canceled);
}

void Facade::set_progress_percent(int percent) {
  data_storage_->set_progress_percent(percent);
}

// ______________ GETTERS ______________ //

int Facade::get_hidden_layers() { return data_storage_->get_hidden_layers(); }

int Facade::get_progress_percent() {
  return data_storage_->get_progress_percent();
}

std::vector<double> Facade::get_report_vector_for_learning() {
  return network_->get_report_vector_for_learning();
}

// ______________ FOO ______________ //

void Facade::InitNetwork(bool network_type) {
  delete network_;
  if (!network_type) {
    network_ = new Network(new GraphNetwork(data_storage_), data_storage_);
  } else {
    network_ = new Network(new MatrixNetwork(data_storage_), data_storage_);
  }
}

void Facade::CountFileItems(std::string file_name) {
  data_storage_->CountFileItems(file_name);
}

void Facade::StartEpochTrain() { network_->StartEpochTrain(); }

void Facade::StartCrossValidationTrain() {
  network_->StartCrossValidationTrain();
}

Metrics Facade::StartTesting(double test_sample) {
  return network_->StartTesting(test_sample);
}

int Facade::GetPredictedValue(std::vector<double> pixel_vector) {
  return network_->GetPredictedValue(pixel_vector);
}

void Facade::LoadWeights(std::string file_name) {
  network_->LoadWeights(file_name);
}

void Facade::SaveWeights(std::string file_name) {
  network_->SaveWeights(file_name);
}

void Facade::StartEpochTrainForTetsss() {
  network_->StartEpochTrainForTetsss();
}

std::vector<double> Facade::CollectStringToVector(std::string line) {
  return network_->CollectStringToVector(line);
}

}  // namespace s21
