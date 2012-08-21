#ifndef RFID_RMAC_H
#define RFID_RMAC_H
#include "mac.h"
#include "address.h"
#include "ip.h"
#include "rfidRagent.h"
class LTimer;
class RfidRMac : public Mac {
friend class LTimer;
public:
	RfidRMac();
	void recv(Packet *p,Handler *h);
	//void send(Packet *p,Handler *h);
	int command(int argc,const char*const*);
	virtual void debug(char *mesg){
		fprintf(stderr,"rmac debug:%s\n",mesg);
	}
private:
	Packet* pktRx;
	Packet* pktTx;
	RfidRAgent* agent; // the Ragent this mac is beneath
	LTimer* ltimer;
	void timeup();
};

class RfidTimer : public Handler {
public:
	RfidTimer(RfidRMac* m) : mac(m) {
		busy=0;
	}
	virtual void handle(Event *e)=0;
	virtual void start(double time);
	virtual void restart(double time);
	virtual void stop();
	virtual void reset();
	inline int isbusy(){return busy;}
	inline double expire(){
		return (stime+rtime- 
				Scheduler::instance().clock());
	}

protected:
	RfidRMac	*mac;
	int 		busy;
	double 		stime;
	double 		rtime;
	Event		intr;
};
class LTimer : public RfidTimer {
public:
	LTimer(RfidRMac *m) : RfidTimer(m) {
		busy=0;
	}
	void handle(Event *e);
};

#endif
