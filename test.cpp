#include <iostream>

void test(NeuralNetwork nn, vector<vector<float> > test_data) {
    float perc;
    float correct = 0;
    float incorrect = 0;

    for (int row = 0; row < test_data.size(); row++) {
        // cout << "Testing" << endl;
        float* num;
        num = new float[784];
        float* label;
        label = new float[2];
        bool only_zeroes = true;

        // Init label with only zeroes

        for (int i = 0; i < 2; i++) {
            label[i] = 0;
        }

        // Check if first item in the row is a 1 or 8
        int lab;
        int predict;

        if (test_data[row][0] == 0 || test_data[row][0] == 1) {
            lab = test_data[row][0];  // Label of test
            label[lab] = 1;
            // Prediction

            // Init array of digit
            for (int j = 0; j < 784; j++) {
                num[j] = test_data[row][j + 1] / 255;
                if (num[j] != 0) {
                    only_zeroes = false;
                }
            }

            if (only_zeroes == false) {
                float* probs = nn.predict(num).returnArray();  // Prediction
                for(int i =0 ; i < 2; i++){
                    cout<<probs[i]<<" ";
                }
                cout << endl;
                float actual_max = 0;
                int actual_pos = 0;
                for (int j = 0; j <= 9; j++) {
                    if (probs[j] > actual_max) {
                        actual_max = probs[j];
                        predict = j;
                    }
                }
                cout << "Prediction: " << predict << endl;
                cout << "Actual: " << lab << endl;
            }

            for (int i = 0; i < 2; i++) {
                cout << label[i] << " ";
            }
            cout << endl;
            displayNum2(num);

            // compare
            if (predict == lab) {
                correct++;
            } else {
                incorrect++;
            }
            cout << "\033c";
            delete[] num;
            delete[] label;
        }
    }
    cout << "Correct: " << correct << endl;
    cout << "Incorrect: " << incorrect << endl;

    perc = (correct/(correct + incorrect))*100;
    cout<<perc<<"%"<<" accuracy"<<std::endl;
}
