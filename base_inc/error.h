#ifndef ERROR_H_INCLUDED
#define ERROR_H_INCLUDED

#include "Exception.h"

namespace Error
{
    ///No Error
    const Exception None("", false);
    ///Standard Errors
    const Exception NotYetImplemented("This option or function has not been implemented yet.", true);
    ///String/Parser Processing
    const Exception StringToIntStrictUnrecognizedChar("Couldn't convert string to int due to an unexpected character!", true);
    const Exception ParserEOF("End of file or line reached!", true);
    const Exception ParserStringWordUnrecognizedChar("Unrecognized char while parsing word!", true);
    const Exception ParserStringMissingEnd("String is unclosed!", true);
    const Exception ParserTypesafeVarNeedsDType("This type-safe variable must be declared with a data type.", true);
    const Exception ParserUnknownDataType("Unknown data type", true);
    const Exception ParserExpectedString("Expected a string value!", true);
    const Exception ParserExpectedInt("Expected an integer value!", true);
    const Exception ParserExpectedDouble("Expected a float pointing value (double)", true);
    const Exception ParserExpectedBool("Expected a boolean value", true);
    ///Language Selecting Problem
    const Exception LanguageNoTranslation("There is no translation for this!", true);
    const Exception LanguageUninitialized("The Language sets are uninitialized yet!", true);
    ///CommandLine input
    const Exception WrongNumberOfArguments("You provided the wrong number of arguments.", true);
    ///Directory Errors
    const Exception DirOpenError("Could not open directory!", true);
    const Exception DirEnterError("Could not enter directory!", true);
    const Exception DirUpError("Could not enter parent directory!", true);
    ///Text File Errors
    const Exception TextFileReadError("Could not read text file!", true);
    const Exception TextFileWriteError("Could not write text file!", true);
    ///PNG File Errors
    const Exception PNGFileReadError(ConsoleBlocks::PNG + __S__("Couldn't open file for reading."), true);
    const Exception PNGHeaderMissing(ConsoleBlocks::PNG + __S__("The file doesn't seem to provide a header."), true);
    const Exception PNGNotPNG(ConsoleBlocks::PNG + __S__("The file is not recognized as a PNG file."), true);
    const Exception PNGCreateReadStruct(ConsoleBlocks::PNG + __S__("png_create_read_struct failed."), true);
    const Exception PNGCreateInfoStruct(ConsoleBlocks::PNG + __S__("png_create_info_struct failed."), true);
    const Exception PNGInitIO(ConsoleBlocks::PNG + __S__("Error during init_io."), true);
    const Exception PNGReadImage(ConsoleBlocks::PNG + __S__("Error during read_image."), true);
    const Exception PNGFileWriteError(ConsoleBlocks::PNG + __S__("Couldn't open file for writing."), true);
    const Exception PNGFileWriteHeader(ConsoleBlocks::PNG + __S__("Error during writing header."), true);
    const Exception PNGFileWriteData(ConsoleBlocks::PNG + __S__("Error during writing bytes."), true);
    const Exception PNGFileWriteEnd(ConsoleBlocks::PNG + __S__("Error during end of write."), true);
    const Exception PNGCreateWriteStruct(ConsoleBlocks::PNG + __S__("png_create_write_struct failed."), true);
    ///Syntax Errors
    const Exception MissingBraceBegin("The beginning '{' does not have a corresponding ending!", true);
    const Exception MissingBraceEnd("The ending '}' does not have a corresponding beginning!", true);
    const Exception MissingChevronBegin("The beginning '<' does not have a corresponding ending!", true);
    const Exception MissingChevronEnd("The ending '>' does not have a corresponding beginning!", true);
    const Exception MissingParenthesesBegin("The beginning '(' does not have a corresponding ending!", true);
    const Exception MissingParenthesesEnd("The ending ')' does not have a corresponding beginning!", true);
    ///Config Syntax Errors
    const Exception ConfigSectionUnclosed("A Section in config file has not been closed!", false);
    const Exception ConfigStatementUnclosed("A Statement in config file has not been closed!", true);
    const Exception ConfigTypesNotMatch("The data types for the Property do not match!", true);
    const Exception ConfigUnrecognizedCharL("Unrecognized character (L-Value) in config file!", true);
    const Exception ConfigUnrecognizedCharR("Unrecognized character (R-Value) in config file!", true);
    const Exception ConfigUnrecognizedCharRFSemi("Unrecognized character (R-Value) in config file (Maybe you forgot the ';'?)!", true);
    const Exception ConfigMissingWeakEqual("An weak equal sign is missing.", true);
    const Exception ConfigMissingEqual("An equal sign is missing.", true);
    const Exception ConfigMissingStringEnd("The string literal is not closed again.", true);
    const Exception ConfigUnrecognizedSectionName("Unrecognized Section name!", true);
    const Exception ConfigUnrecognizedSectionParam("Unrecognized Params in Section!", true);
    const Exception ConfigUnrecognizedSectionParamEnd("Unrecognized Params' end in Section!", true);
    const Exception ConfigWrongType("One of the properties have the wrong type", true);
    const Exception ConfigPreprocessorUnclosed("Preprocessor command has no argument or is not closed properly (Forgot the ';'?)!", true);
    const Exception ConfigWrongPreprocessorStringArgSyntax("A string argument of a preprocessor directive must begin and end with double quotes.", true);
    const Exception ConfigUnknownPreprecessorDirective("Unknown preprocessor directive!", true);
    const Exception ConfigNotAValidFileId("This is not a valid file id!", true);
    const Exception ConfigOnlyVirtAppPathSupport("Currently only '%VIRTUAL_APP_PATH%' is supported.", true);
    const Exception ConfigWrongCodePath("Invalid code path syntax!", true);
    ///Config Internal Errors
    const Exception ConfigAtSearchNotFound("Item not found while trying to perform an 'at' search for a config section!", true);
    const Exception ConfigAtSearchPropNotFound("Item not found while trying to perform an 'at' search for a property!", true);
    const Exception ConfigAtSearchMod2("Wrong number of arguments while trying to perform an 'at' search for a config section!", true);
    const Exception ConfigCriticalError("An critical error occurred! This program will shut down.", true);
    const Exception ConfigDeleteVoid("Cannot delete a voided or not yet defined property!", true);
    ///Cfg Explorer
    const Exception CfgExplorerUnknownCommand("Unknown command!", true);
    const Exception CfgExplorerSSectionDoesntExist("This subsection doesn't exist!", true);
    const Exception CfgExplorerSectionDoesntExist("This section doesn't exist!", true);
    const Exception CfgExplorerPropDoesntExist("This property doesn't exist!", true);
    ///CfgTable
    const Exception CfgColumnNotFound("This column doesn't exist!", true);
    const Exception CfgColumnLTooMuch("You provided too much cells in this line", true);
    const Exception CfgColumnLTooFew("You provided too few cells in this line", true);
    const Exception CfgTableIdAlreadyFound("This Table has already an unique id. This database currently only supports a single UID per table.", true);
    ///Set Command
    const Exception SetLanguageNotAvailable("Unfortunately this language is not available!", true);
    ///Shader
    const Exception ShaderUnknownType("This Shader type is unknown! The Shader program could not compile properly!", true);
    const Exception ShaderNoFile("For this shader there is no source file!", true);
    const Exception ShaderCompileError("A Shader had compile errors! This program doesn't work without valid shaders and is shutting down immediately.", true);
    const Exception ShaderLinkerError("The shader program had linker errors! This program doesn't work without valid shaders and is shutting down immediately.", true);
    const Exception ShaderNoVertex("No source file specified for the vertex shader. But this shader program needs a valid vertex shader", true);
    const Exception ShaderNoFragment("No source file specified for the fragment shader. But this shader program needs a valid fragment shader", true);
    const Exception ShaderNoUniforms("There were no uniforms provided to pass!", true);
    const Exception ShaderTooMuchUniforms("There were too much uniforms provided to pass!", true);
    const Exception ShaderUniformNotFound("The given uniform name wasn't found in the shader!", true);
    const Exception ShaderAttribNotFound("The given attribute name wasn't found in the shader!", true);
};

#endif // ERROR_H_INCLUDED
