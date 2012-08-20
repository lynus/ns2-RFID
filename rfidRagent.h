#ifndef rfidRagent
#define rfidRagent
#include "rfid_hdr.h"

class RfidRAgent : public Agent {
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
	
};

enum Ragent_state {
	RAGENT_READY= 1,
	RAGENT_LISTEN,
	/**
	RAGENT_
	 */
};
#endif
