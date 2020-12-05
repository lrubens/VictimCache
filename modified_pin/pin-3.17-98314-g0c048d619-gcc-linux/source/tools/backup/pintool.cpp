#include "pin.H"
#include <fstream>
#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <queue> 
//#include <boost/unordered_set.hpp>
//#include "pin/source/include/pin/pin.H"
using std::cout;
using std::cerr;
using std::ofstream;
using std::ios;
using std::string;
using std::endl;
using std::queue;
// const uint64_t PG_SIZE = 4096; // 4kb

static std::list<UINT64> accessed_pages;
static queue<int> labels;

VOID RecordMemAccess(VOID *addr, VOID *label) {
    UINT32 label_val = (UINT64)label;
    UINT64 addr_val = (UINT64)addr;
    accessed_pages.push_back(addr_val);
    labels.push(label_val);
}
// Is called for every instruction and instruments reads and writes
VOID OnInstruction(INS ins, VOID *v)
{
    // Instruments memory accesses using a predicated call, i.e.
    // the instrumentation is called iff the instruction will actually be executed.
    //
    
    // On the IA-32 and Intel(R) 64 architectures conditional moves and REP 
    // prefixed instructions appear as predicated instructions in Pin.
    UINT32 memOperands = INS_MemoryOperandCount(ins);
    std::ofstream outfile;
    outfile.open("type.txt", std::ios_base::app);
    // Iterate over each memory operand of the instruction.
    for (UINT32 memOp = 0; memOp < memOperands; memOp++)
    {
        if (INS_MemoryOperandIsRead(ins, memOp))
        {
            INS_InsertPredicatedCall(
                ins, IPOINT_BEFORE, (AFUNPTR)RecordMemAccess,
                IARG_MEMORYOP_EA, memOp,
                IARG_UINT32, 0,
		IARG_END);
	    outfile << 0;
	    //cout << ' ';
	    //cout << std::hex << ins << endl;
	    //labels.push(0);
        }
        // Note that in some architectures a single memory operand can be 
        // both read and written (for instance incl (%eax) on IA-32)
        // In that case we instrument it once for read and once for write.
        if (INS_MemoryOperandIsWritten(ins, memOp))
        {
            INS_InsertPredicatedCall(
                ins, IPOINT_BEFORE, (AFUNPTR)RecordMemAccess,
                IARG_MEMORYOP_EA, memOp,
		IARG_UINT32, 1,
                IARG_END);
        }
    }
}

VOID Fini(INT32 code, VOID *v) {
     ofstream file;
     file.open("trace.txt");
     for(auto const& x : accessed_pages) {
         file << labels.front(); 
	 labels.pop(); 
	 file << ' ';
	 file << std::hex << x << endl;
     }
     //UINT64 i;
     /*for (list<UINT64>::iterator i = accessed_pages.begin(); i != accessed_pages.end(); ++i){
         file << labels.front();
         labels.pop();
         file << ' ';         
         file << std::hex << i << endl;
     }*/
     file.close();
    //std::copy(accessed_pages.begin(),
    //    accessed_pages.end(),
    //    std::ostream_iterator<int>(std::cout, "\n"));
}

/* ===================================================================== */
/* Print Help Message                                                    */
/* ===================================================================== */
INT32 Usage()
{
    cerr << "This tool counts the number of dynamic instructions executed" << endl;
    cerr << endl << KNOB_BASE::StringKnobSummary() << endl;
    return -1;
}
/* ===================================================================== */
/* Main                                                                  */
/* ===================================================================== */
/*   argc, argv are the entire command line: pin -t <toolname> -- ...    */
/* ===================================================================== */
int main(int argc, char * argv[])
{
    // Initialize pin
    if (PIN_Init(argc, argv)) return Usage();
    // Register Instruction to be called to instrument instructions
    INS_AddInstrumentFunction(OnInstruction, 0);
    // Register Fini to be called when the application exits
    PIN_AddFiniFunction(Fini, 0);
    
    // Start the program, never returns
    PIN_StartProgram();
    
    return 0;
}
