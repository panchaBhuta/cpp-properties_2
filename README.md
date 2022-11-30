# cpp-properties (Recursive-Variable)
A small C++ Java properties parser.

## How to build
cpp-properties uses CMake build system (http://www.cmake.org/).

```
./build.sh
```

## Examples
__input.properties__
```
key1=value1
key2=value2
key3=value3
key4=value4
dir1=dname1
dir2=dname2
dir3=dname3
dir123=${dir1}/${dir2}/${dir3}
dir123123=${dir123}/${dir123}
```

__output.properties__
```
key100=value100
key200=value200
key300=value300
```

__Main.cpp__
```c++
#include <iostream>
#include "PropertiesParser.h"
using namespace std;
using namespace cppproperties;

void TestRead() {
    Properties props = PropertiesParser::Read("input.properties");
    vector<string> names = props.GetPropertyNames();
    for (vector<string>::const_iterator i = names.begin(); i != names.end(); ++i) {
        cout << *i << " = " << props.GetProperty(*i) << endl;
    }
}

void TestPropertyExpanded() {
    Properties props = PropertiesParser::Read("input.properties");
    vector<string> names = props.GetPropertyNames();
    for (vector<string>::const_iterator i = names.begin(); i != names.end(); ++i) {
        cout << *i << " = " << props.GetPropertyExpanded(*i) << endl;
    }
}

void TestWrite() {
    Properties props;
    props.AddProperty("key100", "value100");
    props.AddProperty("key200", "value200");
    props.AddProperty("key300", "value300");
    PropertiesParser::Write("output.properties", props);
}

int main() {
    TestRead();
    TestPropertyExpanded();
    TestWrite();
    return 0;
}
```
