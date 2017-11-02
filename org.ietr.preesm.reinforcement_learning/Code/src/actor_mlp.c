// File header
#include "../include/actor_mlp.h"
// Math lib
#include <math.h>
// Std libs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef M_PI
    #define M_PI 3.1415926535897932385
#endif

void layer(int layer_size, int output_size, float *weights, float *bias_values, float *input, float *output) {
    /*
     * Structure of layer in a MLP:
     *
     * input:       -> N tokens with N the number of neurons of the layer
     * output:      -> O tokens with O the number of neurons of the next layer
     *
     * weights:     -> Matrix of dimension N*O tokens
     * bias_values: -> Vector of O tokens
     *
     */
    // Performs the matrix product between the input vector and the weight matrix
    for (int wo_i = 0; wo_i < output_size; ++wo_i) {
        // Start with the bias_value
        output[wo_i] = bias_values[wo_i];
        int matrix_row = output_size * wo_i;
        for (int wl_i = 0; wl_i < layer_size; ++wl_i) {
            output[wo_i] += weights[matrix_row + wo_i] * input[wl_i];
        }
    }
}

void neuron(int input_size,
            IN float *input, IN float *weights, IN float *bias_values,
            OUT float *output) {
    float result = bias_values[0];
    /*
     * This compute the output of neuron[i] of a layer of a MLP neural network
     *
     * With n input values, weights array is constructed this way:
     *      weight[0] -> weight from input[0] to neuron[i]
     *      weight[1] -> weight from input[1] to neuron[i]
     *      ...
     *      weight[n] -> weight from input[n] to neuron[i]
     *
     */
    for (int wi = 0; wi < input_size; ++wi) {
        //fprintf(stderr, "%lf\n", weights[wi]);
        result += input[wi] * weights[wi];
    }
    (*output) = tanh(result);
}

void neuron_output(int input_size,
            IN float *input, IN float *weights, IN float *bias_values,
            OUT float *output) {
    float result = bias_values[0];
    /*
     * This compute the output of neuron[i] of an output layer of a MLP neural network
     *
     * With n input values, weights array is constructed this way:
     *      weight[0] -> weight from input[0] to neuron[i]
     *      weight[1] -> weight from input[1] to neuron[i]
     *      ...
     *      weight[n] -> weight from input[n] to neuron[i]
     *
     */
    for (int wi = 0; wi < input_size; ++wi) {
        //fprintf(stderr, "%lf\n", weights[wi]);
        result += input[wi] * weights[wi];
    }
    (*output) = result;
}


void weightsGen(int input_size, int layer_size,
               IN float *weights_in, IN float *bias_in,
               OUT float *weights_out, OUT float *bias_out) {
    /*
     * Simple copy of the IN data to the OUT data
     */
    memcpy(weights_out, weights_in, input_size * layer_size * sizeof(float));
    memcpy(bias_out, bias_in, layer_size * sizeof(float));
}

