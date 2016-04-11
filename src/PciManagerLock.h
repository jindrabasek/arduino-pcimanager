/*
 * PciManagerLock.h
 *
 *  Created on: 13. 2. 2016
 *      Author: jindra
 */

#ifndef LIBRARIES_PCIMANAGER_SRC_PCIMANAGERLOCK_H_
#define LIBRARIES_PCIMANAGER_SRC_PCIMANAGERLOCK_H_

#include "PciManager.h"

class PciManagerLock {
public:
    PciManagerLock() {
        PciManager::instance().setEnabled(false);
    }
    ~PciManagerLock() {
        PciManager::instance().setEnabled(true);
    }
};

#endif /* LIBRARIES_PCIMANAGER_SRC_PCIMANAGERLOCK_H_ */
