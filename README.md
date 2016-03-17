# BaseLib
用于Arduino 的 LogPrinter &amp; CmdLoarder 类


LogPrinter用于将日志信息打印到任何Print的子类上，例如Serial、WiFiClient，支持Printf函数。

CmdLoarder用于从任何Stream的子类上获取命令，例如Serial、WiFiClient，可以调用addMatchKey函数来添加关键字，在关键字出现时调用指定函数。
