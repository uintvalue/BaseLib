#ifndef __LOGPRINTER__
#define __LOGPRINTER__

#include "Print.h"


class LogPrinter : public Print
{
    public:
        bool PrinterDefined;
        bool Enable;

        LogPrinter();
        void setPrintTo(Print& p, bool printHeadEnable);
        void removePrinter();
        size_t write(uint8_t b) override;
        size_t write(const uint8_t *buffer, size_t size) override;

        void printHead(void);
    private:
        Print *logPrinter;

};


extern LogPrinter Logger;




#endif
