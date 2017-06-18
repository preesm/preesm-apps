#ifndef BP1D_NODE_H_
#define BP1D_NODE_H_

#include <stdint.h>

typedef uint16_t node_type;

typedef struct node
{
	node_type M;
	node_type B;
}node;


typedef uint8_t phib_type;
typedef node fi_type;
typedef uint16_t energy_type;

#define	F_BIG				30000

#endif