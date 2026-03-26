/*
    SPDX-FileCopyrightText: 2026 Stanislav Aleksandrov <lightofmysoul@gmail.com>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>
#include <QtQmlIntegration>

namespace KWin
{

class Window;

// RAII holder of a Window::refOffscreenRendering() ref on the assigned window.
// Released on window change, window destruction, or this object's destruction.
class KwinWindowOffscreenRef : public QObject
{
    Q_OBJECT
    Q_PROPERTY(KWin::Window *window READ window WRITE setWindow NOTIFY windowChanged FINAL)
    QML_ELEMENT
public:
    explicit KwinWindowOffscreenRef(QObject *parent = nullptr);
    ~KwinWindowOffscreenRef() override;

    Window *window() const;
    void setWindow(Window *window);

Q_SIGNALS:
    void windowChanged();

private:
    Window *m_window = nullptr;
};

} // namespace KWin
