/*
 * Properties.h
 *
 * URL:      https://github.com/panchaBhuta/cpp-properties_RecVar
 * Version:  2.0.rv-1.0
 *
 * Copyright (C) 2022 Gautam Dhar
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

#ifndef PROPERTIES_H_
#define PROPERTIES_H_

#include <string>
#include <vector>
#include <map>

#include <cpp-properties/exports/cppproperties_export.h>
#include <cpp-properties/PropertiesException.h>
#include <cpp-properties/PropertyNotFoundException.h>

namespace cppproperties {

class Properties {
public:
    Properties();
    virtual ~Properties();

    /**
     * Gets the raw property value from a given key. If the value contains any
     * '${inner-key}' , those keys are not replaced.
     *
     * This method throws a PropertyNotFoundException when a given key does not
     * exist.
     */
    std::string GetProperty(const std::string& key) const;

    /**
     * Gets the expanded property value from a given key. If the value contains any
     * '${inner-key}' , those keys are replaced with their values.
     *
     * This method throws a PropertyNotFoundException when a given key does not
     * exist.
     * PropertyException when closing brace '}' not found in value.
     * PropertyException when recursive inner expansion level is more than 10.
     */
    std::string GetPropertyExpanded(const std::string& key) const {
        return _GetPropertyExpanded(key,0);
    }

    /**
     * Gets the property value from a given key. Use a default value if not found.
     */
    std::string GetProperty(const std::string& key, const std::string& defaultValue) const;

    /**
     * Gets the list of property names.
     */
    std::vector<std::string> GetPropertyNames() const;

    /**
     * Adds a new property. If the property already exists, it'll overwrite
     * the old one.
     */
    void AddProperty(const std::string& key, const std::string& value);

    /**
     * Removes the property from a given key.
     *
     * If the property doesn't exist a PropertyNotFoundException will be thrown.
     */
    void RemoveProperty(const std::string& key);
private:
    std::string _GetPropertyExpanded(const std::string& key, size_t iter) const;

    // to preserve the order
    std::vector<std::string> _keys;
    std::map<std::string, std::string> _properties;
};

} /* namespace cppproperties */

#endif /* PROPERTIES_H_ */
