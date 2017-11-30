//
// Created by farresti on 30/11/17.
//

#ifndef CACLA_COMMON_H
#define CACLA_COMMON_H

#define N_SAMPLING_SIZE 50

#ifndef M_PI
    #define M_PI 3.1415926535897932385f
#endif

#define MODF(a,b) ((a) - (b) * (int)((a) / (b)))
#define POW2(x) ((x) * (x))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

/**
 * @brief Samples a random variable following a normal distribution.
 *        Each distribution is parameterized by mu and
 *        sigma = sigma
 *        The behavior is as follows, N random (normal) values are sampled
 *        and then a value is chosen uniformly among these N values and returned.
 *
 * @param sigma  Standard deviation of the distribution.
 * @param mu     Center value of the distribution.
 * @return random sample following the normal law.
 */
float normalSampler(float mu, float sigma);

/**
 * @brief Functions that returns uniformly either 1 or -1.
 *        The function samples 10 uniform values and choose
 *        one uniformly in this array.
 *
 * @return -1 or 1
 */
int randomSign(void);

#endif //CACLA_COMMON_H