void weightGenInit(int id, OUT float *weights_out, OUT float *bias_out) {
    switch(id) {
        case 0:
            weights_out[0] = 6.103481292724609;
            weights_out[1] = 1.8938380479812622;
            weights_out[2] = -1.572178602218628;
            weights_out[3] = -5.537895202636719;
            weights_out[4] = -22.776283264160156;
            weights_out[5] = 5.881246566772461;
            weights_out[6] = 9.541479110717773;
            weights_out[7] = 0.8353186845779419;
            weights_out[8] = -0.7163775563240051;
            weights_out[9] = 1.8381121158599854;
            weights_out[10] = -1.1968830823898315;
            weights_out[11] = -0.19141370058059692;
            weights_out[12] = 7.464032173156738;
            weights_out[13] = -0.5403027534484863;
            weights_out[14] = 2.970580577850342;
            weights_out[15] = 4.629502773284912;
            weights_out[16] = -1.491894245147705;
            weights_out[17] = -0.32614365220069885;
            weights_out[18] = 19.572704315185547;
            weights_out[19] = 4.6797356605529785;
            weights_out[20] = 2.745119571685791;
            weights_out[21] = 4.86457633972168;
            weights_out[22] = 0.6062073111534119;
            weights_out[23] = 0.5467478632926941;
            weights_out[24] = -16.661718368530273;
            weights_out[25] = 3.891967296600342;
            weights_out[26] = 1.528936505317688;
            weights_out[27] = 15.19936752319336;
            weights_out[28] = 6.877312660217285;
            weights_out[29] = -6.355995178222656;
            weights_out[30] = 10.890667915344238;
            weights_out[31] = 1.1758694648742676;
            weights_out[32] = 0.9998450875282288;
            weights_out[33] = 18.462982177734375;
            weights_out[34] = -11.4066743850708;
            weights_out[35] = -2.0098159313201904;
            weights_out[36] = 1.9436562061309814;
            weights_out[37] = -1.1557774543762207;
            weights_out[38] = -0.20245519280433655;
            weights_out[39] = -7.20500373840332;
            weights_out[40] = -16.424196243286133;
            weights_out[41] = 5.74139928817749;
            weights_out[42] = 3.8783326148986816;
            weights_out[43] = 1.8775659799575806;
            weights_out[44] = 0.5955561995506287;
            weights_out[45] = 5.965015411376953;
            weights_out[46] = -1.4358479976654053;
            weights_out[47] = -0.40194785594940186;
            weights_out[48] = 5.883052349090576;
            weights_out[49] = 0.8940021991729736;
            weights_out[50] = 0.7600221633911133;
            weights_out[51] = 16.377397537231445;
            weights_out[52] = 5.833582401275635;
            weights_out[53] = 5.615663051605225;
            weights_out[54] = 5.9257001876831055;
            weights_out[55] = 0.6445311307907104;
            weights_out[56] = -1.1628108024597168;
            weights_out[57] = 16.239910125732422;
            weights_out[58] = -2.8111228942871094;
            weights_out[59] = -3.597381114959717;
            bias_out[0] = -20.177616119384766;
            bias_out[1] = 2.497835636138916;
            bias_out[2] = -17.362316131591797;
            bias_out[3] = -15.145865440368652;
            bias_out[4] = -17.622142791748047;
            bias_out[5] = -17.146181106567383;
            bias_out[6] = -19.921977996826172;
            bias_out[7] = -17.11701774597168;
            bias_out[8] = -9.608945846557617;
            bias_out[9] = 7.162945747375488;
            bias_out[10] = -19.751569747924805;
            bias_out[11] = -18.97005271911621;
            bias_out[12] = -15.211738586425781;
            bias_out[13] = -2.018737316131592;
            bias_out[14] = -18.828340530395508;
            bias_out[15] = -17.57478141784668;
            bias_out[16] = -18.07686424255371;
            bias_out[17] = -17.510927200317383;
            bias_out[18] = -16.068052291870117;
            bias_out[19] = -16.435142517089844;
            break;
        case 1:
            weights_out[0] = 0.4571332335472107;
            weights_out[1] = 0.369848370552063;
            weights_out[2] = -0.2183680683374405;
            weights_out[3] = 0.4390034079551697;
            weights_out[4] = -1.7147407531738281;
            weights_out[5] = 0.5035991072654724;
            weights_out[6] = -3.231074094772339;
            weights_out[7] = -0.6160842180252075;
            weights_out[8] = 0.1262763887643814;
            weights_out[9] = -0.6194915175437927;
            weights_out[10] = -0.48036372661590576;
            weights_out[11] = 1.302878499031067;
            weights_out[12] = 0.45691150426864624;
            weights_out[13] = 0.37861010432243347;
            weights_out[14] = -0.14240297675132751;
            weights_out[15] = 0.4513198733329773;
            weights_out[16] = -0.983752429485321;
            weights_out[17] = -0.735744833946228;
            weights_out[18] = 0.2784736454486847;
            weights_out[19] = 1.930366039276123;
            bias_out[0] = 0.789627194404602;
            break;
        default:
            fprintf(stderr, "Unhandled ID init value: %d", id);
    }
}