
#include "rfid_hdr.h"
#include "rfidTagent.h"
#include "packet.h"
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
	if (argc==3){
		if (strcmp(argv[1],"set-mac")==0){
			if((mac =(NsObject*)TclObject::lookup(argv[2]))==0){
				fprintf(stderr,"rfidRAgent(set-mac) failed\n");
				return TCL_ERROR;
			}
		}
		return TCL_OK;
	}

	Agent::command(argc,argv);
	return TCL_OK;
}

void RfidTAgent::recv(Packet* pkt,Handler*)
{
	hdr_ip* iph=HDR_IP(pkt);
	rfid_hdr *rfidh = HDR_RFID(pkt);
	if ((u_int32_t)iph->daddr() == IP_BROADCAST) {
		fprintf(stderr,"tag#%d.%d recv %s from reader#%d.%d\n",
			here_.addr_,here_.port_,rfidh->comment,
			iph->saddr(),iph->sport());
		//XXX test for answer to query command
		 if (HDR_RFID(pkt)->cmd == RFID_QUERY){
			 Packet *p=mkPacket(RFID_RN16,"ack_to_query\0");
			 mac->recv(p,(Handler*)0);
		 }
		Packet::free(pkt);
		return;	
	} 
}
Packet *RfidTAgent::mkPacket(int cmd,char *comment="no comment\0"){
	Packet *pkt=allocpkt();
	rfid_hdr *rh = HDR_RFID(pkt);
	hdr_cmn *ch = HDR_CMN(pkt);
	rh->cmd=RFID_RN16;
	strcpy(rh->comment,comment);
	ch->direction()=hdr_cmn::DOWN;
	hdr_ip *ih=HDR_IP(pkt);
	ih->daddr()=IP_BROADCAST;
	ih->dport()=RAgentPort;
	return pkt;
}
