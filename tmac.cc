#include "tmac.h"
#include "rfid_hdr.h"

#define SLOT_F 6e-6

static class RfidTMacClass : public TclClass {
public:
	RfidRMacClass() : TclClass("Mac/T-Rfid") {}
	TclObject* create(int,const char* const*) {
		return new RfidTMac();
	}
}class_rfidtmac;

RfidTMac::RfidTMac() : Mac() {
}


