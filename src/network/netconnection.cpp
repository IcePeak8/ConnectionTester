#include "netconnection.h"

NetConnection::NetConnection(QObject *parent):QObject(parent)
{

}

NetConnection::~NetConnection()
{
    for(int i=0;i<m_scriptsMap.size();++i)
    {
        ScriptItem *script = m_scriptsMap.values().at(i);
        script->clearScript();
        script->disconnect();
        delete script;
    }

    m_scriptsMap.clear();
}

ScriptItem *NetConnection::addScript(const QString &name, const QString &text)
{
    removeScript(name);

    ScriptItem *script = new ScriptItem(this);
    script->setName(name);
    script->setScript(text);
    connect(this, &NetConnection::datagram, script, &ScriptItem::setDatagram);
    connect(script, &ScriptItem::datagram, this, &NetConnection::sendDatagram);
    connect(script, &ScriptItem::status, this, &NetConnection::status);

    m_scriptsMap.insert(name, script);
    return script;
}

QString NetConnection::scriptText(const QString &name)
{
    QString result;

    if(m_scriptsMap.contains(name))
        result = m_scriptsMap.value(name)->scriptText();

    return result;
}

void NetConnection::removeScript(const QString &name)
{
    if(!m_scriptsMap.contains(name))
        return;

    ScriptItem *script = m_scriptsMap.value(name);
    m_scriptsMap.remove(name);

    script->clearScript();
    script->disconnect();
    delete script;
}
