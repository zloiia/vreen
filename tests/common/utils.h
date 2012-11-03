/****************************************************************************
**
** Vreen - vk.com API Qt bindings
**
** Copyright © 2012 Aleksey Sidorov <gorthauer87@ya.ru>
**
*****************************************************************************
**
** $VREEN_BEGIN_LICENSE$
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
** See the GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see http://www.gnu.org/licenses/.
** $VREEN_END_LICENSE$
**
****************************************************************************/
#ifndef UTILS_H
#define UTILS_H
#include "client.h"
#include <QTest>

inline QString getVariable(const char *name)
{
    return qgetenv(name);
}

#define VREEN_ADD_LOGIN_VARS() \
    QTest::addColumn<QString>("login"); \
    QTest::addColumn<QString>("password"); \
    QTest::newRow("From enviroment variables VK_LOGIN and VK_PASSWORD") \
    << getVariable("VREEN_LOGIN") \
    << getVariable("VREEN_PASSWORD");

//TODO add oauth connection support

#define VREEN_CREATE_CLIENT() \
    QFETCH(QString, login); \
    QFETCH(QString, password); \
	Vreen::Client client(login, password); \
    QEventLoop loop; \
    connect(&client, SIGNAL(onlineStateChanged(bool)), &loop, SLOT(quit())); \
    connect(&client, SIGNAL(error(Vreen::Client::Error)), &loop, SLOT(quit())); \
    if (login.isEmpty() || password.isEmpty()) \
        QSKIP("Please set VREEN_LOGIN and VREEN_PASSWORD environment variables", SkipAll); \
    client.connectToHost(); \
    loop.exec();

#endif // UTILS_H

