/**
 * File: PciManager.h
 * Description:
 * PciManager library is an easy to use Pin Change Interrupt manager for Arduino.
 *
 * Author: Balazs Kelemen
 * Contact: prampec+arduino@gmail.com
 * Copyright: 2012 Balazs Kelemen
 * Copying permission statement:
 This file is part of PciManager.

 PciManager is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.

 */

#ifndef PCIMANAGER_H
#define PCIMANAGER_H

#include <PciListener.h>
#include <stdbool.h>
#include <stdint.h>

/**
 * Register PCI listeners to pins with this Manager class.
 * The listener will be called on pin change of the vector of pins that this pin belongs to. So you always have
 * to check if your pin was changed or not. 
 */
class PciManagerT {
public:

    PciManagerT();
    PciManagerT(const PciManagerT& that) = delete;
    void operator=(const PciManagerT& that) = delete;

    /**
     * Register a pin for pin change interrupt. Same as above but the pin needs to be configured in the listener.
     *  listener - The lister that is called on pin change. Note, that as matters stand, you souldn't register
     *    a listener multiply times (e.g. for more pins).
     */
    void registerListener(PciListener* listener);
    /**
     * Remove registration of a pin for PCI.
     *  listener - The that should be removed.
     */
    void removeListener(PciListener* listener);

    /**
     * For internal use only.
     */
    void callListeners(uint8_t pciVectorId);

    volatile bool isEnabled() const {
        return enabled;
    }

    void setEnabled(volatile bool enabled) {
        this->enabled = enabled;
    }

private:
    PciListener* firstListener;
    PciListener* lastListener;

    volatile bool enabled;
};

extern PciManagerT PciManager;

#endif
