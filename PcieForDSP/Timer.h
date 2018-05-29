#ifndef __TIMER_H_
#define __TIMER_H_

NTSTATUS
PcieTimerCreate(
_In_ WDFTIMER *Timer,
_In_ WDFDEVICE Device,
_In_ PFN_WDF_TIMER EvtTimerFunc
);

BOOLEAN
PcieTimerStart(
_In_ WDFTIMER Timer,
_In_ ULONGLONG timeByMs
);

BOOLEAN
PcieTimerStop(
_In_ WDFTIMER Timer
);

VOID
DmaWriteTimerEventFunc(
_In_ WDFTIMER Timer
);

VOID
ReadTimerEventFunc(
_In_ WDFTIMER Timer
);

VOID
IoWriteTimerEventFunc(
_In_ WDFTIMER Timer
);

#endif // !__TIMER_H_

