#ifndef RFID_HDR
#define RFID_HDR

#include "agent.h"
#include "tclcl.h"
#include "packet.h"
#include "address.h"
#include "ip.h"


#define HDR_RFID(p)	rfid_hdr::access(p)
struct rfid_hdr {
	int cmd;
	char comment[16];
	int misc;
	static int offset_;
	inline static rfid_hdr* access (const Packet* p){
		return (rfid_hdr*) p->access(offset_);
	}
};

enum rfidcmd {
	RFID_QUERY = 1,
	RFID_LISTEN,
	RFID_QUERYADJ,
	RFID_QUERYREP,
	RFID_ACK,
	RFID_NAK
}; 


#endif
