// Copyright (c) 2022-2024 Manuel Schneider

#pragma once
#include "docset.h"
#include <albert/extensionplugin.h>
#include <albert/indexqueryhandler.h>
class QNetworkReply;


class Plugin : public albert::ExtensionPlugin,
               public albert::util::IndexQueryHandler
{
    ALBERT_PLUGIN

public:

    Plugin();
    ~Plugin();

    void updateIndexItems() override;
    QWidget* buildConfigWidget() override;

    void updateDocsetList();
    const std::vector<Docset> &docsets() const;

    void downloadDocset(uint index);
    void cancelDownload();
    bool isDownloading() const;
    void removeDocset(uint index);

    static Plugin *instance();

private:

    void debug(const QString &);
    void error(const QString &, QWidget *modal_parent = nullptr);
    std::filesystem::path docsetsLocation() const;
    std::filesystem::path iconsLocation() const;

    std::vector<Docset> docsets_;
    QNetworkReply *download_ = nullptr;
    static Plugin *instance_;

signals:

    void docsetsChanged();
    void downloadStateChanged();
    void statusInfo(const QString&);

};
