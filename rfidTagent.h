#ifndef RFIDTAGENT
#define RFIDTAGENT

#include "rfid_hdr.h"

class RfidTAgent : public Agent {
public:
	RfidTAgent();
	int state;

	virtual int command(int argc,const char* const* argv);
	virtual void recv(Packet *,Handler*);
	void debug(char *msg){
		fputs(msg,stderr);
	}
protected:
	NsObject *mac;
	Packet *mkPacket(int,char*);
};

#endif
