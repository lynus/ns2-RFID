#include "rfid_hdr.h"
#include "rfidTagent.h"
static class RfidTAgentClass : public TclClass {
public:
	RfidTAgentClass() : TclClass("Agent/RfidTAgent") {}
	TclObject* create(int ,const char* const*){
		return (new RfidTAgent());
	}
}class_RfidTAgent;

RfidTAgent::RfidTAgent() : Agent(PT_RFID),state(1)
{
	bind("packetSize_",&size_);
}
int RfidTAgent::command(int argc,const char* const* argv){
	if (argc==2){
	}
	Agent::command(argc,argv);
	return TCL_OK;
}

void RfidTAgent::recv(Packet* pkt,Handler*)
{
	hdr_ip* iph=HDR_IP(pkt);
	rfid_hdr* rfidh =HDR_RFID(pkt);
	if ((u_int32_t)iph->daddr() == IP_BROADCAST) {
		printf("tag#%d.%d recv %s from reader#%d.%d\n",
			here_.addr_,here_.port_,rfidh->comment,
			iph->saddr(),iph->sport());
		Packet:free(pkt);
		return;	
	} 
}
