#ifndef RB3_NETWORKSOCKET_HPP
#define RB3_NETWORKSOCKET_HPP
#include "types.h"
#include "revolution/rvl/so.h"

class NetworkSocket {
	public:
		NetworkSocket();
		virtual ~NetworkSocket();
		virtual bool Connect() = 0;
		virtual bool Fail() = 0;
		virtual bool Disconnect() = 0;
		virtual bool InqBoundPort() = 0;
		virtual void Listen() = 0;
		virtual NetworkSocket* Accept() = 0;
		virtual bool GetRemoteIP() = 0;
		virtual int CanSend() = 0;
		virtual int BytesAvailable() = 0;
		virtual void* Send(int, uint) = 0;
		virtual void* Recv(int, int) = 0;
		virtual bool SendTo() = 0;
		virtual bool BroadcastTo() = 0;
		virtual bool RecvFrom() = 0;
		virtual bool SetNoDelay() = 0;
		virtual int V_Unk19();
};
#endif
