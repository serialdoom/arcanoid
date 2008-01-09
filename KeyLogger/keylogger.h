// Keylogger header file
/*
 * author: mhristof
 * refactoring: koutsop
 */

#ifndef KEYLOGGER_H
#define KEYLOGGER_H


#include <iostream>
#include <fstream>
#include <stdarg.h>


#define BUFFER_SIZE 9999
/* testing*/
class KeyLogger {
	static std::ofstream logfile; /* Holds the stream to write the bullshit we are telling this logger to write.*/
	static bool enabled;

public:
	/* initialize the stream (and enables logging).
	 * filename: The name of the file that the log with occur.
	 * returns TRUE: if all ok, FALSE if there was a failed attempt to open the stream.
	 */
	static bool Init(char *filename);

	/* Write something to the logger.
	 * Provide arguments just like printf.
	 * returns: TRUE: if all OK, FALSE if the logger is disabled, or not initiallized.
	 */
	static bool Write(const char* const format, ...);

	/* Enables the logger.
	 */
	static void Enable(void);

	/* Disables the logger.
	 */
	static void Disable(void);

	/* Terminates the logger making the file able to read.
	 */
	static void Terminate(void);
};

#endif
