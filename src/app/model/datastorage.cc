#include "datastorage.h"

namespace s21 {

// ______________ SETTERS ______________ //

void DataStorage::set_hidden_layers(int hidden_layers) {
  hidden_layers_ = hidden_layers;
}

void DataStorage::set_epochs_count(int epochs_count) {
  epochs_count_ = epochs_count;
}

void DataStorage::set_cross_validation_group(int cross_validation_group) {
  cross_validation_group_ = cross_validation_group;
}

void DataStorage::set_progress_percent(int progress_percent) {
  progress_percent_ = progress_percent;
}

void DataStorage::set_cancel_process(bool is_canceled) {
  is_canceled_ = is_canceled;
}

// ______________ GETTERS ______________ //

int DataStorage::get_hidden_layers() { return hidden_layers_; }

int DataStorage::get_epochs_count() { return epochs_count_; }

int DataStorage::get_cross_validation_group() {
  return cross_validation_group_;
}

int DataStorage::get_progress_percent() { return progress_percent_; }

bool DataStorage::get_is_canceled() { return is_canceled_; }

int DataStorage::get_file_size() { return file_size_; }

std::string DataStorage::get_file_name() { return file_name_; }

// ______________ STORAGE FOO ______________ //

void DataStorage::CountFileItems(std::string file_name) {
  file_size_ = 0;
  file_name_ = file_name;
  std::ifstream in(file_name);
  if (!in) throw std::invalid_argument("You should choose file!");
  while (in) {
    std::string line;
    while (getline(in, line)) {
      ++file_size_;
    }
  }
}

}  // namespace s21
