/****************************************************************************
**  FougTools
**  Copyright Fougue (30 Mar. 2015)
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

#include "unique_id.h"

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QSet>

namespace qtcore {

namespace internal {

class UniqueIdRegistration
{
public:
    QMutex m_mutex;
    QSet<int> m_set;
};

} // namespace internal

Q_GLOBAL_STATIC(internal::UniqueIdRegistration, uniqueIdRegistrationHelper)

/*!
 * \class UniqueId
 * Provides services around creation of (app execution scope) unique indexes
 *
 * \headerfile unique_id.h <qttools/core/unique_id.h>
 * \ingroup qttools_core
 *
 */

/*!
 * \struct UniqueId::RegisterResult
 * \brief Stores the result of UniqueId::registerId()
 */

/*!
 * \brief Registers a new unique index.
 *
 * Returns a value between \p min and \p max that has not yet been registered.
 *
 * This is a generalization of QEvent::registerEventType()
 *
 * \note This function is thread-safe.
 *
 */
UniqueId::RegisterResult UniqueId::registerId(int min, int max)
{
    UniqueId::RegisterResult result;
    result.isValid = false;
    result.id = -1;

    internal::UniqueIdRegistration* reg = uniqueIdRegistrationHelper();
    if (reg == NULL || min > max)
        return result;

    QMutexLocker locker(&reg->m_mutex);
    Q_UNUSED(locker);

    // Find a free id, starting at \p max and decreasing
    int id = max;
    while (reg->m_set.contains(id) && id >= min)
        --id;
    if (id >= min) {
        reg->m_set.insert(id);
        result.isValid = true;
        result.id = id;
        return result;
    }

    return result;
}

//! Has \p id already been registered with UniqueId::registerId() ?
bool UniqueId::isRegistered(int id)
{
    internal::UniqueIdRegistration* reg = uniqueIdRegistrationHelper();
    if (reg == NULL)
        return false;
    return reg->m_set.contains(id);
}

} // namespace qtcore
