#include <stdio.h>

#define SIFT_IMG_DBL 1

#define SIFT_IMAGE_W 800
#define SIFT_IMAGE_H 640
#define SIFT_IMAGE_MAX 800

#define SIFT_pLevels 4
#define SIFT_nOctaves 7
#define SIFT_nDogLayers 5
#define SIFT_nGpyrLayers 6 //(SIFT_nDogLayers + 1)
#define SIFT_nLayers 3 //(SIFT_nGpyrLayers - 3)


static inline size_t tmin_s(size_t n1, size_t n2) {
  if (n1 < n2) {
    return n1;
  }
  return n2;
}


void ITERATOR_generic(int parallelismLevels, int nbLayers,
		      int * start_octave, int * stop_octave,
		      int * start_layer, int * stop_layer,
		      int * start_line,  int * stop_line,
		      int * start_col, int * stop_col) {


  start_octave[0] = 0;
  start_layer[0] = 0;
  start_line[0] = 0;
  start_col[0] = 0;

  int w[SIFT_nOctaves];
  w[0] = SIFT_IMAGE_W;
  int h[SIFT_nOctaves];
  h[0] = SIFT_IMAGE_H;
  if (SIFT_IMG_DBL) {
    w[0] *= 2;
    h[0] *= 2;
  }
  for (int i = 1; i < SIFT_nOctaves; i++) {
    w[i] = w[i-1] / 2;
    h[i] = h[i-1] / 2;
  }
  if (parallelismLevels == 1) {
    stop_octave[0] = SIFT_nOctaves;
    stop_layer[0] = nbLayers;
    stop_line[0] = h[SIFT_nOctaves-1];
    stop_col[0] = w[SIFT_nOctaves-1];
    return;
  }

  unsigned long iter_space = 0;

  for (int i = 0; i < SIFT_nOctaves; i++) {
    iter_space += w[i]*h[i];
  }
  iter_space *= nbLayers;

  unsigned long piter_space = iter_space/parallelismLevels;
  fprintf(stderr, "piter_space: %lu\n\n", piter_space);

  unsigned long citer_space = 0;
  int nOctaves = SIFT_nOctaves;
  int nLayers = nbLayers;
  int nLines = h[0];
  int nCols = w[0];
  
  for (int i = 0; i < SIFT_nOctaves; i++) {
    long tmp = citer_space + w[i]*h[i]*nbLayers;
    if (tmp <= piter_space) {
      citer_space = tmp;
    }
    if (tmp > piter_space) {
      nOctaves = i;
      break;
    }
  }
  if (citer_space < piter_space) {
    int size = w[nOctaves]*h[nOctaves];
    unsigned long diff = piter_space - citer_space;
    nLayers = diff / size;
    unsigned long offset = nLayers*size;
    citer_space += offset;
    if (diff - offset != 0) {
      nLayers++;
    }
  }
  if (citer_space < piter_space) {
    int size = w[nOctaves];
    unsigned long diff = piter_space - citer_space;
    nLines = diff / size;
    unsigned long offset = nLines*size;
    citer_space += offset;
    if (diff - offset != 0) {
      nLines++;
    }
  }

  if (citer_space < piter_space) {
    int size = 1;
    unsigned long diff = piter_space - citer_space;
    nCols = diff / size;
    citer_space += nCols*size;
  }
    
  stop_octave[0] = nOctaves + 1;
  stop_layer[0] = nLayers;
  stop_line[0] = nLines;
  stop_col[0] = nCols;

  unsigned long oiter_space = piter_space;
  for (int p = 1; p < parallelismLevels - 1; p++) {
    long prev_lack = oiter_space - citer_space;
    oiter_space = piter_space + prev_lack;
    fprintf(stderr, "prev_lack: %ld\tspace: %lu\n", prev_lack, oiter_space);
    int hC = h[stop_octave[p-1]-1];
    int cC = w[stop_octave[p-1]-1];
    citer_space = 0;
    nOctaves = SIFT_nOctaves;
    nLayers = nbLayers;
    nLines = hC;
    nCols = cC;

    int tmp = stop_col[p - 1] % cC; 
    start_col[p] = tmp;
    short endsLine = 0;
    long min = tmin_s(oiter_space, (size_t) (cC - tmp));
    nCols = tmp + (int) min;
    citer_space += min;
    if (nCols == cC) {
      endsLine = 1;
    }
    stop_col[p] = nCols;

    fprintf(stderr, "citer_space(0): %lu\tendsLine: %d\n", citer_space, endsLine);
    fprintf(stderr, "nCols(1): %d\n", nCols);

    tmp = (stop_col[p - 1] == cC) ? stop_line[p-1] % hC : stop_line[p-1] - 1;
    start_line[p] = tmp;
    tmp += endsLine;
    short endsLayer = 0;
    min = tmin_s((oiter_space - citer_space)/cC, (size_t) (hC - tmp));
    nLines = tmp + (int) min;
    citer_space += min*cC;
    if (nLines == hC) {
      endsLayer = 1;
    } else if (citer_space < oiter_space) {
      nLines++;
    }
    stop_line[p] = nLines;

    
    fprintf(stderr, "citer_space(0.1): %lu\tendsLayer: %d\n", citer_space, endsLayer);
    fprintf(stderr, "nLines(1): %d\n", nLines);

    
    tmp = ((stop_col[p - 1] == cC) && (stop_line[p - 1] == hC)) ? stop_layer[p-1] % nbLayers : stop_layer[p-1] - 1;
    start_layer[p] = tmp;
    tmp += endsLayer;
    short endsOctave = 0;
    min = tmin_s((oiter_space - citer_space)/(hC*cC), (size_t) (nbLayers - tmp));
    nLayers = tmp + (int) min;
    citer_space += min*cC*hC;
    if (nLayers == nbLayers) {
      endsOctave = 1;
    } else if (citer_space < oiter_space) {
      nLayers++;
    }
    stop_layer[p] = nLayers;

    
    fprintf(stderr, "citer_space(1): %lu\tendsOctave: %d\n", citer_space, endsOctave);
    fprintf(stderr, "nLayers(1): %d\n", nLayers);

    start_octave[p] = ((stop_col[p - 1] == cC) && (stop_line[p - 1] == hC) && (stop_layer[p - 1] == nbLayers)) ? stop_octave[p-1] : stop_octave[p-1] - 1;
    nOctaves = start_octave[p]+1;
    if (citer_space < oiter_space) {
      for (int i = start_octave[p] + endsOctave; i < SIFT_nOctaves; i++) {
	long tmp = citer_space + w[i]*h[i]*nbLayers;
	if (tmp <= oiter_space) {
	  citer_space = tmp;
	}
	if (tmp >= oiter_space) {
	  nOctaves = i + 1;
	  break;
	}
      }
    }
    stop_octave[p] = nOctaves;
    fprintf(stderr, "nOctaves: %d\n", nOctaves);

    if (stop_octave[p] > stop_octave[p-1]) {
      hC = h[stop_octave[p]-1];
      cC = w[stop_octave[p]-1];
      nLines = hC;
      nCols = cC;
    }
    
    if (citer_space < oiter_space && stop_octave[p] > stop_octave[p-1]) {
      int size = hC*cC;
      unsigned long diff = oiter_space - citer_space;
      nLayers = diff / size;
      unsigned long offset = nLayers*size;
      citer_space += offset;
      if (diff - offset != 0) {
	nLayers++;
      }
    }
    stop_layer[p] = nLayers;
    fprintf(stderr, "nLayers(2): %d\n", nLayers);

    if (citer_space < oiter_space && (stop_octave[p] > stop_octave[p-1] || stop_layer[p] > stop_layer[p-1])) {
      int size = cC;
      unsigned long diff = oiter_space - citer_space;
      fprintf(stderr, "diff: %lu\n", diff);
      nLines = diff / size;
      unsigned long offset = nLines*size;
      citer_space += offset;
      if (diff - offset != 0) {
	nLines++;
      }
    }
    stop_line[p] = nLines;
    fprintf(stderr, "nLines(2): %d\n", nLines);


    if (citer_space < oiter_space && (stop_octave[p] > stop_octave[p-1] || stop_layer[p] > stop_layer[p-1] || stop_line[p] > stop_line[p-1])) {
      int size = 1;
      unsigned long diff = oiter_space - citer_space;
      fprintf(stderr, "diff: %lu\n", diff);
      nCols = diff / size;
      unsigned long offset = nCols*size;
      citer_space += offset;
    }
    stop_col[p] = nCols;
    fprintf(stderr, "nCols(2): %d\n", nCols);

    fprintf(stderr, "citer_space(2): %lu\n\n", citer_space);
  }

  int hC = h[stop_octave[parallelismLevels-2]-1];
  int cC = w[stop_octave[parallelismLevels-2]-1];
  start_col[parallelismLevels - 1] = stop_col[parallelismLevels - 2] % cC;
  start_line[parallelismLevels - 1] = (stop_col[parallelismLevels - 2] == cC) ? stop_line[parallelismLevels - 2] % hC: stop_line[parallelismLevels - 2] - 1;
  start_layer[parallelismLevels - 1] = (stop_col[parallelismLevels - 2] == cC) && (stop_line[parallelismLevels - 2] == hC) ? stop_layer[parallelismLevels - 2] % nbLayers : stop_layer[parallelismLevels - 2] - 1;
  start_octave[parallelismLevels - 1] = (stop_col[parallelismLevels - 2] == cC) && (stop_line[parallelismLevels - 2] == hC) &&  (stop_layer[parallelismLevels - 2] == nbLayers) ? stop_octave[parallelismLevels - 2] : stop_octave[parallelismLevels - 2] - 1;
  
  stop_octave[parallelismLevels - 1] = SIFT_nOctaves;
  stop_layer[parallelismLevels - 1] = nbLayers;
  stop_line[parallelismLevels - 1] = h[SIFT_nOctaves - 1];
  stop_col[parallelismLevels - 1] = w[SIFT_nOctaves - 1];
  
}


int main(int argc, char ** argv) {

  int start_col[SIFT_pLevels];
  int start_line[SIFT_pLevels];
  int start_layer[SIFT_pLevels];
  int start_octave[SIFT_pLevels];
  int stop_col[SIFT_pLevels];
  int stop_line[SIFT_pLevels];
  int stop_layer[SIFT_pLevels];
  int stop_octave[SIFT_pLevels];

  ITERATOR_generic(SIFT_pLevels, SIFT_nGpyrLayers,
		   start_octave, stop_octave,
		   start_layer, stop_layer,
		   start_line,  stop_line,
		   start_col,  stop_col);
  
  for (int i = 0; i < SIFT_pLevels; i++) {
    fprintf(stderr, "%d-%d\t%d-%d\t%d-%d\t%d-%d\n", start_octave[i], stop_octave[i], start_layer[i], stop_layer[i], start_line[i], stop_line[i], start_col[i], stop_col[i]);
  }

  return 0;
}
