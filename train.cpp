#include <iostream>

void train(NeuralNetwork nn, vector<vector<float> > train_data) {
    // Get all the ones and eights from the train_data
    // int zero_arr =0;
    // int not_zero = 0;
    int count = 0;
    for (int row = 0; row < train_data.size(); row++) {
        float* num;
        num = new float[784];
        float* label;
        label = new float[2];
        bool only_zeroes = true;

        // Init label with only zeroes

        for (int i = 0; i < 2; i++) {
            label[i] = 0;
        }

        // Check if first item in the row is a 0 or 1
        if (train_data[row][0] == 0 || train_data[row][0] == 1 ) {
            // Now extract this vector and convert it into a float* with normalized values.
            // Feed into nn and train
            int lab_pos = train_data[row][0];
            label[lab_pos] = 1;
            for (int j = 0; j < 784; j++) {
                num[j] = train_data[row][j + 1] / 255;

                if (num[j] != 0) {
                    only_zeroes = false;
                }
            } 
            if (only_zeroes == false) {
                for (int i = 0; i < 2; i++) {
                    cout << label[i] << " ";
                }
                cout << endl;
                displayNum2(num);
                count++;
                nn.train(num, label);
            }

            cout << "\033c";
            delete[] num;
            delete[] label;
        }

        // displayNum2(num);
    }
    // cout << count << endl;
    //  cout<<"Tot not zero: "<<not_zero<<endl;
    //  cout<<"Tot zero arr: "<<zero_arr<<endl;
}