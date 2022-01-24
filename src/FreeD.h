/*
 Name:		FreeD.h
 Created:	11/12/2021 3:05:10 AM
 Author:	Robert
 Editor:	http://www.visualmicro.com
*/

#ifndef _FreeD_h
#define _FreeD_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <ClockCache.h>

namespace freeD
{
	class LATCH
	{
	public:
		LATCH() {}
		bool Latch();
		void RESET();
		operator bool();
	private:
		bool mActive = true;
	};
	class LATCHMESSAGE
	{
	public:
		LATCHMESSAGE() {};

		bool LATCH();
		void MSG(const char*);
		void RESET();
		static void SetGlobalSerial(UARTClass& globalSerial);
	private:
		static UARTClass* mSerial;
		static bool mInit;
		bool SendMsg = true;
	};
	class FREEDELAY
	{
	public:
		// A Free Loop, timer based, "Delay" to by-pass subroutine loops without stopping execution.
		FREEDELAY() {}
		// Will return TRUE for a specified time after STARTDELAY(uint32_t period) is called.
		bool BREAK_OUT_OF_LOOP_HERE();
		// Starts the Delay for specified time in Milliseconds, at the BREAK_OUT_OF_LOOP_HERE() point. Returns false if already Active.
		bool STARTDELAY(uint32_t period);
		bool STARTDELAY(uint32_t period, bool& doOnceFlag);
		bool DELAYONCE(uint32_t period);
		void ResetDelayOnce();
		bool STARTHOLD();
		bool ENDHOLD();
	private:
		bool DoOnceFlag = true;
		bool Active = false;
		bool Hold = false;
		bool StartMsgSent = false;
		bool BreakMsgSent = false;
		uint32_t Period = 0;
		ClockCache fdClock = ClockCache();
	};
}


#endif

