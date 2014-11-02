#include "ExpHelper.h"

ExpHelper::ExpHelper()
{
    //ctor
}

ExpHelper::~ExpHelper()
{
    //dtor
}

std::string ExpHelper::genRegEx(std::string s)
{
    std::string out(s);
    int replacements = StringHelper::replaceAll(out, "//L", "{{{ESCAPED_LEFT_BRACE}}}");
    replacements += StringHelper::replaceAll(out, "{L", "{{{UNESCAPED_LEFT_BRACE}}}");
    replacements += StringHelper::replaceAll(out, "R}", "{{{UNESCAPED_RIGHT_BRACE}}}");
    replacements += StringHelper::replaceAll(out, "\\*", "{{{ESCAPED_WILDCART}}}");
    replacements += StringHelper::replaceAll(out, "(.*)", "{{{UNESCAPED_WILDCART}}}");
    replacements += StringHelper::replaceAll(out, "*", "{{{UNESCAPED_WILDCART}}}");
    replacements += StringHelper::replaceAll(out, "{{{UNESCAPED_WILDCART}}}", "(.*)");
    replacements += StringHelper::replaceAll(out, "{{{ESCAPED_WILDCART}}}", "\\*");
    replacements += StringHelper::replaceAll(out, "{{{UNESCAPED_LEFT_BRACE}}}", "{");
    replacements += StringHelper::replaceAll(out, "{{{ESCAPED_LEFT_BRACE}}}", "\\{");
    replacements += StringHelper::replaceAll(out, "{{{UNESCAPED_RIGHT_BRACE}}}", "}");

    return out;
}
