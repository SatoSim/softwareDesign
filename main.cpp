#include <string>
#include "nn.cpp"
#include "read_data.cpp"
#include "test.cpp"
#include "train.cpp"

int main() {
    int input;
    // Next step normalize inputs
    NeuralNetwork nn(784, 100, 2);
    vector<vector<float>> train_data;
    vector<vector<float>> test_data;
    string train_data_file = "mnist_train.csv";
    string test_data_file = "mnist_test.csv";

    train_data = read_file(train_data_file); // Vector that contains all the written digits
    test_data = read_file(test_data_file);

    train(nn, train_data);
    test(nn, test_data);
    return 0;
}
