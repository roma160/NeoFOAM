// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2023 NeoFOAM authors

#pragma once

#include <any>
#include <unordered_map>
#include <functional>

#include "error.hpp"

namespace NeoFOAM
{

/**
 * @brief Class representing the documentation for a derived class.
 *
 * This class stores the documentation and schema information for a derived class.
 */
class DerivedClassDocumentation
{
public:

    std::function<std::string()> doc;
    std::function<std::string()> schema;
};


/**
 * @class BaseClassData
 * @brief Represents the data for a base class.
 *
 * This class holds the information related to a base class, including documentation,
 * schema, and entries.
 */
class BaseClassData
{
public:

    std::function<std::string(const std::string&)>
        doc; /**< Function to retrieve the documentation for a specific entry. */
    std::function<std::string(const std::string&)>
        schema; /**< Function to retrieve the schema for a specific entry. */
    std::function<std::vector<std::string>()>
        entries; /**< Function to retrieve the list of entries. */

    std::any derivedClassesConstructors;
    std::unordered_map<std::string, DerivedClassDocumentation> derivedClassesDoc;

    BaseClassData();
};

/**
 * @class BaseClassDocumentation
 * @brief Provides a mechanism for registering and retrieving documentation for base and derived
 * classes.
 *
 * The BaseClassDocumentation class allows users to register documentation for base classes and
 * retrieve documentation for derived classes based on the registered information. It also provides
 * methods to retrieve the schema and entries associated with a base class.
 */
class BaseClassDocumentation
{
public:

    using LookupTable = std::unordered_map<std::string, BaseClassData>;

    static void registerClass(
        std::string name,
        std::function<std::string(const std::string&)> doc,
        std::function<std::string(const std::string&)> schema,
        std::function<std::vector<std::string>()> entries
    );

    /**
     * Returns the documentation for a derived class based on the base class name.
     *
     * @param baseClassName The name of the base class.
     * @param derivedClassName The name of the derived class.
     * @return The documentation for the derived class.
     */
    static std::string doc(const std::string& baseClassName, const std::string& derivedClassName);

    /**
     * Returns the schema of the derived class based on the base class name and derived class name.
     *
     * @param baseClassName The name of the base class.
     * @param derivedClassName The name of the derived class.
     * @return The schema of the derived class.
     */
    static std::string
    schema(const std::string& baseClassName, const std::string& derivedClassName);

    /**
     * Returns a vector of strings representing the entries for a given base class name.
     *
     * @param baseClassName The name of the base class.
     * @return A vector of strings representing the entries.
     */
    static std::vector<std::string> entries(const std::string& baseClassName);

    static LookupTable& docTable();
};

}; // namespace NeoFOAM
