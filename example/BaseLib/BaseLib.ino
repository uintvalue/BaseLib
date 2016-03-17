#include <LogPrinter.h>
#include <CmdLoarder.h>

void CommandMatched(String key)
{
    Logger.print(key); Logger.println(" received.");
}

void setup()
{
    Serial.begin(115200);
    delay(10);

    Command.setLoadFrom(Serial);
    Command.addMatchKey("Command", CommandMatched, true);
    Command.addMatchKey("test", CommandMatched);

    Logger.setPrintTo(Serial, true);
    Logger.println("Welcome to use LogPrinter.");
    Logger.printf("millis: %d\n", millis());
}

void loop()
{
    Command.fresh();

    delay(10);
}
