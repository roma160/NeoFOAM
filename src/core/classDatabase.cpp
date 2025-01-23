// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2023 NeoFOAM authors

#include "NeoFOAM/core/classDatabase.h"

NeoFOAM::BaseClassData::BaseClassData() = default;

void NeoFOAM::BaseClassDocumentation::registerClass(
    std::string name,
    std::function<std::string(const std::string&)> doc,
    std::function<std::string(const std::string&)> schema,
    std::function<std::vector<std::string>()> entries
)
{
    // if not already registered
    auto& to_update = docTable()[name];
    to_update.doc = doc;
    to_update.schema = schema;
    to_update.entries = entries;
}

std::string NeoFOAM::BaseClassDocumentation::doc(
    const std::string& baseClassName, const std::string& derivedClassName
)
{
    return docTable().at(baseClassName).doc(derivedClassName);
}

std::string NeoFOAM::BaseClassDocumentation::schema(
    const std::string& baseClassName, const std::string& derivedClassName
)
{
    // get the schema of the derived class
    return docTable().at(baseClassName).schema(derivedClassName);
}

std::vector<std::string> NeoFOAM::BaseClassDocumentation::entries(const std::string& baseClassName)
{
    return docTable().at(baseClassName).entries();
}

NeoFOAM::BaseClassDocumentation::LookupTable& NeoFOAM::BaseClassDocumentation::docTable()
{
    static LookupTable tbl;
    return tbl;
}
