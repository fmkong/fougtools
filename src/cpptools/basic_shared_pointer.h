/****************************************************************************
**  FougTools
**  Copyright Fougue (1 Mar. 2011)
**  contact@fougue.pro
**
** This software is a computer program whose purpose is to provide utility
** tools for the C++ language and the Qt toolkit.
**
** This software is governed by the CeCILL-C license under French law and
** abiding by the rules of distribution of free software.  You can  use,
** modify and/ or redistribute the software under the terms of the CeCILL-C
** license as circulated by CEA, CNRS and INRIA at the following URL
** "http://www.cecill.info".
****************************************************************************/

#pragma once

#include <cstddef>

namespace cpp {

template <typename T>
class BasicSharedPointer
{
public:
    BasicSharedPointer(T* data = NULL);
    BasicSharedPointer(const BasicSharedPointer<T>& other);
    ~BasicSharedPointer();

    T& operator*() const;
    T* operator->() const;
    T* data() const;

    bool isNull() const;

    BasicSharedPointer<T>& operator=(const BasicSharedPointer<T>& other);

private:
    void addRef();
    void releaseRef();

    T* m_data;
    unsigned* m_refCount;
};

//
// Implementation
//

/*!
 * \class BasicSharedPointer
 * \brief Provides basic sharing of a pointer
 *
 * BasicSharedPointer is an automatic, shared pointer in C++. It behaves exactly
 * like a normal pointer for normal purposes, including respect for constness.
 *
 * BasicSharedPointer will delete the pointer it is holding when it goes out of
 * scope, provided no other BasicSharedPointer objects are referencing it.
 *
 * "Basic" means that there is no thread-safety or any sophisticated management.
 * It aims to stay light for simple uses.
 *
 * \headerfile basic_shared_pointer.h <cpptools/basic_shared_pointer.h>
 * \ingroup cpptools
 */

template<typename T>
BasicSharedPointer<T>::BasicSharedPointer(T* data)
    : m_data(data),
      m_refCount(new unsigned(1))
{
}

template<typename T>
BasicSharedPointer<T>::BasicSharedPointer(const BasicSharedPointer<T>& other)
    : m_data(other.m_data),
      m_refCount(other.m_refCount)
{
    this->addRef();
}

template<typename T>
BasicSharedPointer<T>::~BasicSharedPointer()
{
    this->releaseRef();
}

template<typename T>
T& BasicSharedPointer<T>::operator*() const
{
    return *m_data;
}

template<typename T>
T* BasicSharedPointer<T>::operator->() const
{
    return m_data;
}

template<typename T>
T* BasicSharedPointer<T>::data() const
{
    return m_data;
}

template<typename T>
bool BasicSharedPointer<T>::isNull() const
{
    return m_data == NULL;
}

template<typename T>
BasicSharedPointer<T>& BasicSharedPointer<T>::operator=(const BasicSharedPointer<T>& other)
{
    if (this != &other) {
        m_data = other.m_data;
        m_refCount = other.m_refCount;
        this->addRef();
    }
    return *this;
}

template<typename T>
void BasicSharedPointer<T>::addRef()
{
    ++(*m_refCount);
}

template<typename T>
void BasicSharedPointer<T>::releaseRef()
{
    --(*m_refCount);
    if (*m_refCount == 0) {
        delete m_data;
        delete m_refCount;
        m_data = NULL;
        m_refCount = NULL;
    }
}

} // namespace cpp
