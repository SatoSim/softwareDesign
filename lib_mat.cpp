# include <iostream>
#include <stdlib.h> 
#include "sigmoid.cpp"

class Matrix{

    int num_rows;
    int num_cols;
    float ** matrix;

public: 
    Matrix(int r, int c): num_rows(r), num_cols(c){
        matrix = new float* [num_rows];
    
        for(int i =0; i<num_rows; i++){
        matrix[i] = new float[num_cols];
        }

        for(int row = 0; row<num_rows;row++){
            for (int col = 0;  col < num_cols ; col++){
                matrix[row][col] = 0;
            }
        }
    }
    
Matrix& operator=(const Matrix &m) {
    if (this != &m) {
        // Check for self-assignment to avoid unnecessary work

        // Free existing resources
        for (int i = 0; i < num_rows; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;

        // Copy the size information
        num_rows = m.num_rows;
        num_cols = m.num_cols;

        // Allocate memory for the new matrix
        matrix = new float*[num_rows];
        for (int i = 0; i < num_rows; ++i) {
            matrix[i] = new float[num_cols];
        }

        // Copy the values from the original matrix to the new matrix
        for (int row = 0; row < num_rows; ++row) {
            for (int col = 0; col < num_cols; ++col) {
                matrix[row][col] = m.matrix[row][col];
            }
        }
    }
    return *this;
}

    Matrix(const Matrix& other) : num_rows(other.num_rows), num_cols(other.num_cols) {
    matrix = new float*[num_rows];
    for (int i = 0; i < num_rows; ++i) {
        matrix[i] = new float[num_cols];
    }

    for (int row = 0; row < num_rows; ++row) {
        for (int col = 0; col < num_cols; ++col) {
            matrix[row][col] = other.matrix[row][col];
        }
    }
}


        
    void initFromArray(float* input){
        for(int i = 0; i < num_rows; i++) {
            matrix[i][0] = input[i];
        }
    }

    float* returnArray(){
         float * arr = new float[num_rows];
        for(int i =0; i<num_rows; i++){
            arr[i] = matrix[i][0];
        }
        return arr;
    }



    void set_value(int row, int col, float n){
        matrix[row-1][col-1]= n;
    }
    float ** get_matrix(){
        return matrix;
    }
    int num_row(){
        return num_rows;
    }

    int num_col(){
        return num_cols;
    }

    void randomize(){
        srand((unsigned) time(NULL));
        for(int i =0; i< num_rows; i++){
            for(int j = 0; j < num_cols; j++){
                matrix[i][j] = (float)(rand()) / (float)(RAND_MAX) - (float)(rand()) / (float)(RAND_MAX);
            }
        }
    }
    void display(){
        for(int row = 0; row<num_rows;row++){
            std::cout<<"[ ";
            for (int col = 0; col < num_cols ; col++){
                std::cout<<matrix[row][col]<<" ";
            }
            std::cout<<"]";
            std::cout<<std::endl;       
        }
        std::cout<<std::endl;
    }

    Matrix add_matrix(Matrix b){ // Takes a matrix and adds up with the matrix that called it.
        float** matb = b.get_matrix();
        if(b.num_col() != num_cols || b.num_row() != num_rows){
            std::cout<<"MATRICES DO NOT HAVE SAME SIZE!!"<<std::endl;
        }else{
            Matrix res(b.num_row(), b.num_col());
            float** matres = res.get_matrix();
            for(int row = 0; row< num_rows; row++){
                for(int col =0; col<num_cols; col++){
                     matres[row][col]= matb[row][col]+matrix[row][col];
                }
            }
            return res; 
        }
        return b;
    }

    Matrix subtract_matrix(Matrix b){ 
        float** matb = b.get_matrix();
        if(b.num_col() != num_cols || b.num_row() != num_rows){
            std::cout<<"MATRICES DO NOT HAVE SAME SIZE!!"<<std::endl;
        }else{
            Matrix res(b.num_row(), b.num_col());
            float** matres = res.get_matrix();
            for(int row = 0; row< num_rows; row++){
                for(int col =0; col<num_cols; col++){
                     matres[row][col]= -matb[row][col]+matrix[row][col];
                }
            }
            return res; 
        }
        return b;
    }

    void scalar_mult(float n){
        for(int row = 0; row< num_rows; row++){
                for(int col =0; col<num_cols; col++){
                    matrix[row][col] *= n;
                }
            }

    }


    void add(float n){
         for(int row = 0; row< num_rows; row++){
                for(int col =0; col<num_cols; col++){
                    matrix[row][col] +=n;
                }
            }
    }

    Matrix mat_mult(Matrix b){
        float** matb = b.get_matrix();
        float** mata = matrix;
        if(b.num_row()!=num_cols){
            std::cout<<"Matrices cant be multiplied."<<std::endl;
        }else{
            Matrix result(num_rows, b.num_col());
            float ** matc = result.get_matrix();
            
            for(int rowc = 0; rowc < result.num_row(); rowc++){
                for(int colc = 0; colc < result.num_col(); colc++){
                    
                for(int i = 0; i< b.num_row(); i++){
                    matc[rowc][colc] += (mata[rowc][i]* matb[i][colc]);
                }
                }
            }

            return result;
        }
        return b;
    }

    Matrix transpose(){
        
        Matrix At(num_cols, num_rows);
        float** at = At.get_matrix();
        for(int i = 0; i < num_rows; i++ ){
            for(int j = 0; j < num_cols; j++){
                at[j][i]= matrix[i][j];
            }
        }
        return At;
    }
    

    void sigmoid(){
        for(int i = 0; i < num_rows; i++){
            for(int j =0 ; j< num_cols; j++){
                matrix[i][j] = sig(matrix[i][j]);
            }
        }
    } 

    void hadamard(Matrix b ){
        // Takes a matrix and multiplies elementwise the matrix that called it.
        float** matb = b.get_matrix();
        if(b.num_col() != num_cols || b.num_row() != num_rows){
            std::cout<<"MATRICES DO NOT HAVE SAME SIZE!!"<<std::endl;
        }else{
            for(int row = 0; row< num_rows; row++){
                for(int col =0; col<num_cols; col++){
                     matrix[row][col] *= matb[row][col];
                }
            }
        }
    }
    void softmax(){
        float tot;
        for(int i = 0; i < num_rows; i++){
            for(int j =0 ; j< num_cols; j++){
                tot += std::exp(matrix[i][j]);
            }
        }
        for(int i = 0; i < num_rows; i++){
            for(int j =0 ; j< num_cols; j++){
                matrix[i][j] = std::exp(matrix[i][j])/tot;
            }
        }
    }
    // Deallocate matrix
    
    ~Matrix(){
        for (int i =0; i<num_rows; i++){
            delete matrix[i];
        }
        delete [] matrix;
    }
    
};
 