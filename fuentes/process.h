#ifndef __OPTION_H__
#define __OPTION_H__

#include <getopt.h>
#include <unistd.h>

// process arguments and runs the program
// returns error code
int process(int argc, char **argv);

#endif /* __OPTION_H__ */
