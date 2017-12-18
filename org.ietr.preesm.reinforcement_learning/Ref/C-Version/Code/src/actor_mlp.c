// std libs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// math lib
#include <math.h>
// file header
#include "../include/actor_mlp.h"
#include "../include/common.h"



void actorWeightGenInit(int id, OUT float *weights_out, OUT float *bias_out) {
//    switch(id) {
//        case 0:
//            weights_out[0] = 6.103481292724609f;
//            weights_out[1] = 1.8938380479812622f;
//            weights_out[2] = -1.572178602218628f;
//            weights_out[3] = -5.537895202636719f;
//            weights_out[4] = -22.776283264160156f;
//            weights_out[5] = 5.881246566772461f;
//            weights_out[6] = 9.541479110717773f;
//            weights_out[7] = 0.8353186845779419f;
//            weights_out[8] = -0.7163775563240051f;
//            weights_out[9] = 1.8381121158599854f;
//            weights_out[10] = -1.1968830823898315f;
//            weights_out[11] = -0.19141370058059692f;
//            weights_out[12] = 7.464032173156738f;
//            weights_out[13] = -0.5403027534484863f;
//            weights_out[14] = 2.970580577850342f;
//            weights_out[15] = 4.629502773284912f;
//            weights_out[16] = -1.491894245147705f;
//            weights_out[17] = -0.32614365220069885f;
//            weights_out[18] = 19.572704315185547f;
//            weights_out[19] = 4.6797356605529785f;
//            weights_out[20] = 2.745119571685791f;
//            weights_out[21] = 4.86457633972168f;
//            weights_out[22] = 0.6062073111534119f;
//            weights_out[23] = 0.5467478632926941f;
//            weights_out[24] = -16.661718368530273f;
//            weights_out[25] = 3.891967296600342f;
//            weights_out[26] = 1.528936505317688f;
//            weights_out[27] = 15.19936752319336f;
//            weights_out[28] = 6.877312660217285f;
//            weights_out[29] = -6.355995178222656f;
//            weights_out[30] = 10.890667915344238f;
//            weights_out[31] = 1.1758694648742676f;
//            weights_out[32] = 0.9998450875282288f;
//            weights_out[33] = 18.462982177734375f;
//            weights_out[34] = -11.4066743850708f;
//            weights_out[35] = -2.0098159313201904f;
//            weights_out[36] = 1.9436562061309814f;
//            weights_out[37] = -1.1557774543762207f;
//            weights_out[38] = -0.20245519280433655f;
//            weights_out[39] = -7.20500373840332f;
//            weights_out[40] = -16.424196243286133f;
//            weights_out[41] = 5.74139928817749f;
//            weights_out[42] = 3.8783326148986816f;
//            weights_out[43] = 1.8775659799575806f;
//            weights_out[44] = 0.5955561995506287f;
//            weights_out[45] = 5.965015411376953f;
//            weights_out[46] = -1.4358479976654053f;
//            weights_out[47] = -0.40194785594940186f;
//            weights_out[48] = 5.883052349090576f;
//            weights_out[49] = 0.8940021991729736f;
//            weights_out[50] = 0.7600221633911133f;
//            weights_out[51] = 16.377397537231445f;
//            weights_out[52] = 5.833582401275635f;
//            weights_out[53] = 5.615663051605225f;
//            weights_out[54] = 5.9257001876831055f;
//            weights_out[55] = 0.6445311307907104f;
//            weights_out[56] = -1.1628108024597168f;
//            weights_out[57] = 16.239910125732422f;
//            weights_out[58] = -2.8111228942871094f;
//            weights_out[59] = -3.597381114959717f;
//            bias_out[0] = -20.177616119384766f;
//            bias_out[1] = 2.497835636138916f;
//            bias_out[2] = -17.362316131591797f;
//            bias_out[3] = -15.145865440368652f;
//            bias_out[4] = -17.622142791748047f;
//            bias_out[5] = -17.146181106567383f;
//            bias_out[6] = -19.921977996826172f;
//            bias_out[7] = -17.11701774597168f;
//            bias_out[8] = -9.608945846557617f;
//            bias_out[9] = 7.162945747375488f;
//            bias_out[10] = -19.751569747924805f;
//            bias_out[11] = -18.97005271911621f;
//            bias_out[12] = -15.211738586425781f;
//            bias_out[13] = -2.018737316131592f;
//            bias_out[14] = -18.828340530395508f;
//            bias_out[15] = -17.57478141784668f;
//            bias_out[16] = -18.07686424255371f;
//            bias_out[17] = -17.510927200317383f;
//            bias_out[18] = -16.068052291870117f;
//            bias_out[19] = -16.435142517089844f;
//            break;
//        case 1:
//            weights_out[0] = 0.4571332335472107f;
//            weights_out[1] = 0.369848370552063f;
//            weights_out[2] = -0.2183680683374405f;
//            weights_out[3] = 0.4390034079551697f;
//            weights_out[4] = -1.7147407531738281f;
//            weights_out[5] = 0.5035991072654724f;
//            weights_out[6] = -3.231074094772339f;
//            weights_out[7] = -0.6160842180252075f;
//            weights_out[8] = 0.1262763887643814f;
//            weights_out[9] = -0.6194915175437927f;
//            weights_out[10] = -0.48036372661590576f;
//            weights_out[11] = 1.302878499031067f;
//            weights_out[12] = 0.45691150426864624f;
//            weights_out[13] = 0.37861010432243347f;
//            weights_out[14] = -0.14240297675132751f;
//            weights_out[15] = 0.4513198733329773f;
//            weights_out[16] = -0.983752429485321f;
//            weights_out[17] = -0.735744833946228f;
//            weights_out[18] = 0.2784736454486847f;
//            weights_out[19] = 1.930366039276123f;
//            bias_out[0] = 0.789627194404602f;
//            break;
//        default:
//            fprintf(stderr, "Unhandled ID init value: %d", id);
//    }
    switch(id) {
        case 0:
            weights_out[0] = 0.070820f;
            weights_out[1] = -1.686643f;
            weights_out[2] = 0.258346f;
            weights_out[3] = -0.314811f;
            weights_out[4] = -0.026931f;
            weights_out[5] = -0.027297f;
            weights_out[6] = -1.063958f;
            weights_out[7] = -1.649330f;
            weights_out[8] = -0.530226f;
            weights_out[9] = 0.238586f;
            weights_out[10] = -0.124147f;
            weights_out[11] = -0.222951f;
            weights_out[12] = -0.588873f;
            weights_out[13] = -1.521553f;
            weights_out[14] = -0.021012f;
            weights_out[15] = 0.008623f;
            weights_out[16] = -0.514678f;
            weights_out[17] = 0.385743f;
            weights_out[18] = -0.849239f;
            weights_out[19] = -1.905250f;
            weights_out[20] = -0.325808f;
            weights_out[21] = 0.235092f;
            weights_out[22] = 0.471694f;
            weights_out[23] = -0.137155f;
            weights_out[24] = -0.640861f;
            weights_out[25] = 0.972564f;
            weights_out[26] = 0.369690f;
            weights_out[27] = 0.933077f;
            weights_out[28] = -0.871878f;
            weights_out[29] = 0.531618f;
            weights_out[30] = -0.741372f;
            weights_out[31] = 0.124006f;
            weights_out[32] = -1.120049f;
            weights_out[33] = -0.065685f;
            weights_out[34] = -1.766974f;
            weights_out[35] = -0.344865f;
            weights_out[36] = -0.296009f;
            weights_out[37] = 0.499985f;
            weights_out[38] = 0.565063f;
            weights_out[39] = -0.541229f;
            weights_out[40] = -1.157844f;
            weights_out[41] = -0.290059f;
            weights_out[42] = -0.307535f;
            weights_out[43] = 0.397449f;
            weights_out[44] = -0.389477f;
            weights_out[45] = 0.207116f;
            weights_out[46] = 0.079241f;
            weights_out[47] = 0.851513f;
            weights_out[48] = -0.506086f;
            weights_out[49] = 2.884640f;
            weights_out[50] = 0.618516f;
            weights_out[51] = -0.659263f;
            weights_out[52] = -1.078610f;
            weights_out[53] = 0.613672f;
            weights_out[54] = -0.585248f;
            weights_out[55] = -0.010013f;
            weights_out[56] = -1.005075f;
            weights_out[57] = -0.335567f;
            weights_out[58] = -1.909947f;
            weights_out[59] = -0.275814f;
            weights_out[60] = -0.650540f;
            weights_out[61] = -0.065693f;
            weights_out[62] = 1.049102f;
            weights_out[63] = -0.749182f;
            weights_out[64] = -0.703077f;
            weights_out[65] = 0.059737f;
            weights_out[66] = -0.591329f;
            weights_out[67] = 0.006776f;
            weights_out[68] = 1.020539f;
            weights_out[69] = 0.287909f;
            weights_out[70] = -0.527831f;
            weights_out[71] = 0.020074f;
            weights_out[72] = -0.309146f;
            weights_out[73] = -1.862594f;
            weights_out[74] = -0.271767f;
            weights_out[75] = 0.371275f;
            weights_out[76] = 0.554135f;
            weights_out[77] = 0.447712f;
            weights_out[78] = 0.333255f;
            weights_out[79] = 1.084614f;
            weights_out[80] = 1.217827f;
            weights_out[81] = 0.028071f;
            weights_out[82] = 1.893664f;
            weights_out[83] = 0.390634f;
            weights_out[84] = 0.438091f;
            weights_out[85] = -0.483448f;
            weights_out[86] = -0.306473f;
            weights_out[87] = -0.376355f;
            weights_out[88] = 1.181076f;
            weights_out[89] = 0.392533f;
            weights_out[90] = -0.726664f;
            weights_out[91] = 0.128744f;
            weights_out[92] = -0.050210f;
            weights_out[93] = 1.153073f;
            weights_out[94] = -1.876594f;
            weights_out[95] = -0.420153f;
            weights_out[96] = -1.152043f;
            weights_out[97] = -1.314069f;
            weights_out[98] = -1.054250f;
            weights_out[99] = 1.085725f;
            weights_out[100] = -1.772250f;
            weights_out[101] = -0.477263f;
            weights_out[102] = -0.696031f;
            weights_out[103] = -0.468646f;
            weights_out[104] = -1.023052f;
            weights_out[105] = 0.018332f;
            weights_out[106] = -1.828656f;
            weights_out[107] = -0.391693f;
            weights_out[108] = 0.027730f;
            weights_out[109] = 0.296705f;
            weights_out[110] = 0.949307f;
            weights_out[111] = -0.295660f;
            weights_out[112] = -0.942141f;
            weights_out[113] = 0.032130f;
            weights_out[114] = 0.346597f;
            weights_out[115] = 2.340396f;
            weights_out[116] = 0.354109f;
            weights_out[117] = -0.048730f;
            weights_out[118] = -3.519576f;
            weights_out[119] = -0.659793f;
            bias_out[0] = 0.235605f;
            bias_out[1] = 0.069926f;
            bias_out[2] = -0.063434f;
            bias_out[3] = 0.344924f;
            bias_out[4] = 0.278412f;
            bias_out[5] = 0.065922f;
            bias_out[6] = 0.882032f;
            bias_out[7] = 0.491336f;
            bias_out[8] = -0.619817f;
            bias_out[9] = -0.084131f;
            bias_out[10] = 0.049254f;
            bias_out[11] = 0.058526f;
            bias_out[12] = -0.208792f;
            bias_out[13] = -0.226145f;
            bias_out[14] = -0.045618f;
            bias_out[15] = -0.123508f;
            bias_out[16] = 0.595596f;
            bias_out[17] = -0.287956f;
            bias_out[18] = 0.100733f;
            bias_out[19] = 0.377378f;
            bias_out[20] = 0.463590f;
            bias_out[21] = 0.365009f;
            bias_out[22] = -0.141469f;
            bias_out[23] = -0.165372f;
            bias_out[24] = 0.348241f;
            bias_out[25] = -0.227473f;
            bias_out[26] = 0.032296f;
            bias_out[27] = 0.006809f;
            bias_out[28] = 0.388539f;
            bias_out[29] = 0.606456f;
            bias_out[30] = -0.280829f;
            bias_out[31] = 0.332161f;
            bias_out[32] = -0.430890f;
            bias_out[33] = 0.477979f;
            bias_out[34] = -0.174344f;
            bias_out[35] = -0.059217f;
            bias_out[36] = 0.187336f;
            bias_out[37] = 0.571280f;
            bias_out[38] = 0.928801f;
            bias_out[39] = -0.032596f;
            break;
        case 1:
            weights_out[0] = 0.104259f;
            weights_out[1] = -0.019090f;
            weights_out[2] = -0.528524f;
            weights_out[3] = -0.172529f;
            weights_out[4] = -0.614005f;
            weights_out[5] = -0.342345f;
            weights_out[6] = 0.680585f;
            weights_out[7] = -0.640064f;
            weights_out[8] = 0.409166f;
            weights_out[9] = -0.778165f;
            weights_out[10] = -0.038249f;
            weights_out[11] = 0.387383f;
            weights_out[12] = 0.433580f;
            weights_out[13] = -0.945121f;
            weights_out[14] = 0.256362f;
            weights_out[15] = 0.454647f;
            weights_out[16] = -0.786431f;
            weights_out[17] = -0.570526f;
            weights_out[18] = -0.165656f;
            weights_out[19] = 0.764445f;
            weights_out[20] = -0.398150f;
            weights_out[21] = -0.323447f;
            weights_out[22] = 0.307289f;
            weights_out[23] = 0.010296f;
            weights_out[24] = 0.728104f;
            weights_out[25] = 0.159156f;
            weights_out[26] = -0.614183f;
            weights_out[27] = -0.360886f;
            weights_out[28] = -0.288471f;
            weights_out[29] = -0.300612f;
            weights_out[30] = -0.954700f;
            weights_out[31] = -0.901169f;
            weights_out[32] = -0.318425f;
            weights_out[33] = -0.792885f;
            weights_out[34] = -0.210443f;
            weights_out[35] = 0.162702f;
            weights_out[36] = 0.570939f;
            weights_out[37] = -0.175069f;
            weights_out[38] = 1.005261f;
            weights_out[39] = 1.457759f;
            bias_out[0] = -0.054691f;
            break;
        default:
            fprintf(stderr, "Unhandled ID init value: %d", id);
    }
}


