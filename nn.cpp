
#include <iostream>
#include "lib_mat.cpp"


class NeuralNetwork {

    int input_nodes;
    int hidden_nodes;
    int output_nodes;
    float lr = .1;
    
    Matrix weights_ih;  
    Matrix weights_ho;
    Matrix bias_h;
    Matrix bias_o;

public: 
    NeuralNetwork(int inp_nodes, int hidd_nodes, int outp_nodes)
        : input_nodes(inp_nodes), hidden_nodes(hidd_nodes), output_nodes(outp_nodes),
          weights_ih(hidd_nodes, inp_nodes), weights_ho(outp_nodes, hidd_nodes),
          bias_h(hidd_nodes, 1), bias_o(outp_nodes, 1) {

        //Temporary init of weights.
        weights_ih.randomize();
        weights_ho.randomize();
        bias_h.randomize();
        bias_o.randomize();

    }

    Matrix predict(float* input) {
         
        Matrix inputs(input_nodes, 1);
        inputs.initFromArray(input); //Init mat from inputs
        Matrix hidden_act = weights_ih.mat_mult(inputs);
        hidden_act = hidden_act.add_matrix(bias_h); // Adding bias
        hidden_act.sigmoid(); //Activ funct
        Matrix output = weights_ho.mat_mult(hidden_act);
        output = output.add_matrix(bias_o);//Adding bias
        output.sigmoid();

        //float * outputArray = output.returnArray();
        //output.display();
        return output;
    }
    
    void train(float* inputs, float* targets){
        // Guess of nn for set of inputs (feed forwards algorithm)
        Matrix inpMat(input_nodes, 1);
        inpMat.initFromArray(inputs); //Init mat from inputs
        Matrix hidden_act = weights_ih.mat_mult(inpMat); // Activ of hidden
        hidden_act = hidden_act.add_matrix(bias_h); // Adding bias
        hidden_act.sigmoid(); //Activ funct
        //Moving hidd act to output
        Matrix outputs(output_nodes, 1);
        outputs = weights_ho.mat_mult(hidden_act);
        outputs = outputs.add_matrix(bias_o);//Adding bias
        outputs.sigmoid();
        // Error calculation. 
        Matrix targetsMat(output_nodes, 1);
        targetsMat.initFromArray(targets); // Init target Matrix
        //Calculate output error   
        // Error = Target - outputs
        Matrix output_errors = targetsMat.subtract_matrix(outputs);
        //Calculate error in hidden layer
        // hid_err =  transposed(weight_ho) * output_err 
        Matrix hidden_layer_error(hidden_nodes,1); // Init mat that contains errors
        Matrix weights_ho_transposed = weights_ho.transpose();
        hidden_layer_error = weights_ho_transposed.mat_mult(output_errors);


        // Tweak weights based on the errors calculated. 
        // y = m * x + b | y = sig(W * I + b)
        // delta m = lr*x*error  | d Who ij = lr * E(s(out)(1-out)) * hid_act_transp
        // delta b =  lr*error
        // delta bias = lr * E(s(out)(1-out))
        
        //Calculating gradient
        Matrix output_grad = outputs;
        output_grad.scalar_mult(-1); // -out
        output_grad.add(1); //(1-out)
        output_grad.hadamard(outputs); // s(out)(1-out)
        output_grad.hadamard(output_errors); //E(s(out)(1-out))
        output_grad.scalar_mult(lr); //lr*gradient

        //Calculating deltas of weights;
        Matrix hidd_actTransposed = hidden_act.transpose();
        Matrix weights_ho_deltas = output_grad.mat_mult(hidd_actTransposed);

        // Adjusting the weights and the biases with deltas
        weights_ho = weights_ho.add_matrix(weights_ho_deltas);
        bias_o = bias_o.add_matrix(output_grad); // just adding lr*gradient to biases 
    


        // Now the hiddden layer!

        Matrix hidden_grad = hidden_act;
        hidden_grad.scalar_mult(-1); //-hidden
        hidden_grad.add(1); //(1-hidd)

        hidden_grad.hadamard(hidden_act); //(hidd)(1-hidd)
        hidden_grad.hadamard(hidden_layer_error); //E(hidd)(1-hidd)
        hidden_grad.scalar_mult(lr); //lr * grad

        // Calculating the delta for weights in hidden
        Matrix inpMatTransposed = inpMat.transpose(); 
        Matrix weights_ih_deltas = hidden_grad.mat_mult(inpMatTransposed);
        
        //Adjust the weights and biases with deltas
        weights_ih = weights_ih.add_matrix(weights_ih_deltas);
        bias_h =bias_h.add_matrix(hidden_grad);
    }
}; 