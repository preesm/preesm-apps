/*
 * Copyright or © or Copr. IETR/INSA - Rennes (2018) :
 *
 * Antoine Morvan <antoine.morvan@insa-rennes.fr> (2018)
 * Florian Arrestier <florian.arrestier@insa-rennes.fr> (2017-2019)
 *
 * Spider is a dataflow based runtime used to execute dynamic PiSDF
 * applications. The Preesm tool may be used to design PiSDF applications.
 *
 * This software is governed by the CeCILL  license under French law and
 * abiding by the rules of distribution of free software.  You can  use,
 * modify and/ or redistribute the software under the terms of the CeCILL
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * "http://www.cecill.info".
 *
 * As a counterpart to the access to the source code and  rights to copy,
 * modify and redistribute granted by the license, users are provided only
 * with a limited warranty  and the software's author,  the holder of the
 * economic rights,  and the successive licensors  have only  limited
 * liability.
 *
 * In this respect, the user's attention is drawn to the risks associated
 * with loading,  using,  modifying and/or developing or reproducing the
 * software by the user in light of its specific status of free software,
 * that may mean  that it is complicated to manipulate,  and  that  also
 * therefore means  that it is reserved for developers  and  experienced
 * professionals having in-depth computer knowledge. Users are therefore
 * encouraged to load and test the software's suitability as regards their
 * requirements in conditions enabling the security of their systems and/or
 * data to be ensured and,  more generally, to use and operate it in the
 * same conditions as regards security.
 *
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL license and that you accept its terms.
 */

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include "switch.h"

void selector(OUT Param *value) {
    int choice = -1;
    while (choice != 0 && choice != 1) {
        fprintf(stderr, "Choose an algorithm (0, 1): ");
        auto ret = fscanf(stdin, "%d", &choice);
        if (ret != 1) {
            fprintf(stderr, "ERROR: fscanf failed\n");
        }
    }
    /* == Flush the input buffer == */
    while (fgetc(stdin) != '\n');
    (*value) = choice;
    fprintf(stderr, "Using branch %d\n", choice);
}

void dataProvider(OUT char *data) {
	const char *valueToSend = "1337";
	strcpy(data, valueToSend);
	fprintf(stderr, "INFO:%s: sending value [%s].\n", __FUNCTION__, data);
}

void branchZero(IN char *data) {
	fprintf(stderr, "INFO:%s: value [%s] was set by user.\n", __FUNCTION__, data);
}

void branchOne(IN char *data) {
	fprintf(stderr, "INFO:%s: value [%s] was set by user.\n", __FUNCTION__, data);
}
