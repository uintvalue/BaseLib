#include "LogPrinter.h"
#include <Print.h>
#include <Arduino.h>

LogPrinter Logger;


LogPrinter::LogPrinter()
{
    PrinterDefined = false;
    Enable = true;
}

void LogPrinter::setPrintTo(Print& p, bool printHeadEnable)
{
    if(&p)
    {
        logPrinter = &p;
        PrinterDefined = true;
        if(printHeadEnable) printHead();
    }
    else
    {
        PrinterDefined = false;
        return;
    }
}
void LogPrinter::removePrinter(void)
{
    logPrinter = NULL;
    PrinterDefined = false;
}

size_t LogPrinter::write(uint8_t b)
{
    // if(Enable && PrinterDefined)
    //     return logPrinter->write(b);
    // else
    //     return 0;
    write(&b, 1);
}

size_t LogPrinter::write(const uint8_t *buffer, size_t size)
{
    if(Enable && PrinterDefined)
        return logPrinter->write(buffer, size);
    else
        return 0;
}


void LogPrinter::printHead(void)
{
    println();
    println("*********************************");
    println("             Welcome             ");
    println("*********************************");
    println();
}
