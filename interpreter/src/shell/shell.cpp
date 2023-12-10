#include "shell/shell.hpp"

#include "shell/parser/parser.hpp"
#include "shell/parser/lexer.hpp"

namespace shell {

/**
 * Borrowed from: https://wandbox.org/permlink/TS56MAb97NQXkepj
 */
template<typename T, typename K>
auto mapGetOptional(T&& map, K&& key)
{
    auto it = map.find(std::forward<K>(key));
    if (it == map.end()) return std::optional<typename std::decay<T>::type::mapped_type>{};
    return std::optional<typename std::decay<T>::type::mapped_type>{it->second};
}

template<typename T>
std::ostream& printMap(std::ostream& stream, T&& map)
{
    if(map.empty()) {
        stream << "MAP IS EMPTY";
    }

    for(auto it = map.cbegin(); it != map.cend(); ++it)
    {
        auto& key = it->first;
        auto& val = it->second;

        stream << key << ": " << val << std::endl;
    }

    return stream;
}

Shell::Shell()
: _lexer(), _parser(_lexer), _userPrompt(std::nullopt)
{

}

Shell::~Shell()
{
    
}

void Shell::runInteractive(std::istream& input, std::ostream& output, std::ostream& error)
{
    while(true) {
        output << _userPrompt.value_or("\x1B[92mPROS $> \x1b[0m");

        std::optional<AstNode> astOptional = _parser.parseNextStatement();

        if(!astOptional)
            break;
        
        AstNode astTree = astOptional.value();

        //astTree.print(output);

        //output << "\nExecuting entered input:\n" << std::endl;

        // Execute the command.
        // TODO: This will need moved and made more safe eventually
        std::string commandName = astTree.getStringValue();

        if(auto search = _commands.find(commandName); search != _commands.end()) {
            CommandCallback cb = search->second;

            CommandArgs args;
            args._name = commandName;
            args._shell = this;

            // Build command helper based on ast
            for(AstNode child : astTree.children()) {
                
                if(child.type() == AstNode::COMMAND_UNNAMED_ARG) {
                    AstNode subChild = child.children()[0];

                    switch(subChild.type()) 
                    {
                    case AstNode::NUMBER_LITERAL:
                        if(auto baseUnitOpt = evaluateNumberToBase(subChild.getNumberValue())) {
                            Number baseUnit = baseUnitOpt.value();

                            args.addNewUnnamedNumber(baseUnit);
                        }
                        else {
                            std::cerr << "Could not convert number" << std::endl;
                        }
                        break;

                    case AstNode::STRING_LITERAL:
                        args.addUnnamedString(subChild.getStringValue());
                        break;

                    case AstNode::BOOLEAN_LITERAL:
                        args.addUnnamedBoolean(subChild.getBooleanValue());
                        break;
                    }
                }
                else if(child.type() == AstNode::COMMAND_NAMED_ARG) {
                    std::string name = child.getStringValue();

                    AstNode subChild = child.children()[0];

                    switch(subChild.type()) 
                    {
                    case AstNode::NUMBER_LITERAL:
                        if(auto baseUnitOpt = evaluateNumberToBase(subChild.getNumberValue())) {
                            Number baseUnit = baseUnitOpt.value();

                            args.addNewNamedNumber(name, baseUnit);
                        }
                        else {
                            std::cerr << "Could not convert number" << std::endl;
                        }

                        break;

                    case AstNode::STRING_LITERAL:
                        args.addNamedString(name, subChild.getStringValue());
                        break;

                    case AstNode::BOOLEAN_LITERAL:
                        args.addNamedBoolean(name, subChild.getBooleanValue());
                        break;
                    }
                }
            }

            cb(args);
        }
        else {
            error << "Command \"" << commandName << "\" not found" << std::endl;

            continue;
        }
    }

    std::cerr << "EOF" << std::endl;
}

void Shell::runNonInteractive(std::istream& input, std::ostream& output, std::ostream& error)
{

}

void Shell::setPrompt(std::string prompt)
{
    _userPrompt = prompt;
}

void Shell::resetPrompt()
{
    _userPrompt = std::nullopt;
}

void Shell::registerCommand(std::string name, CommandCallback callback)
{
    _commands.insert(std::make_pair(name, callback));
}

void Shell::addUnitSystem(std::string systemName, std::string baseUnit)
{
    std::cout << "Creating unit system \"" << systemName 
        << "\" with base unit \"" << baseUnit << "\"" << std::endl;

    
    std::cout << "UNIT SYSTEM MAP BEFORE:" << std::endl;
    printMap(std::cout, unitSystems);

    UnitSystemInfo systemInfo;
    systemInfo.systemName = systemName;
    systemInfo.baseUnit = baseUnit;

    unitSystems[systemName] = systemInfo;
    unitToSystem[baseUnit] = systemName;

    std::cout << "UNIT SYSTEM MAP AFTER" << std::endl;
    printMap(std::cout, unitSystems);
}

void Shell::addUnitSuffix(std::string systemName,
    std::string                     unitSuffix, 
    std::function<double(double)>   toBaseUnit,
    std::function<double(double)>   toUnit
)
{
    std::cout << "Adding unit \"" << unitSuffix << "\" to system \""
        << systemName << "\"" << std::endl;

    std::cout << "UNIT SYSTEM MAP BEFORE:" << std::endl;
    printMap(std::cout, unitSystems);

    if(auto itt = unitSystems.find(systemName); itt != unitSystems.end())
    {
        UnitSystemInfo& info = itt->second;

        UnitInfo unitInfo;
        unitInfo.suffix = unitSuffix;
        unitInfo.toBaseUnit = toBaseUnit;
        unitInfo.toUnit = toUnit;

        info.units[unitSuffix] = unitInfo;

        unitToSystem[unitSuffix] = systemName;

        std::cout << "UNIT SYSTEM MAP AFTER:" << std::endl;
        printMap(std::cout, unitSystems);
        std::cout << std::endl;
    }
    else {
        std::cerr << "Could not find unit system!!" << std::endl;
    }
}

std::optional<Number> Shell::evaluateNumberToBase(Number number) const
{
    if(number.suffix.empty()) {
        std::cerr << "Number suffix is blank"  << std::endl;
        return number;
    }

    if(auto systemNameItt = unitToSystem.find(number.suffix); systemNameItt != unitToSystem.end()) 
    {
        const std::string& systemName = systemNameItt->second;


        if(auto systemInfoItt = unitSystems.find(systemName); systemInfoItt != unitSystems.end()) {
            const UnitSystemInfo& systemInfo = systemInfoItt->second;

            if(number.suffix == systemInfo.baseUnit) {
                std::cerr << "Number is the base unit. No mapping necessary"  << std::endl;
                return number;
            }

            if(auto unitInfoItt = systemInfo.units.find(number.suffix); unitInfoItt != systemInfo.units.end()) {
                const UnitInfo& unitInfo = unitInfoItt->second;

                return Number {
                    unitInfo.toBaseUnit(number.value),
                    systemInfo.baseUnit
                };
            }
            else {
                std::cerr << "Unit suffix could not be mapped to the unit info"  << std::endl;
            }
        }
        else {
            std::cerr << "Number system name could not be mapped to it's info"  << std::endl;
        }
    }
    else {
        std::cerr << "Number suffix could not be mapped to it's unit system!"  << std::endl;
    }

    return std::nullopt;
}

std::optional<Number> Shell::evaluateNumberToUnit(Number number, std::string unit) const
{
    if(number.suffix.empty()) {
        std::cerr << "Number suffix is blank"  << std::endl;
        return number;
    }

    if(auto systemNameItt = unitToSystem.find(unit); systemNameItt != unitToSystem.end()) 
    {
        const std::string& systemName = systemNameItt->second;

        if(auto systemInfoItt = unitSystems.find(systemName); systemInfoItt != unitSystems.end()) {
            const UnitSystemInfo& systemInfo = systemInfoItt->second;

            if(unit == systemInfo.baseUnit) {
                std::cerr << "Number is the base unit. No mapping necessary"  << std::endl;
                return number;
            }

            if(auto unitInfoItt = systemInfo.units.find(unit); unitInfoItt != systemInfo.units.end()) {
                const UnitInfo& unitInfo = unitInfoItt->second;

                return Number {
                    unitInfo.toUnit(number.value),
                    unit
                };
            }
            else {
                std::cerr << "Unit suffix could not be mapped to the unit info"  << std::endl;
            }
        }
        else {
            std::cerr << "Number system name could not be mapped to it's info"  << std::endl;
        }
    }
    else {
        std::cerr << "Number suffix could not be mapped to it's unit system!"  << std::endl;
    }

    return number;
}

std::ostream& operator<<(std::ostream& stream, const Shell::UnitInfo& info) 
{
    stream << "(" << info.suffix << ", toBase, toUnit)";

    return stream;
}
std::ostream& operator<<(std::ostream& stream, const Shell::UnitSystemInfo& info)
{
    stream << "(" << info.systemName << ", " << info.baseUnit << ", \n";

    printMap(stream, info.units);

    stream << ")" << std::endl;

    return stream;
}

} // namespace shell