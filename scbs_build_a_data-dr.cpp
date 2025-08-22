#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

// Define a data structure to hold automation script data
struct AutomationScript {
    string scriptName;
    vector<string> actions;
    map<string, string> variables;
};

// Function to parse automation script data from a string
AutomationScript parseScript(const string& scriptData) {
    AutomationScript script;
    vector<string> lines = {};
    size_t pos = 0;
    while ((pos = scriptData.find("\n")) != string::npos) {
        lines.push_back(scriptData.substr(0, pos));
        scriptData.erase(0, pos + 1);
    }
    lines.push_back(scriptData);

    // Parse script name
    script.scriptName = lines[0].substr(6); // assume "Script: " is fixed prefix

    // Parse actions
    for (size_t i = 1; i < lines.size(); i++) {
        if (lines[i].find("Action: ") == 0) {
            script.actions.push_back(lines[i].substr(7));
        } else if (lines[i].find("Var: ") == 0) {
            size_t colonPos = lines[i].find(":");
            string varName = lines[i].substr(4, colonPos - 4);
            string varValue = lines[i].substr(colonPos + 1);
            script.variables[varName] = varValue;
        }
    }

    return script;
}

int main() {
    string scriptData = R"(
Script: My Automation Script
Action: Click Button
Var: username=john Doe
Action: Enter Text
Var: password=hidden
Action: Submit Form
)";

    AutomationScript script = parseScript(scriptData);

    cout << "Script Name: " << script.scriptName << endl;
    cout << "Actions: ";
    for (const string& action : script.actions) {
        cout << action << " ";
    }
    cout << endl;
    cout << "Variables: ";
    for (const auto& var : script.variables) {
        cout << var.first << "=" << var.second << " ";
    }
    cout << endl;

    return 0;
}