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
#ifndef SET_ENCRYPTION_KEY_H
#define SET_ENCRYPTION_KEY_H

#include <QWidget>
#include <QString>
#include "file_request_service.h"

namespace EncryptPad
{
    struct EncryptionKeySelectionResult
    {
        QString key_file_path;
        bool persist_key_path;
    };

    bool SetEncryptionKey(QWidget *parent, const QString &key_file_path, bool persist_key_path,
                          FileRequestService &file_request_service, EncryptionKeySelectionResult &result_out);
}

#endif // SET_ENCRYPTION_KEY_H
