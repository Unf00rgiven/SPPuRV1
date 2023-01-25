#include "Types.h"
#include "Constants.h"
#include "ResourceAllocation.h"
#include "libResourceAllocation.h"
#include "InterferenceGraph.h"
#include "Instruction.h"
#include "Variable.h"
#include "Simplification.h"
#include "libLivnessAnalysis.h"

#define LIB_NAME "LivenessAnalysis"
#include "auto_link.h"
#define LIB_NAME "ResourceAllocation"
#include "auto_link.h"

#include <iostream>

using namespace std;

int main()
{
	InterferenceGraph* ig;
	Instructions* instructions;
	stack<Variable*>* simplificationStack;

	// get instructions
	instructions = doLivenessAnalysis(0);


	// 1) build interference graph
	ig = doInterferenceGraph(instructions);

	printInterferenceGraph(ig);

	cout << "*******************************************************************\n";
	cout << "*******************************************************************\n";
	cout << "*****************  RESOURCE ALLOCATION START...  ******************\n";
	cout << "*******************************************************************\n";
	printVariables(ig->variables);
	cout << "\nInstruction list:\n";
	printInstructions(instructions);
	cout << "*******************************************************************\n\n\n";


	// 2) simplify
	simplificationStack = doSimplification(ig, __REG_NUMBER__);

	// 3) spill
	if (simplificationStack == NULL)
	{
		cout << "Spill detected!\n";
	}
	else
	{
		// 4) select
		if (doResourceAllocation(simplificationStack, ig) == true)
		{
			if (checkResourceAllocation(ig) == true)
			{

				// 5) remove unnecessary move operation
				Instructions* noMoveInstr = removeMove(instructions);

				// 6) final print
				cout << "*******************************************************************\n";
				cout << "*******************************************************************\n";
				cout << "******************  RESOURCE ALLOCATION END...  *******************\n";
				cout << "*******************************************************************\n";
				printVariables(ig->variables);
				cout << "\nInstruction list:\n";
				printInstructions(noMoveInstr);
				cout << "*******************************************************************\n\n\n";
			}
			else
			{
				cout << "Allocation failed!\n";
			}
		}
		else
		{
			cout << "Actual spill!\n";
		}
	}


	// free resources
	if (ig != NULL && ig->values != NULL)
	{
		freeInterferenceGraph(ig);
	}

	getchar();

	return 0;
}
