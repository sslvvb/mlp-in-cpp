#include <gtest/gtest.h>

#include <vector>

#include "../app/model/facade.h"

namespace s21 {

void CompareWeights(Facade facade, std::string etalon_weights,
                    std::string testing_weights) {
  std::ifstream etalon(etalon_weights);
  std::ifstream testing(testing_weights);
  std::string etalon_line;
  std::string testing_line;

  std::getline(etalon, etalon_line);
  std::getline(testing, testing_line);

  auto etalon_vector_weights = facade.CollectStringToVector(etalon_line);
  auto testing_vector_weights = facade.CollectStringToVector(testing_line);

  for (size_t i = 0; i < etalon_vector_weights.size(); ++i) {
    ASSERT_EQ(etalon_vector_weights[i], testing_vector_weights[i]);
  }

  std::getline(etalon, etalon_line);
  std::getline(testing, testing_line);

  auto etalon_vector_bias = facade.CollectStringToVector(etalon_line);
  auto testing_vector_bias = facade.CollectStringToVector(testing_line);

  for (size_t i = 0; i < etalon_vector_bias.size(); ++i) {
    ASSERT_EQ(etalon_vector_bias[i], testing_vector_bias[i]);
  }
}

TEST(MLP_TEST, test1) {
  Facade facade;
  facade.set_hidden_layers(2);
  facade.set_epochs_count(2);
  facade.InitNetwork(1);  // matrix
  std::string etalon_weights = "etalon_1_test.weights";
  std::string generated_weights = "test_generated_1.weights";

  facade.LoadWeights("random_generated.weights");
  facade.CountFileItems(
      "../../datasets/emnist-letters/emnist-letters-train_part.csv");
  facade.StartEpochTrainForTetsss();
  facade.SaveWeights(generated_weights);

  CompareWeights(facade, etalon_weights, generated_weights);
}

TEST(MLP_TEST, test2) {
  Facade facade;
  facade.set_hidden_layers(5);
  facade.set_epochs_count(4);
  facade.InitNetwork(1);  // matrix
  std::string etalon_weights = "etalon_2_test.weights";
  std::string generated_weights = "test_generated_2.weights";

  facade.LoadWeights("random_generated.weights");
  facade.CountFileItems(
      "../../datasets/emnist-letters/emnist-letters-train_part.csv");
  facade.StartEpochTrainForTetsss();
  facade.SaveWeights(generated_weights);

  CompareWeights(facade, etalon_weights, generated_weights);
}

TEST(MLP_TEST, test3) {
  Facade facade;
  facade.set_hidden_layers(3);
  facade.set_epochs_count(10);
  facade.InitNetwork(1);  // matrix
  std::string etalon_weights = "etalon_3_test.weights";
  std::string generated_weights = "test_generated_3.weights";

  facade.LoadWeights("random_generated.weights");
  facade.CountFileItems(
      "../../datasets/emnist-letters/emnist-letters-train_part.csv");
  facade.StartEpochTrainForTetsss();
  facade.SaveWeights(generated_weights);

  CompareWeights(facade, etalon_weights, generated_weights);
}

TEST(MLP_TEST, test4) {
  Facade facade;
  facade.set_hidden_layers(2);
  facade.set_epochs_count(2);
  facade.InitNetwork(0);  // graph
  std::string etalon_weights = "etalon_4_test.weights";
  std::string generated_weights = "test_generated_4.weights";

  facade.LoadWeights("random_generated.weights");
  facade.CountFileItems(
      "../../datasets/emnist-letters/emnist-letters-train_part.csv");
  facade.StartEpochTrainForTetsss();
  facade.SaveWeights(generated_weights);

  CompareWeights(facade, etalon_weights, generated_weights);
}

TEST(MLP_TEST, test5) {
  Facade facade;
  facade.set_hidden_layers(5);
  facade.set_epochs_count(4);
  facade.InitNetwork(0);  // graph
  std::string etalon_weights = "etalon_5_test.weights";
  std::string generated_weights = "test_generated_5.weights";

  facade.LoadWeights("random_generated.weights");
  facade.CountFileItems(
      "../../datasets/emnist-letters/emnist-letters-train_part.csv");
  facade.StartEpochTrainForTetsss();
  facade.SaveWeights(generated_weights);

  CompareWeights(facade, etalon_weights, generated_weights);
}

TEST(MLP_TEST, test6) {
  Facade facade;
  facade.set_hidden_layers(3);
  facade.set_epochs_count(10);
  facade.InitNetwork(0);  // graph
  std::string etalon_weights = "etalon_6_test.weights";
  std::string generated_weights = "test_generated_6.weights";

  facade.LoadWeights("random_generated.weights");
  facade.CountFileItems(
      "../../datasets/emnist-letters/emnist-letters-train_part.csv");
  facade.StartEpochTrainForTetsss();
  facade.SaveWeights(generated_weights);

  CompareWeights(facade, etalon_weights, generated_weights);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

}  // namespace s21
