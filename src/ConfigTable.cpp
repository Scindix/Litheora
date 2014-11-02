
#include "ConfigTable.h"

ConfigTable::ConfigTable()
{
    //ctor
}

ConfigTable::ConfigTable(const ConfigTable& c)
{
    for(size_t i = 0; i < c.column.size(); i++)
    {
        ///column.push_back(new ConfigColumn(c.column[i]));
    }
}

ConfigTable::~ConfigTable()
{
    //dtor
}

void ConfigTable::parse(std::string* line, size_t* initial, char stop, size_t* lineNumber)
{
    (*initial)++;
    bool idFound = false;
    while(1)
    {
        bool uid = false, ainc = false;
        ParserHelper::skipSpaces(initial, line, lineNumber);
        std::string datatype = "auto";
        if(KeyWD::Chars.find(line->at(*initial))!=std::string::npos)
        {
            datatype = ParserHelper::getWord(initial, line, lineNumber);
            ParserHelper::skipSpaces(initial, line, lineNumber);
        }
        if(line->at(*initial) == '@' || line->substr(*initial, 2) == "+@")
        {
            if(idFound)
                throw(Error::CfgTableIdAlreadyFound);
            idFound = true;
            uid = true;
        }
        if(line->at(*initial) == '+' || line->substr(*initial, 2) == "@+")
            ainc = true;
        if(line->at(*initial) == '@' || line->at(*initial) == '+')
            (*initial)++;
        if(line->substr((*initial)-1, 2) == "+@" || line->substr((*initial)-1, 2) == "@+")
            (*initial)++;
        ParserHelper::skipSpaces(initial, line, lineNumber);
        std::string name = ParserHelper::getWord(initial, line, lineNumber, KeyWD::Equal+KeyWD::Comma+KeyWD::SemiColon);
        ParserHelper::skipSpaces(initial, line, lineNumber);
        if(line->substr((*initial), 1) == KeyWD::Equal)
        {
            (*initial)++;
            if(datatype=="string" || (datatype=="auto" && line->at(*initial) == '"'))
            {
                if(line->at(*initial) != '"')
                    throw(Error::ParserExpectedString);
                datatype = "string";
                std::string value = ParserHelper::getString(initial, line, lineNumber, "\"");
                addColumn<ConfigColumnSTRING, std::string>(name, ainc, uid, value);
            } else if(datatype=="bool" ||
                      (datatype=="auto" && line->substr(*initial, 4) == "true") ||
                      (datatype=="auto" && line->substr(*initial, 5) == "false"))
            {
                bool value = ParserHelper::getBool(initial, line, lineNumber);
                addColumn<ConfigColumnBOOL, bool>(name, ainc, uid, value);
            } else if(datatype=="int")
            {
                bool* type = nullptr;
                void* vvalue = ParserHelper::getNumber(type, initial, line, lineNumber);
                if(!(*type))
                    throw(Error::ParserExpectedInt);
                addColumn<ConfigColumnINT, int>(name, ainc, uid, *(int*)vvalue);
            } else if(datatype=="double")
            {
                bool* type = nullptr;
                void* vvalue = ParserHelper::getNumber(type, initial, line, lineNumber);
                if(*type)
                    throw(Error::ParserExpectedDouble);
                addColumn<ConfigColumnDOUBLE, double>(name, ainc, uid, *(double*)vvalue);
            } else if(datatype=="ref" || (datatype=="auto" && line->at(*initial) == '&'))
            {
                throw(((Exception)Error::NotYetImplemented)[L("ReferenceTypePlanned")]);
            } else if(datatype=="auto" && KeyWD::Numbers.find(line->at(*initial))!=std::string::npos)
            {
                bool type = false;
                void* vvalue = ParserHelper::getNumber(&type, initial, line, lineNumber);
                if(type)
                {
                    addColumn<ConfigColumnINT, int>(name, ainc, uid, *(int*)vvalue);
                } else
                {
                    addColumn<ConfigColumnDOUBLE, double>(name, ainc, uid, *(double*)vvalue);
                }
            } else
            {
                throw(((Exception)Error::ParserUnknownDataType)[S(" (") + datatype + S(")")]);
            }
        }
        else if(line->substr((*initial), 1) == KeyWD::Comma)
        {
            if(datatype == "auto")
                throw(Error::ParserTypesafeVarNeedsDType);
            else if(datatype == "string")
            {
                addColumn<ConfigColumnSTRING, std::string>(name, ainc, uid, S(""));
            }
            else if(datatype == "bool")
            {
                addColumn<ConfigColumnBOOL, bool>(name, ainc, uid, false);
            }
            else if(datatype == "int")
            {
                addColumn<ConfigColumnINT, int>(name, ainc, uid, 0);
            }
            else if(datatype == "double")
            {
                addColumn<ConfigColumnDOUBLE, double>(name, ainc, uid, 0.0);
            }
            else if(datatype == "ref")
            {
                throw(((Exception)Error::NotYetImplemented)[L("ReferenceTypePlanned")]);
            }
        }
        if(line->substr((*initial), 1) == KeyWD::Comma)
            (*initial)++;
        else if(line->substr((*initial), 1) == KeyWD::SemiColon)
        {
            (*initial)++;
            break;
        }
        else
            throw(Error::ConfigUnrecognizedCharR);
    }
    while(1)
    {
        if((*initial) == line->find(stop, *initial))
        {
            (*initial)++;
            return;
        }
        for(size_t i = 0; i < column.size(); i++)
        {
            ConfigColumn* cc = column[i];
            ParserHelper::skipSpaces(initial, line, lineNumber);
            bool bval;
            std::string sval;
            bool type;
            void* ival;
            void* dval;
            switch(cc->type())
            {
            case PropertyType::BOOL:
                bval = ParserHelper::getBool(initial, line, lineNumber);
                ((ConfigColumnBOOL*)cc)->add(bval);
                break;
            case PropertyType::STRING:
                sval = ParserHelper::getString(initial, line, lineNumber);
                ((ConfigColumnSTRING*)cc)->add(sval);
                break;
            case PropertyType::INT:
                ival = ParserHelper::getNumber(&type, initial, line, lineNumber);
                if(!type)
                    throw(Error::ParserExpectedInt);
                ((ConfigColumnINT*)cc)->add(*(int*)ival);
                break;
            case PropertyType::DOUBLE:
                dval = ParserHelper::getNumber(&type, initial, line, lineNumber);
                if(type)
                    throw(Error::ParserExpectedDouble);
                ((ConfigColumnDOUBLE*)cc)->add(*(double*)dval);
                break;
            }
            ParserHelper::skipSpaces(initial, line, lineNumber);
            if(line->substr(*initial,1) == KeyWD::Comma)
            {
                if(i+1 != column.size())
                    (*initial)++;
                else
                    throw(Error::CfgColumnLTooMuch);
            } else if(line->substr(*initial,1) == KeyWD::SemiColon)
            {
                if(i+1 == column.size())
                    (*initial)++;
                else
                    throw(Error::CfgColumnLTooFew);
            }
        }
    }
}

