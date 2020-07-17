#ifndef CONNECTIOWIDGET_H
#define CONNECTIOWIDGET_H

#include <QMenu>
#include <QWidget>
#include <QSplitter>
#include "netconnection.h"
#include "scripteditor.h"
#include "scriptitem.h"
#include "global.h"

class QListWidgetItem;

namespace Ui {
class ConnectionWidget;
}

class ConnectionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConnectionWidget(QWidget *parent = Q_NULLPTR);
    ~ConnectionWidget();

private:
    Ui::ConnectionWidget *ui;
    int m_type;
    NetConnection *m_netConnection;
    ScriptEditor *m_scriptEditor;
    QMenu *m_menuScriptEdit;

    QString m_styleString;

signals:
    void defaultSettings(int type, const NetSettingsStruct &settings);
    void showScriptMenu();

public slots:
    void setType(int type);
    inline int type() const {return m_type;}

    void setNetConnection(NetConnection *pointer);
    inline NetConnection *netConnection(){return m_netConnection;}

    void setSettings(const NetSettingsStruct &settings);
    NetSettingsStruct settings();

    void onScriptLoad();
    void onScriptSave();
    void onScriptAdd();
    void onScriptEdit();
    void onScriptRemove();

    void addScriptItem(const QString &name, const QString &text);
    QStringList scriptsNames();
    QString currentScriptName();

    void setStyleString(const QString &styleStr);
    void setScriptEditor(ScriptEditor *editor){m_scriptEditor = editor;}
private slots:
    void setStatusMessage(const QString &message, int type);
    void setDatagram(const QByteArray &data, const QString &host, quint16 port);
    void onScriptContextMenuRequested(const QPoint &pos);
    void onSettingsChanged();
    void onSendClicked();
    void onCurrentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
};

#endif // CONNECTIOWIDGET_H
