// Copyright (c) 2022-2025 Manuel Schneider

#include "docitem.h"
#include "docset.h"
#include "plugin.h"
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <albert/albert.h>
#include <albert/logging.h>
using namespace Qt::StringLiterals;
using namespace albert;
using namespace std;


DocItem::DocItem(const Docset &ds, const QString &t, const QString &n, const QString &p, const QString &a)
    : docset(ds), type(t), name(n), path(p), anchor(a) {}

QString DocItem::id() const { return docset.name + name; }

QString DocItem::text() const { return name; }

QString DocItem::subtext() const { return u"%1 %2"_s.arg(docset.title, type); }

QStringList DocItem::iconUrls() const
{
    return {
        u"comp:?src1=%1&size1=1&pos1=cc&src2=%2&size2=0.7&pos2=cc"_s
            .arg(u"gen:?text=📚"_s, docset.icon_path)
    };
}

QString DocItem::inputActionText() const { return name; }

vector<Action> DocItem::actions() const
{ return {{ id(), Plugin::tr("Open documentation"), [this] { open(); } }}; }

// Workaround for some browsers not opening "file:" urls having an anchor
void DocItem::open() const
{
    // QTemporaryFile will not work here because its deletion introduces race condition
    const auto cache = Plugin::instance()->cacheLocation();
    tryCreateDirectory(cache);
    if (QFile file(cache / "trampoline.html");
        file.open(QIODevice::WriteOnly))
    {
        auto url = u"file:%1/Contents/Resources/Documents/%2"_s.arg(docset.path, path);
        if (!anchor.isEmpty())
            url += u"#"_s + anchor;

        QTextStream stream(&file);
        stream << uR"(<html><head><meta http-equiv="refresh" content="0;%1"></head></html>)"_s
                      .arg(url);
        file.close();

        ::open(file.fileName());
    }
    else
        WARN << "Failed to open file for writing" << file.fileName() << file.errorString();
}