ConfigTable ConfigTable::select(ConfigColumnItem cci, std::string s)
{
    ConfigTable ctout(*this);
    ConfigColumn* col = column[selectColumn(s)];
    /**for(size_t i = 0; i < col.item.size(); i++)
    {
        if(cci == *col.item[i])
            ctout.column[i].item.push_back(col.item[i]);
    }**/
    return ctout;
}

size_t ConfigTable::selectColumn(std::string s)
{
    for(size_t i = 0; i < column.size(); i++)
    {
        if(s==column[i]->name())
            return i;
    }
    throw(Error::CfgColumnNotFound);
}

std::string ConfigTable::print()
{
    std::string out("(");
    for(ConfigColumn* cc : column)
    {
        out += cc->print() + ",\t";
    }
    out = out.substr(0, out.length()-2) + ";\n\t";
    for(size_t i = 0; i < UIDC->size(); i++)
    {
        for(ConfigColumn* cc : column)
        {
            out += cc->printCell(i) + ",\t";
        }
        out = out.substr(0, out.length()-2) + ";\n\t";
    }
    out = out.substr(0, out.length()-3) + ")";
    return out;
}

std::string ConfigTable::printHeader()
{
    std::string out;
    for(ConfigColumn* cc : column)
    {
        std::string pre("");
        if(cc->identity())
            pre = "@";
        if(cc->increment())
            pre+= "+";

        out += pre + cc->name() + ", ";
    }
    return out.substr(0, out.size()-2);
}

template <class ColumnType, class stdVal>
void ConfigTable::addColumn(std::string name, bool ainc, bool uid, stdVal val)
{
    ColumnType* cc = new ColumnType(S(name.c_str()), bool(ainc), bool(uid), val);
    column.push_back((ConfigColumn*)cc);
    if(uid)
        UIDC = (ConfigColumn*)cc;
}


