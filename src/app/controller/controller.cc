#include "controller.h"

namespace s21 {

// ______________ SETTERS ______________ //

void Controller::set_hidden_layers(int hidden_layers) {
  facade_->set_hidden_layers(hidden_layers);
}

void Controller::set_epochs_count(int epochs_count) {
  facade_->set_epochs_count(epochs_count);
}

void Controller::set_cross_validation_group(int cross_validation_group) {
  facade_->set_cross_validation_group(cross_validation_group);
}

void Controller::set_cancel_process(bool is_canceled) {
  facade_->set_cancel_process(is_canceled);
}

void Controller::set_progress_percent(int percent) {
  facade_->set_progress_percent(percent);
}

// ______________ GETTERS ______________ //

int Controller::get_hidden_layers() { return facade_->get_hidden_layers(); }

int Controller::get_progress_percent() {
  return facade_->get_progress_percent();
}

std::vector<double> Controller::get_report_vector_for_learning() {
  return facade_->get_report_vector_for_learning();
}

// ______________ FOO ______________ //

void Controller::InitNetwork(bool network_type) {
  facade_->InitNetwork(network_type);
}

void Controller::CountFileItems(std::string file_name) {
  facade_->CountFileItems(file_name);
}

void Controller::StartEpochTrain() { facade_->StartEpochTrain(); }

void Controller::StartCrossValidationTrain() {
  facade_->StartCrossValidationTrain();
}

Metrics Controller::StartTesting(double test_sample) {
  return facade_->StartTesting(test_sample);
}

int Controller::GetPredictedValue(std::vector<double> pixel_array) {
  return facade_->GetPredictedValue(pixel_array);
}

void Controller::LoadWeights(std::string file_name) {
  facade_->LoadWeights(file_name);
}

void Controller::SaveWeights(std::string file_name) {
  facade_->SaveWeights(file_name);
}

}  // namespace s21
