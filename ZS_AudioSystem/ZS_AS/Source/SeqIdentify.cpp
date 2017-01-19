/*
  ==============================================================================

    SeqIdentify.cpp
    Created: 19 Jan 2017 1:29:23pm
    Author:  SDUser

  ==============================================================================
*/

#include "SeqIdentify.h"

SeqIdentify::SeqIdentify(int seq[16]) {
	for (unsigned i = 0; i < 16; i++) {
		if (i < sizeof(seq)) {
			seqInput[i] = seq[i];
		}
		else {
			seqInput[i] = 0;
		}
	}

}
SeqIdentify::SeqIdentify() {
	for (unsigned i = 0; i < 16; i++) {
		seqInput[i] = 0;
	}
}