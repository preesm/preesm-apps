#ifndef ORDERED_CHAINED_LIST_H
#define ORDERED_CHAINED_LIST_H

#include <stdlib.h>

template<typename T>
struct Element {
  size_t elementIndex; // we can avoid it with pointer arithmetic
  struct Element<T> * next;
};

template<typename T>
struct OrderedList {
  struct Element<T> * allEl;
  T * allVal;
  size_t beginIndex;
  size_t size;
  size_t max;
};

template<typename T>
struct OrderedList<T> * CreateOrdList(size_t nbEls) {
  if (nbEls < 1) {
    return NULL;
  }
  struct OrderedList<T> * l = (struct OrderedList<T> *) malloc(sizeof(struct OrderedList<T>));
  l->allEl = (struct Element<T> *) malloc(sizeof(struct Element<T>)*nbEls);
  l->allVal = (T *) malloc(sizeof(T)*nbEls);
  l->beginIndex = 0;
  l->size = 0;
  l->max = nbEls;
  return l;
}


template<typename T>
int getSize(struct OrderedList<T> * list) {
  return list->size;
}

template<typename T>
T * getUnorderedVals(struct OrderedList<T> * list) {
  return list->allVal;
}

template<typename T>
int addElementUnordered(struct OrderedList<T> * list, T * val) {
  int l_size = list->size;
  if (l_size == list->max) {
    return EXIT_FAILURE;
  }
  if (l_size == 0) {
    list->beginIndex = 0;
  } else {
    list->allEl[l_size-1].next = &(list->allEl[l_size]);
  }
  memcpy(&(list->allVal[l_size]), val, sizeof(T));
  list->allEl[l_size].elementIndex = l_size;
  list->size++;
  return EXIT_SUCCESS;
}

// the comparator must return 0 if both elements are equal, any other value otherwise
template<typename T>
int addElementUnique(struct OrderedList<T> * list, T * val, int (*comparisonFunction)(T * val_in_list, T * val_to_add)) {
  size_t l_size = list->size;
  if (l_size == list->max) {
    return EXIT_FAILURE;
  }
  if (l_size == 0) {
    list->beginIndex = 0;
  } else {
    short goForward = 1;
    for (size_t i = 0; i < l_size; ++i) {
      goForward = (*comparisonFunction)(&(list->allVal[i]), val);
      if (goForward == 0) {
	return EXIT_FAILURE;
      }
    }
    list->allEl[l_size-1].next = &(list->allEl[l_size]);
  }
  memcpy(&(list->allVal[l_size]), val, sizeof(T));
  list->allEl[l_size].elementIndex = l_size;
  list->size++;
  return EXIT_SUCCESS;
}



// the comparator must return -1 if value to insert is below the value in the list, 1 for the opposite
// and 0 if equality
template<typename T>
void addElement(struct OrderedList<T> * list, T * val, int (*comparisonFunction)(T * val_in_list, T * val_to_add)) {
  if (list->size == 0) {
    list->size = 1;
    list->allEl[0].next = NULL;
    list->allEl[0].elementIndex = 0;
    memcpy(list->allVal, val, sizeof(T));
    return;
  }

  short goForward = 1;
  struct Element<T> * el = &(list->allEl[list->beginIndex]);
  struct Element<T> * prev_el = NULL;
  while (el != NULL) {
    goForward = (*comparisonFunction)(&(list->allVal[el->elementIndex]), val);
    if (goForward == 1) {
      prev_el = el;
      el = el->next;
    } else {
      break;
    }
  }
  /* if (goForward == 0) { */
  /*   return; */
  /* } */

  size_t copyIndex = list->size;

  if (prev_el == NULL) {
    if (list->size == list->max) {
      return;
    } else {
      list->beginIndex = copyIndex;
      list->allEl[copyIndex].elementIndex = copyIndex;
      list->size++;
    }
  } else {
    if (list->size == list->max) {
      copyIndex = list->beginIndex;
      if (prev_el->elementIndex == copyIndex) {
	list->beginIndex = copyIndex;
      } else {
	list->beginIndex = list->allEl[copyIndex].next->elementIndex;
	prev_el->next = &(list->allEl[copyIndex]);
      }
    } else {
      list->allEl[copyIndex].elementIndex = copyIndex;
      prev_el->next = &(list->allEl[copyIndex]);
      list->size++;
    }
  }
  
  memcpy(&(list->allVal[copyIndex]), val, sizeof(T));    
  list->allEl[copyIndex].next = el;  
}




template<typename T>
void release(struct OrderedList<T> * list) {
  free(list->allEl);
  free(list->allVal);
  free(list);
}


  
#endif
