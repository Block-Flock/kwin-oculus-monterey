/*
    SPDX-FileCopyrightText: 2026 Stanislav Aleksandrov <lightofmysoul@gmail.com>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "kwinwindowoffscreenref.h"

#include "window.h"

namespace KWin
{

KwinWindowOffscreenRef::KwinWindowOffscreenRef(QObject *parent)
    : QObject(parent)
{
}

KwinWindowOffscreenRef::~KwinWindowOffscreenRef()
{
    if (m_window) {
        m_window->unrefOffscreenRendering();
    }
}

Window *KwinWindowOffscreenRef::window() const
{
    return m_window;
}

void KwinWindowOffscreenRef::setWindow(Window *window)
{
    if (m_window == window) {
        return;
    }

    if (m_window) {
        disconnect(m_window, nullptr, this, nullptr);
        m_window->unrefOffscreenRendering();
    }

    m_window = window;

    if (m_window) {
        connect(m_window, &QObject::destroyed, this, [this] {
            m_window = nullptr;
        });
        m_window->refOffscreenRendering();
    }

    Q_EMIT windowChanged();
}

} // namespace KWin
