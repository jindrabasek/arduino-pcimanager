/*
 * PciListener.cpp
 *
 *  Created on: 14. 1. 2016
 *      Author: jindra
 */

#include "PciListener.h"

PciListener::PciListener(byte pciPin) :
		pciPin(pciPin),
		pciVector(digitalPinToPCICRbit(pciPin)),
		pciNextListener(NULL),
		prevToThisListener(NULL) {
}

void PciListener::remove() {
	if (prevToThisListener != NULL) {
		*prevToThisListener = pciNextListener;
		prevToThisListener = NULL;
		pciNextListener = NULL;
	}
}

