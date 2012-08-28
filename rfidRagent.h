#ifndef rfidRagent
#define rfidRagent
#include "rfid_hdr.h"
#include "timer-handler.h"
class Listener;
class RfidRAgent : public Agent {
friend class Listener;
public:
	RfidRAgent();
	int state;

	virtual int command(int argc,const char* const* argv);
	virtual void recv(Packet*,Handler*);
	virtual void handle(Event* p){
		fprintf(stderr,"RfidRagent handle() called\n");
	}
	void timeup(){
		fprintf(stderr,"rmac timeup\n");
	}
protected:
	NsObject *mac; 
	Listener *listener;
	Packet *mkPacket(int cmd,char *comment);
	double qfp;
	int q;
	int lst_flag;		//listener flag
};

enum Ragent_state {
	RAGENT_READY= 1,
	RAGENT_LISTEN,
	/**
	RAGENT_
	 */
};
enum lst_state {
	LST_NA = 1,
	LST_TIMEOUT,
	LST_HIT,
	LST_COLL
};
class Listener : public TimerHandler{
public:
	Listener(RfidRAgent *a):TimerHandler(),agent(a){}
	inline virtual void expire(Event *e);
protected:
	RfidRAgent *agent;
};
#endif
