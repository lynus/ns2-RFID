#ifndef RFIDTAGENT
#define RFIDTAGENT

#include "rfid_hdr.h"

class RfidTAgent : public Agent {
public:
	RfidTAgent();
	int state;

	virtual int command(int argc,const char* const* argv);
	virtual void recv(Packet *,Handler*);
};

#endif
