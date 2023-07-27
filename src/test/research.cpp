#include <iostream>
#include <thread>
#include <vector>

#include "app/controller/controller.h"

int main() {
  s21::Controller controller;
  controller.InitNetwork(true);
  controller.LoadWeights("graph_2hidden_3epoch.weights");
  controller.CountFileItems(
      "../datasets/emnist-letters/emnist-letters-test.csv");

  int count_thread = std::thread::hardware_concurrency();

  std::cout << "максимальное количество потоков " << count_thread << std::endl;

  std::vector<double> times;
  int runs = 1000;
  for (int i = 0; i < runs;) {
    std::vector<std::thread> threads;
    int tmp = 0;
    for (; tmp < count_thread && i < runs; ++tmp, ++i) {
      threads.push_back(std::thread([&controller, &times]() {
        times.push_back(controller.StartTesting(1).time);
      }));
    }
    for (int k = 0; k < tmp; ++k) {
      threads[k].join();
    }
  }

  double sum = 0.0;
  for (int i = 1; i <= times.size(); ++i) {
    sum += times[i - 1];
    std::cout << " time " << i << " = " << times[i - 1];
    if (i % 10 == 0) {
      std::cout << std::endl;
    }
  }
  std::cout << " sum = " << sum << std::endl;

  return 0;
}
