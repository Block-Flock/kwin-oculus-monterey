/*
    SPDX-FileCopyrightText: 2026 Stanislav Aleksandrov <lightofmysoul@gmail.com>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "kwinvrshortcuts.h"

#include <KGlobalAccel>
#include <KLocalizedString>

#include <QAction>

namespace KWin
{

KWinVrShortcuts *KWinVrShortcuts::instance()
{
    static KWinVrShortcuts *s_instance = new KWinVrShortcuts();
    return s_instance;
}

KWinVrShortcuts::KWinVrShortcuts(QObject *parent)
    : QObject(parent)
{
    registerShortcut(QStringLiteral("Realign VR Window"),
                     i18nc("@action Realign VR Window", "Realign VR Window"),
                     {Qt::CTRL | Qt::META | Qt::Key_W},
                     &KWinVrShortcuts::realignWindowTriggered);

    registerShortcut(QStringLiteral("Grab Window"),
                     i18nc("@action Grab Window", "Grab Window"),
                     {Qt::CTRL | Qt::META | Qt::Key_E},
                     &KWinVrShortcuts::grabWindowTriggered);

    registerShortcut(QStringLiteral("Grab All Windows"),
                     i18nc("@action Grab All Windows", "Grab All Windows"),
                     {Qt::SHIFT | Qt::META | Qt::Key_E},
                     &KWinVrShortcuts::grabAllWindowsTriggered);

    registerShortcut(QStringLiteral("VR Hud"),
                     i18nc("@action VR Hud", "VR Hud"),
                     {Qt::CTRL | Qt::META | Qt::Key_H},
                     &KWinVrShortcuts::toggleHudTriggered);

    registerShortcut(QStringLiteral("Toggle VR Ray"),
                     i18nc("@action Toggle VR Ray", "Toggle VR Ray"),
                     {Qt::CTRL | Qt::META | Qt::Key_I},
                     &KWinVrShortcuts::toggleRayTriggered);

    registerShortcut(QStringLiteral("Toggle VR Cursor"),
                     i18nc("@action Toggle VR Cursor", "Toggle VR Cursor"),
                     {Qt::CTRL | Qt::META | Qt::Key_C},
                     &KWinVrShortcuts::toggleCursorTriggered);

    registerShortcut(QStringLiteral("Recenter VR View"),
                     i18nc("@action Recenter VR View", "Recenter VR View"),
                     {Qt::CTRL | Qt::META | Qt::Key_T},
                     &KWinVrShortcuts::recenterViewTriggered);

    registerShortcut(QStringLiteral("Hide VR Scene"),
                     i18nc("@action Hide VR Scene", "Hide VR Scene"),
                     {Qt::CTRL | Qt::META | Qt::Key_V},
                     &KWinVrShortcuts::hideVrSceneTriggered);
}

void KWinVrShortcuts::registerShortcut(const QString &name, const QString &text,
                                       const QKeySequence &defaultSequence,
                                       void (KWinVrShortcuts::*signal)())
{
    auto action = new QAction(this);
    action->setObjectName(name);
    action->setText(text);
    KGlobalAccel::self()->setDefaultShortcut(action, {defaultSequence});
    KGlobalAccel::self()->setShortcut(action, {defaultSequence});
    connect(action, &QAction::triggered, this, signal);
}

} // namespace KWin
