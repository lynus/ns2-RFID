#ifndef RFID_TMAC_H

#define RFID_TMAC_H
#include "mac.h"
#include "address.h"
#include "ip.h"
#include "rfidTagent.h"
#include "rmac.h"  //declare RfidTimer

class RfidTMac : public Mac{
friend class LTimer;
public:
	RfidTMac();
	void recv(Packet *p,Handler *h);
	int command(int,const char*const);
	inline void debug(char *mesg);
private:
	Packet *pktRx;
	packet *pktTx;
	RfidTAgent *agent;
};

