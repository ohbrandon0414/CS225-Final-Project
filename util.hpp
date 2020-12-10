#pragma once

#include <vector>
#include <map>
#include <string>
#include <iostream>

using std::vector;
using std::map;
using std::string;

class OptionsParser
{
	private:
	typedef map<string, bool*> optsMap_t;
	typedef map<string, bool>  valueMap_t;
	valueMap_t valueMap; // not static to prevent still reachable memory
	
	optsMap_t  optsMap;
	vector<string *> args;

    void makeLower(string & str) {
        for (size_t i = 0; i < str.length(); i++) {
            str[i] = tolower(str[i]);
        }
    }

    string toLower(const string & str) {
        string s(str);
        makeLower(s);
        return s;
    }

	public:
	OptionsParser() {
        valueMap[""]      = true;

        valueMap["yes"]   = true;
        valueMap["no"]    = false;

        valueMap["on"]    = true;
        valueMap["off"]   = false;

        valueMap["true"]  = true;
        valueMap["false"] = false;

        valueMap["1"]     = true;
        valueMap["0"]     = false;
    }

	void addOption(const string & name, bool & setValue) { optsMap[name] = &setValue; }

	void addArg(string & setValue) { args.push_back(&setValue); }

	vector<string> parse(int argc, const char * const * argv) {
        vector<string> rawArgs(argv, argv + argc);
        return parse(rawArgs);
    }

	vector<string> parse(const vector<string> & rawArgs) {
        vector<string> unprocessedArgs;
        size_t out_arg_i = 0;

        for (size_t arg_i = 1; arg_i < rawArgs.size(); arg_i++) {
            const string & originalCaseArg = rawArgs[arg_i];
            string currarg = toLower(originalCaseArg);

            if (currarg.compare(0, 2, "--") == 0) { // long option
                bool invert = (currarg.compare(2, 2, "no") == 0);
                size_t name_i = (invert ? 4 : 2);
                size_t equalspos = currarg.find_first_of("=-", name_i);

                string name = currarg.substr(name_i, equalspos - name_i);
                string value = (equalspos >= currarg.length()) ? "" : currarg.substr(equalspos);

                optsMap_t::iterator option = optsMap.find(name);
                if (option == optsMap.end()) {
                    std::cerr << "Unknown option: " << currarg << std::endl;
                    exit(-1);
                }

                valueMap_t::iterator valueIt = valueMap.find(value);
                if (valueIt == valueMap.end()) {
                    std::cerr << "Unknown value: " << currarg << std::endl;
                    exit(-1);
                }

                *option->second = valueIt->second ^ invert;
            } // "--"

            else if (currarg[0] == '-') { //string of single char options
                for (size_t c = 1; currarg[c] != '\0'; c++) {
                    optsMap_t::iterator option = optsMap.find(string(1,currarg[c]));
                    if (option == optsMap.end()) {
                        std::cerr << "Unknown option: -" << currarg[c] << std::endl;
                        exit(-1);
                    }
                    *option->second = true;
                }
            }

            else { //positional argument
                if (out_arg_i < args.size())
                    *args[out_arg_i] = originalCaseArg;
                else
                    unprocessedArgs.push_back(originalCaseArg);
                out_arg_i++;
            }
        }

        return unprocessedArgs;
    }
};

