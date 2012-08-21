#include "tmac.h"
#include "rfid_hdr.h"
#include "packet.h"
#define SLOT_F 6e-6

static class RfidTMacClass : public TclClass {
public:
	RfidTMacClass() : TclClass("Mac/T-Rfid") {}
	TclObject* create(int,const char* const*) {
		return new RfidTMac();
	}
}class_rfidtmac;

RfidTMac::RfidTMac() : Mac() {
}

void RfidTMac::recv(Packet *p,Handler *h){
	hdr_cmn *ch=HDR_CMN(p);
	if(ch->direction()==hdr_cmn::UP){
		if (!isFromReader(p)){
			Packet::free(p);
			return;
	}
	uptarget_->recv(p,h);
	}
	else 
		downtarget_->recv(p,h);
	return;
}

int RfidTMac::command(int argc ,const char *const* argv){
	Mac::command(argc,argv);
	return TCL_OK;
}

inline bool isFromReader(Packet *p){
	return (HDR_RFID(p)->cmd!=RFID_RN16);
}
