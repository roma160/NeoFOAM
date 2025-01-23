// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2023 NeoFOAM authors

#pragma once

#include "NeoFOAM/core/runtimeSelectionFactory.hpp"

class BaseClass : public NeoFOAM::RuntimeSelectionFactory<BaseClass, NeoFOAM::Parameters<>>
{
public:

    BaseClass();
    virtual int doSomeThing() = 0;
    static std::string name();
};

class DerivedClass : public BaseClass::Register<DerivedClass>
{
public:

    DerivedClass();
    virtual int doSomeThing() override;
    static std::string name();
    static std::string doc();
    static std::string schema();
};

template<typename T>
class BaseClass2 : public NeoFOAM::RuntimeSelectionFactory<BaseClass2<T>, NeoFOAM::Parameters<>>
{
public:

    BaseClass2();
    virtual T doSomeThing(T in) = 0;
    static std::string name();
};

template<typename T>
class DerivedClass2 : public BaseClass2<T>::template Register<DerivedClass2<T>>
{
public:

    DerivedClass2();
    virtual T doSomeThing(T in) override;
    static std::string name();
    static std::string doc();
    static std::string schema();
};

// in case of registered template classes templates need to be instantiated explicitly
template class DerivedClass2<float>;
template class DerivedClass2<int>;
