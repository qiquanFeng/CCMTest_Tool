#include "../Board_SDK/dt/dtccm.h"
#include "../rlg/include/HisFX3Platform.h"

#ifdef _WIN64
#pragma comment(lib,"../Board_SDK/dt/X64_Lib/dtccm")
#pragma comment(lib,"../Board_SDK/rlg/X64/HisFX3Platform64D")
#else
#pragma comment(lib,"../DTCCM_SDK/X86_Lib/dtccm")
#endif


typedef QList<QPair<int, int>> PAIRLIST;