void actionSampler(int size,
                   IN float *sigma_in, IN const float *action_in,
                   OUT float *action_out) {
    // Pre-compute constant value
    float sigma = sigma_in[0];
    for (int i = 0; i < size; ++i) {
        float mu = action_in[i];
        action_out[i] = normalSampler(mu, sigma);
    }
//    fprintf(stderr, "mu: %f sigma: %f action: %f \n", action_in[0], sigma, action_out[0]);
}

void validActor(IN float *sigma,
                OUT int *valid) {
    valid[0] = 0;
    if (sigma[0] > 0.f) {
        valid[0] = 1;
    }
}

void sigmaGen(OUT float *sigma) {
    static float sigma_static = SIGMA_GAUSSIAN;
    static int timestep = 0;
    sigma[0] = sigma_static;
    // Sigma decay

    sigma_static = (float)(timestep) * (-SIGMA_GAUSSIAN / 20000.f) + SIGMA_GAUSSIAN;
    timestep = (timestep + 1) % 20000;
    if (timestep == 0) {
        sigma_static = SIGMA_GAUSSIAN;
    }
}

void actorLearningRateGen(OUT float *learning_rate) {
    learning_rate[0] = ACTOR_LEARNING_RATE;
}


void saveNetWork(int n_layer,
                 IN int *size_layer_weights, IN int * size_layer_bias, IN float **weights, IN float **bias) {
    FILE *file = NULL;
    file = fopen("./network.txt", "wr+");
    if (file) {
        char integer[3] = "%d";
        fprintf(file, "void actorWeightGenInit(int id, OUT float *weights_out, OUT float *bias_out) {\n");
        fprintf(file, "\tswitch(id) {\n");
        int offset_weights = 0;
        int offset_bias = 0;
        for (int i = 0; i < n_layer; ++i) {
            fprintf(file, "\t\tcase %d:\n", i);
            int w_size = size_layer_weights[i];
            int b_size = size_layer_bias[i];
            for (int w = 0; w < w_size; ++w) {
                fprintf(file, "\t\t\tweights_out[%d] = %ff;\n", w, weights[i][w]);
            }
            for (int b = 0; b < b_size; ++b) {
                fprintf(file, "\t\t\tbias_out[%d] = %ff;\n", b, bias[i][b]);
            }
            fprintf(file, "\t\t\tbreak;\n");
            offset_bias += b_size;
            offset_weights += w_size;
        }
        fprintf(file, "\t\tdefault:\n");
        fprintf(file, "\t\t\tfprintf(stderr, \"Unhandled ID init value: %s\", id);\n", integer);
        fprintf(file, "\t}\n");
        fprintf(file, "}\n");
        fclose(file);
    }
}