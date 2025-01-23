// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2023 NeoFOAM authors

#include "sharedExtensionLib.h"

BaseClass::BaseClass() {}
std::string BaseClass::name() { return "BaseClass"; }

DerivedClass::DerivedClass() {}
int DerivedClass::doSomeThing() { return 1; }
std::string DerivedClass::name() { return "DerivedClass"; }
std::string DerivedClass::doc() { return "DerivedClass documentation"; }
std::string DerivedClass::schema() { return "DerivedClass schema"; }


template<typename T>
BaseClass2<T>::BaseClass2()
{}

template<typename T>
std::string BaseClass2<T>::name()
{
    return "BaseClass2";
}


template<typename T>
DerivedClass2<T>::DerivedClass2()
{}

template<typename T>
T DerivedClass2<T>::doSomeThing(T in)
{
    return 2 * in;
}

template<typename T>
std::string DerivedClass2<T>::name()
{
    return "DerivedClass2";
}

template<typename T>
std::string DerivedClass2<T>::doc()
{
    return "DerivedClass2 documentation";
}

template<typename T>
std::string DerivedClass2<T>::schema()
{
    return "DerivedClass2 schema";
}
