#include "LivenessAnalysis.h"



void livenessAnalysis(Instructions instructions){

	Instructions::iterator i;
	for (i = instructions.begin(); i != instructions.end(); i++) {
		(*i)->out.clear();
		(*i)->in.clear();
	}

	bool goAgain = true;
	while (goAgain) {
		goAgain = false;

		Instructions::reverse_iterator it;
		for (it = instructions.rbegin(); it != instructions.rend(); it++) {

			Variables oldOut = (*it)->out;
			Variables oldIn = (*it)->in;

			//out --> skup "out[n]" je unija "in" skupova svih naslednika cvora n
			//odnosno unija svih promenljivih koje pripadaju skupu "in" svakog naslednika cvora n
			Instructions::iterator it_out;
			//prolazimo kroz skup svih naslednika trenutnog cvora
			for (it_out = (*it)->succ.begin(); it_out != (*it)->succ.end(); it_out++) {

				Variables::iterator it_out1;
				//prolazimo kroz ceo "in" skup od naslednika
				for (it_out1 = (*it_out)->in.begin(); it_out1 != (*it_out)->in.end(); it_out1++) {
					(*it)->out.push_back((*it_out1));	//u "out" stavljamo sve iz "in"
				}
			}

			//sortiramo pa brisemo nejednistvene elemente
			(*it)->out.sort();
			(*it)->out.unique();


			//in --> skup "in[n]" cine sve promenljive iz skupa "use[n]" plus promenljive koje jesu u "out[n]", ali nisu u "def[n]"
			(*it)->in = (*it)->use;	//sve iz 'use' smestamo u 'in'

			Variables::iterator it_in;
			//sad prolazimo kroz sve 'out-e' i proveravamo da li su te instrukcije u 'out-u' a nisu u 'def-u'
			for (it_in = (*it)->out.begin(); it_in != (*it)->out.end(); it_in++) {
				if (!variableExists(*it_in, (*it)->def)) {		//i ako nisu dodajemo ih u listu 'in'
					(*it)->in.push_back((*it_in));
				}
			}

			(*it)->in.sort();
			(*it)->in.unique();

			if (oldOut == (*it)->out && oldIn == (*it)->in) {
				goAgain = true;
			}
		}
	}
}
