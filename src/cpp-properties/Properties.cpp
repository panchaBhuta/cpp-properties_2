/*
 * Copyright (c) 2014 Fredy Wijaya
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include <algorithm>
#include <cpp-properties/Properties.h>

namespace cppproperties {

Properties::Properties() {
}

Properties::~Properties() {
    _keys.clear();
    _properties.clear();
}

std::string Properties::GetProperty(const std::string& key) const {
    auto fdIter = _properties.find(key);
    if (fdIter == _properties.end()) {
        throw PropertyNotFoundException(key + " does not exist");
    }
    return fdIter->second;
}

std::string Properties::GetProperty(const std::string& key, const std::string& defaultValue) const {
    auto fdIter = _properties.find(key);
    if (fdIter == _properties.end()) {
        return defaultValue;
    }
    return fdIter->second;
}

std::vector<std::string> Properties::GetPropertyNames() const {
    return _keys;
}

void Properties::AddProperty(const std::string& key, const std::string& value) {
    auto isInsert = _properties.insert_or_assign(key, value);
    if (isInsert.second) {
        _keys.push_back(key);
    }
}

void Properties::RemoveProperty(const std::string& key) {
    std::map<std::string, std::string>::size_type eleSize = _properties.erase(key);
    if (0 == eleSize) {
        throw PropertyNotFoundException(key + " does not exist");
    }
    _keys.erase(std::remove(_keys.begin(), _keys.end(), key), _keys.end());
}

std::string Properties::_GetPropertyExpanded(const std::string& key, const size_t iter) const {
    if( iter > 10) {
        // to prevent infinite cyclic expansion
        throw PropertiesException("recursion expansion at key='" + key + "' reached more than 10, which is not supported.");
    }

    std::string val = GetProperty(key);
    std::string::size_type ns = val.find("${");
    while (ns != std::string::npos) {
        ns+=2;
        const std::string::size_type ne = val.find("}", ns);
        if (ne != std::string::npos) {
            const std::string innerKey = val.substr(ns,(ne-ns));
            const std::string innerVal = _GetPropertyExpanded(innerKey,iter+1);
            val = val.replace(ns-2,(ne-ns)+3,innerVal);
        } else {
            throw PropertiesException("closing brace '}' not found in value='"+val+"'");
        }
        ns = val.find("${", ns-2);
    }
    return val;
}

} /* namespace cppproperties */
