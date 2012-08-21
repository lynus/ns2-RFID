#include "rfid_hdr.h"
#include "rfidRagent.h"
#include "string.h"
#include "mac.h"
int rfid_hdr::offset_;
static class RFIDHeaderClass : public PacketHeaderClass {
public:
	RFIDHeaderClass() : PacketHeaderClass ("PacketHeader/RFID",sizeof(rfid_hdr)){
		bind_offset(&rfid_hdr::offset_);
	}
}class_rfidhdr;

static class RfidRAgentClass : public TclClass {
public:
	RfidRAgentClass() : TclClass("Agent/RfidRAgent") {}
	TclObject* create(int, const char* const*) {
		return (new RfidRAgent());
	}
}class_RfidRAgent;

RfidRAgent::RfidRAgent() : Agent(PT_RFID),state(RAGENT_READY),mac(NULL)
{
	bind("packetSize_",&size_);	// size_ --member of agent class ,fixed packet size
}

int RfidRAgent::command(int argc,const char* const* argv){
	if (argc==2){
		if (strcmp(argv[1],"test")==0){
			Packet *pkt=mkPacket(RFID_QUERY,
					"QUERY_TEXT\0");
			//send(pkt,(Handler *)0);
			mac->recv(pkt,(Handler*)this);
			return (TCL_OK);
		}
		if (strcmp(argv[1],"brd-cmd")==0){
			Packet* pkt=mkPacket(RFID_QUERYREP,
					"QueryRep");
			mac->recv(pkt,(Handler*)this);
			return TCL_OK;
		}
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
			
	return (Agent::command(argc,argv));
}
void RfidRAgent::recv(Packet *p,Handler *h){
	Agent::recv(p,h);
	return;
}
Packet *RfidRAgent::mkPacket(int cmd,char *comment="no comment\0"){
	Packet *pkt=allocpkt();
	rfid_hdr *rh = HDR_RFID(pkt);
	hdr_cmn *ch = HDR_CMN(pkt);
	rh->cmd=cmd;
	strcpy(rh->comment,comment);
	ch->direction()=hdr_cmn::DOWN;
	hdr_ip *ih=HDR_IP(pkt);
	ih->daddr()=IP_BROADCAST;
	ih->dport()=TAgentPort;
	return pkt;
}
