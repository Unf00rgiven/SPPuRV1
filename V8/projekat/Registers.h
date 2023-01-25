#ifndef _REGISTERS_H_
#define _REGISTERS_H_

#include <string>
#include <vector>


/**
 * Use this type to describe register.
 */
typedef int Reg;

/**
 * Use this function to translate reg(number) to appropriate MIPS register.
 * This function hold table of MIPS registers(colors), reg is index (int) which index table.
 */
std::string getRegName(Reg reg);


/**
 * Make new register.
 * @return new reg
 */
Reg getNewReg();

#endif
