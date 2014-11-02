#ifndef CONSOLE_H
#define CONSOLE_H
/**@todo implement Language support in Console.h**/
#include <StringHelper.h>
#include <string>
#include <iostream>
#define __S__(s) (*new std::string(s))

namespace ConsoleFormats
{
    ///Foreground Colors
    const std::string DefaultColor =    "\e[39m";
    const std::string Black =           "\e[30m";
    const std::string Red =             "\e[31m";
    const std::string Green =           "\e[32m";
    const std::string Yellow =          "\e[33m";
    const std::string Blue =            "\e[34m";
    const std::string Magenta =         "\e[35m";
    const std::string Cyan =            "\e[36m";
    const std::string LightGray =       "\e[37m";
    const std::string DarkGray =        "\e[90m";
    const std::string LightRed =        "\e[91m";
    const std::string LightGreen =      "\e[92m";
    const std::string LightYellow =     "\e[93m";
    const std::string LightBlue =       "\e[94m";
    const std::string LightMagenta =    "\e[95m";
    const std::string LightCyan =       "\e[96m";
    const std::string White =           "\e[97m";

    ///Background Colors
    const std::string DefaultColorBack =    "\e[49m";
    const std::string BlackBack =           "\e[40m";
    const std::string RedBack =             "\e[41m";
    const std::string GreenBack =           "\e[42m";
    const std::string YellowBack =          "\e[43m";
    const std::string BlueBack =            "\e[44m";
    const std::string MagentaBack =         "\e[45m";
    const std::string CyanBack =            "\e[46m";
    const std::string LightGrayBack =       "\e[47m";
    const std::string DarkGrayBack =        "\e[100m";
    const std::string LightRedBack =        "\e[101m";
    const std::string LightGreenBack =      "\e[102m";
    const std::string LightYellowBack =     "\e[103m";
    const std::string LightBlueBack =       "\e[104m";
    const std::string LightMagentaBack =    "\e[105m";
    const std::string LightCyanBack =       "\e[106m";
    const std::string WhiteBack =           "\e[107m";

    ///Formattig
    const std::string Bold =            "\e[1m";
    const std::string Dim =             "\e[2m";
    const std::string Underlined =      "\e[4m";
    const std::string Blink =           "\e[5m";
    const std::string Inverted =        "\e[7m";
    const std::string Hidden =          "\e[8m";

    ///Reset Formattig
    const std::string ResetBold =       "\e[21m";
    const std::string ResetDim =        "\e[22m";
    const std::string ResetUnderlined = "\e[24m";
    const std::string ResetBlink =      "\e[25m";
    const std::string ResetInverted =   "\e[27m";
    const std::string ResetHidden =     "\e[28m";

    ///Resetting all previous Formatting and Colors
    const std::string Reset =           "\e[0m";
}

namespace ConsoleBlocks
{
    const std::string Error = ConsoleFormats::Red + ConsoleFormats::Bold + __S__("[ERROR] ") + ConsoleFormats::Reset;
    const std::string Warning = ConsoleFormats::Yellow + ConsoleFormats::Bold + __S__("[WARNING] ") + ConsoleFormats::Reset;
    const std::string Info = ConsoleFormats::Cyan + ConsoleFormats::Bold + __S__("[INFO] ") + ConsoleFormats::Reset;
    const std::string Success = ConsoleFormats::Green + ConsoleFormats::Bold + __S__("[SUCCESS] ") + ConsoleFormats::Reset;
    const std::string Debug = ConsoleFormats::LightBlue + ConsoleFormats::Bold + __S__("[DEBUG] ") + ConsoleFormats::Reset;
    const std::string PNG = ConsoleFormats::Cyan + __S__("[PNG] ") + ConsoleFormats::Reset;
    const std::string BMP = ConsoleFormats::Cyan + __S__("[BMP] ") + ConsoleFormats::Reset;
    const std::string JPG = ConsoleFormats::Cyan + __S__("[JPG] ") + ConsoleFormats::Reset;
    const std::string Input = ConsoleFormats::Bold + __S__(">> ") + ConsoleFormats::Reset;
}

class Console
{
    public:
        Console();
        static std::string FileAdress(std::string);
        static std::string WebAdress(std::string);
        static std::string Header(std::string);
        static std::string Header(std::string, size_t);
        template<class T>
            static std::string Array(std::vector<T> array)
            {
                std::string out = "Array Print:\n";
                int i = 0;
                for(T element : array)
                    out += __S__("\t[") + std::to_string(i) + "] => " + std::to_string(element) + "\n";
                return out;
            }

        static std::string input(std::string);
        virtual ~Console();
    protected:
    private:
};

#endif // CONSOLE_H
