#pragma once

#include SAMPEDGENGINE_PCH

namespace samp_edgengine
{

#ifdef DEBUG

class IServerDebugLogReceiver
{
public:

	void setReceiveServerDebugLog(bool receives_) {
		m_receivesDebugLog = receives_;
	}
	
	bool receivesServerDebugLog() const {
		return m_receivesDebugLog;
	}
private:
	bool m_receivesDebugLog = false;
};

#endif

}