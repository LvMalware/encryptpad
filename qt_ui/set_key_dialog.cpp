//**********************************************************************************
//EncryptPad Copyright 2016 Evgeny Pokhilko 
//<http://www.evpo.net/encryptpad>
//
//This file is part of EncryptPad
//
//EncryptPad is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 2 of the License, or
//(at your option) any later version.
//
//EncryptPad is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with EncryptPad.  If not, see <http://www.gnu.org/licenses/>.
//**********************************************************************************
#include "set_key_dialog.h"
#include <QFileDialog>
#include "ui_set_key_dialog.h"
#include "os_api.h"
#include "file_name_helper.h"
#include "common_definitions.h"

SetKeyDialog::SetKeyDialog(QWidget *parent, FileRequestService &file_request_service) :
    QDialog(parent, kDefaultWindowFlags),
    ui(new Ui::SetKeyDialog),
    model_(nullptr),
    file_request_service_(file_request_service)
{
    ui->setupUi(this);
    auto size = sizeHint();
    size.setWidth(std::max(size.width(), minimumWidth()));
    size.setHeight(std::max(size.height(), minimumHeight()));
    setMinimumSize(size);
    adjustSize();
}

void SetKeyDialog::CurrentChanged(QModelIndex index, QModelIndex)
{
    if(!model_)
        return;
    ui->uiKeyFilePath->setText(model_->fileName(index));
}

SetKeyDialog::~SetKeyDialog()
{
    delete ui;
}

QString SetKeyDialog::GetKeyFilePath() const
{
    return ui->uiKeyFilePath->text();
}

bool SetKeyDialog::GetIsKeyPathPersistent() const
{
    return ui->uiPersistKeyLocation->checkState() == Qt::CheckState::Checked;
}

void SetKeyDialog::SetIsKeyPathPersistent(bool persistent)
{
    ui->uiPersistKeyLocation->setCheckState(persistent ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
}

void SetKeyDialog::SetKeyFilePath(const QString &path)
{
    ui->uiKeyFilePath->setText(path);
}

void SetKeyDialog::SetRepositoryListModel(QFileSystemModel &model, const QModelIndex &index)
{
    ui->uiRepositoryListView->setModel(&model);
    ui->uiRepositoryListView->setRootIndex(index);

    model_ = &model;
    connect(
                ui->uiRepositoryListView->selectionModel(),
                SIGNAL(currentChanged(QModelIndex,QModelIndex)),
                this,
                SLOT(CurrentChanged(QModelIndex, QModelIndex))
                );
}

void SetKeyDialog::on_uiFileDialog_clicked()
{
    QString fileName;
    fileName = ui->uiKeyFilePath->text();
    FileRequestSelection selection = file_request_service_.RequestExistingFile(
                this,
                tr("Specify encryption key location"),
                fileName,
                GetKeyDialogFilter());

    if(selection.cancelled)
        return;

    ui->uiKeyFilePath->setText(selection.file_name);
}
