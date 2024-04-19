/*
 * LTecher Adventure (c) 2024
 *
 * This file belongs to the LTecher Adventure project
 */

#include <iostream>

#include <tinyfiledialogs.h>


#ifndef MARCOS_ERRORS_H
#define MARCOS_ERRORS_H

#define PANIC(msg, exit_code) std::cout << "FATAL: PANIC: " << msg << std::endl; \
                              std::string msg_string = std::string("FATAL ERROR: ") + msg; \
                              const char *msg_dialog = msg_string.c_str(); \
                              tinyfd_messageBox( \
                                "Error", \
                                msg_dialog, \
                                "ok", \
                                "error", \
                                1 \
                              ); \
                              exit(exit_code);

#endif
