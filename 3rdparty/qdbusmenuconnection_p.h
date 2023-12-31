// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#ifndef DBUSCONNECTION_H
#define DBUSCONNECTION_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtCore/QString>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusVariant>
#include <QLoggingCategory>

class QDBusServiceWatcher;

namespace thirdparty {

#ifndef QT_NO_SYSTEMTRAYICON
Q_DECLARE_LOGGING_CATEGORY(dLcMenu);
class QDBusTrayIcon;
#endif // QT_NO_SYSTEMTRAYICON

class QDBusMenuConnection : public QObject
{
    Q_OBJECT

public:
    QDBusMenuConnection(QObject *parent = 0, const QString &serviceName = QString());
    QDBusConnection connection() const { return m_connection; }
    QDBusServiceWatcher *dbusWatcher() const { return m_dbusWatcher; }
    bool isStatusNotifierHostRegistered() const { return m_statusNotifierHostRegistered; }
#ifndef QT_NO_SYSTEMTRAYICON
    bool registerTrayIconMenu(QDBusTrayIcon *item);
    void unregisterTrayIconMenu(QDBusTrayIcon *item);
    bool registerTrayIcon(QDBusTrayIcon *item);
    bool registerTrayIconWithWatcher(QDBusTrayIcon *item);
    bool unregisterTrayIcon(QDBusTrayIcon *item);
#endif // QT_NO_SYSTEMTRAYICON

Q_SIGNALS:
#ifndef QT_NO_SYSTEMTRAYICON
    void trayIconRegistered();
#endif // QT_NO_SYSTEMTRAYICON

private Q_SLOTS:
    void dbusError(const QDBusError &error);

private:
    QDBusConnection m_connection;
    QDBusServiceWatcher *m_dbusWatcher;
    bool m_statusNotifierHostRegistered;
};

} // namespace thirdparty

#endif // DBUSCONNECTION_H
