/**
 * *****************************************************************************
 * Copyright or © or Copr. IETR/INSA: Maxime Pelcat, Jean-François Nezan,
 * Karol Desnos, Julien Heulot, Clément Guy, Yaset Oliva Venegas
 *
 * [mpelcat,jnezan,kdesnos,jheulot,cguy,yoliva]@insa-rennes.fr
 *
 * This software is a computer program whose purpose is to prototype
 * parallel applications.
 *
 * This software is governed by the CeCILL-C license under French law and
 * abiding by the rules of distribution of free software.  You can  use,
 * modify and/ or redistribute the software under the terms of the CeCILL-C
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
 * knowledge of the CeCILL-C license and that you accept its terms.
 * ****************************************************************************
 */

#include <spider.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include "ddpg.h"

static char *shMemBuffer = nullptr;

void initArchi() {

	/* === Init SpiderArchiConfig structure === */

	SpiderArchiConfig config;
	config.nPE = N_PE;
	config.nPEType = N_PE_TYPE;
	config.nMemoryUnit = 1;

	/* === Create Archi === */

	auto *archi = Spider::createArchi(config);

	/* === Create the different MemoryUnit(s) === */

	shMemBuffer = (char *) std::malloc(SH_MEM_SIZE);
	if (!shMemBuffer) {
		fprintf(stderr, "ERROR: failed to allocate [%X] bytes for MemoryUnit [%s]\n", SH_MEM_SIZE, "shared-memory");
		exit(-1);
	}
	auto *shMem = Spider::createMemoryUnit(shMemBuffer, SH_MEM_SIZE);
	memset(shMemBuffer, 0, SH_MEM_SIZE);

	/* === Create the different PE(s) === */

	/* == CORE_TYPE_X86 == */
	auto *peX86Core0 = Spider::createPE(
		static_cast<std::uint32_t>(PEType::CORE_TYPE_X86),
		static_cast<std::uint32_t>(PEHardwareID::CORE_CORE0),
		static_cast<std::uint32_t>(PEVirtID::CORE_CORE0),
		"org.preesm.model.slam.impl.OperatorImpl@27c4201d-Core0",
		SpiderPEType::LRT_PE,
		SpiderHWType::PHYS_PE);
	Spider::setPEMemoryUnit(peX86Core0, shMem);

	/* === Set Spider GRT core === */

	Spider::setSpiderGRTVirtualID(archi, static_cast<std::uint32_t>(PEVirtID::CORE_CORE0));
}

void freeArchi() {

	/* === Freeing memory buffer allocated for MemoryUnit(s) === */

	if (shMemBuffer) {
		std::free(shMemBuffer);
		shMemBuffer = nullptr;
	}
}
