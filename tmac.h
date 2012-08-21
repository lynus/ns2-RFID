#ifndef RFID_TMAC_H

#define RFID_TMAC_H
#include "mac.h"
#include "address.h"
#include "ip.h"
#include "rfidTagent.h"
#include "rmac.h"  //declare RfidTimer
inline bool isFromReader(Packet *);
class RfidTMac : public Mac{
friend class LTimer;
public:
	RfidTMac();
	void recv(Packet *p,Handler *h);
	virtual int command(int argc,const char*const* argv);
	inline void debug(char *mesg);
private:
	Packet *pktRx;
	Packet *pktTx;
	RfidTAgent *agent;
};

#endif
