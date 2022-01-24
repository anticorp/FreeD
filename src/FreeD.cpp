/*
 Name:		FreeD.cpp
 Created:	11/12/2021 3:05:10 AM
 Author:	Robert
 Editor:	http://www.visualmicro.com
*/

#include "FreeD.h"
#include <ADM.h>

namespace freeD
{
	UARTClass* LATCHMESSAGE::mSerial = &Serial;
	bool LATCHMESSAGE::mInit = false;
	bool FREEDELAY::BREAK_OUT_OF_LOOP_HERE()
	{
		if (Active)
		{
			if (Hold) {
				if (!BreakMsgSent) {
					BreakMsgSent = true;
					//Serial.print("\n\nHOLDING BREAK OUT POINT!\n\nHOLDING...\n\n");
				}
				return true;
			}
			if (!BreakMsgSent) {
				BreakMsgSent = true;
				//bug << xntt << "Delay " << Period << " ms\n";
				//Serial.print("\n\nFREE LOOP DELAY BREAKOUT POINT\n\nDelaying for ");
				//Serial.print(Period);
				//Serial.print(" milliseconds\n\n");
			}
			if (fdClock.Delta() >= Period)
			{
				Active = false;
				BreakMsgSent = false;
				return false;
			}
			return true;
		}
		return false;
	}
	bool FREEDELAY::STARTDELAY(uint32_t period)
	{
		if (!Active)
		{
			if (period > 0)
			{
				//Serial.print("\n\n\nDELAY CALLED!\n\n\n");

				Period = period;
				Active = true;
				fdClock.Mark();
				BreakMsgSent = false;
				return true;
			}
		}
		return false;
	}
	bool FREEDELAY::STARTDELAY(uint32_t period, bool& doOnceFlag)
	{
		if (!doOnceFlag) return false;
		if (!Active)
		{
			if (period > 0)
			{
				//Serial.print("\n\n\nDELAY CALLED!\n\n\n");
				Period = period;
				Active = true;
				fdClock.Mark();
				BreakMsgSent = false;
				doOnceFlag = false;
				return true;
			}
		}
		return false;
	}
	bool FREEDELAY::DELAYONCE(uint32_t period)
	{
		if (!DoOnceFlag) return false;
		if (!Active)
		{
			if (period > 0)
			{
				//Serial.print("\n\n\nDELAY CALLED!\n\n\n");
				Period = period;
				Active = true;
				fdClock.Mark();
				BreakMsgSent = false;
				DoOnceFlag = false;
				return true;
			}
		}
		return false;
	}
	void FREEDELAY::ResetDelayOnce()
	{
		DoOnceFlag = true;
	}
	bool FREEDELAY::STARTHOLD()
	{
		if (!Active)
		{
			Serial.print("\n\n\nHOLD CALLED!\n\n\n");
			Active = true;
			Hold = true;
			return true;
		}
		return false;
	}
	bool FREEDELAY::ENDHOLD()
	{
		if (Active)
		{
			Serial.print("\n\n\nHOLD END CALLED!\n\n\n");
			BreakMsgSent = false;
			Active = false;
			Hold = false;
			return true;
		}
		return false;
	}
	bool LATCHMESSAGE::LATCH()
	{
		bool sm = SendMsg;
		SendMsg = false;
		return sm;
	}
	void LATCHMESSAGE::MSG(const char* cc)
	{
		if (!SendMsg) return;
		if (mInit) mSerial->print(cc);
		SendMsg = false;
		return;
	}
	void LATCHMESSAGE::RESET()
	{
		SendMsg = true;
	}
	void LATCHMESSAGE::SetGlobalSerial(UARTClass& globalSerial)
	{
		if (!mInit)
			mSerial = &globalSerial;
		mInit = true;
	}
	
	bool LATCH::Latch()
	{
		if (mActive)
		{
			mActive = false;
			return true;
		}
		return false;
	}
	void LATCH::RESET()
	{
		mActive = true;
	}
	LATCH::operator bool()
	{
		if (mActive)
		{
			mActive = false;
			return true;
		}
		return false;
	}
}
