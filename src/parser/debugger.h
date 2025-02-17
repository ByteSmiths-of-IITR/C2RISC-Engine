#ifndef DEBUGGER_H
#define DEBUGGER_H

//-------------------------------------- Industry Grade Debug mode setup
int DEBUGMODE = 0; // will be set to !0 if the program is run with -d flag
#define DEBUG 1
#define INFO 2
// 0-NoDebug
// 1-Debug [Explicit Debugging the code (using HERE function)]
// 2-Info  [Informational Messages]

std::ofstream debug_log("debug.log", std::ios::trunc);
// We need to truncate the log file every time we run the program

void DEBUG_MSG(int logLevel, std::string msg){
    if (logLevel <= DEBUGMODE){
        // std::time_t t = std::time(0);
        // std::tm* now = std::localtime(&t);
        // debug_log << "[" << now->tm_year + 1900 << '-' << now->tm_mon + 1 << '-' << now->tm_mday << ' ' << now->tm_hour << ':' << now->tm_min << ':' << now->tm_sec << "] ";
        switch (logLevel){
            case DEBUG:
                debug_log << "[DEBUG]  : ";
                break;
            case INFO:
                debug_log << "[INFO]   : ";
                break;
            default:
                debug_log << "[UNKNOWN]: ";
                break;
        }
        debug_log << msg << std::endl;
    }
}

void HERE(){
    DEBUG_MSG(DEBUG, "Reaching here - " + std::to_string(__LINE__) + " in " + __FILE__);
}
//-------------------------------------- End of Debug mode setup

#endif // DEBUGGER_H