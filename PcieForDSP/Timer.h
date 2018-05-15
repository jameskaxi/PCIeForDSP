

NTSTATUS
PcieDMATimerCreate(
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
DmaReadTimerEventFunc(
_In_ WDFTIMER Timer
);