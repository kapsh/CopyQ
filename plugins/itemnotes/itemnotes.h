/*
    Copyright (c) 2013, Lukas Holecek <hluk@email.cz>

    This file is part of CopyQ.

    CopyQ is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    CopyQ is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with CopyQ.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ITEMNOTES_H
#define ITEMNOTES_H

#include "item/itemwidget.h"

#include <QScopedPointer>
#include <QWidget>

namespace Ui {
class ItemNotesSettings;
}

class QLabel;
class QTextEdit;
class QTimer;

class ItemNotes : public QWidget, public ItemWidget
{
    Q_OBJECT

public:
    ItemNotes(ItemWidget *childItem, const QString &text,
              bool notesAtBottom, bool showIconOnly, bool showToolTip);

    virtual void setCurrent(bool current);

protected:
    virtual void highlight(const QRegExp &re, const QFont &highlightFont,
                           const QPalette &highlightPalette);

    virtual void updateSize();

    virtual void mousePressEvent(QMouseEvent *e);

    virtual void mouseDoubleClickEvent(QMouseEvent *e);

    virtual void contextMenuEvent(QContextMenuEvent *e);

    virtual void mouseReleaseEvent(QMouseEvent *e);

    virtual void paintEvent(QPaintEvent *event);

    virtual bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void onSelectionChanged();
    void showToolTip();

private:
    QTextEdit *m_notes;
    QLabel *m_icon;
    QScopedPointer<ItemWidget> m_childItem;
    bool m_notesAtBottom;
    QTimer *m_timerShowToolTip;
    QString m_toolTipText;
};

class ItemNotesLoader : public QObject, public ItemLoaderInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID COPYQ_PLUGIN_ITEM_LOADER_ID)
    Q_INTERFACES(ItemLoaderInterface)

public:
    ItemNotesLoader();

    ~ItemNotesLoader();

    virtual QString id() const { return "itemnotes"; }
    virtual QString name() const { return tr("Notes"); }
    virtual QString author() const { return QString(); }
    virtual QString description() const { return tr("Display notes for items."); }
    virtual QVariant icon() const { return QVariant(0xf14b); }

    virtual QStringList formatsToSave() const;

    virtual QVariantMap applySettings();

    virtual void loadSettings(const QVariantMap &settings) { m_settings = settings; }

    virtual QWidget *createSettingsWidget(QWidget *parent);

    virtual ItemWidget *transform(ItemWidget *itemWidget, const QModelIndex &index);

private:
    QVariantMap m_settings;
    Ui::ItemNotesSettings *ui;
};

#endif // ITEMNOTES_H
