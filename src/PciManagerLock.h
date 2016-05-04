/*
 * PciManagerLock.h
 *
 *  Created on: 13. 2. 2016
 *      Author: jindra
 */

#ifndef LIBRARIES_PCIMANAGER_SRC_PCIMANAGERLOCK_H_
#define LIBRARIES_PCIMANAGER_SRC_PCIMANAGERLOCK_H_

#include <PciManager.h>
#include <stdbool.h>

class PciManagerLock {
public:
    PciManagerLock() {
        PciManager.setEnabled(false);
    }
    ~PciManagerLock() {
        PciManager.setEnabled(true);
    }
};

#endif /* LIBRARIES_PCIMANAGER_SRC_PCIMANAGERLOCK_H_ */
