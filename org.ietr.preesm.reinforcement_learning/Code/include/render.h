//
// Created by farresti on 31/10/17.
//

#ifndef CACLA_RENDER_H
#define CACLA_RENDER_H

#define DISPLAY_W 500
#define DISPLAY_H 500

#define PATH PROJECT_ROOT_PATH "/dat/pendulum.png"

void renderInit(void);

void renderEnv(int size, float *state);

void renderFinalize(void);

#endif //CACLA_RENDER_H
