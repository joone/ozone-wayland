// Copyright (c) 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// This file implements select dialog functionality based on HTML.

#include "ozone/ui/webui/select_file_dialog_impl_webui.h"

#include <deque>
#include <string>

#include "base/environment.h"
#include "base/file_util.h"
#include "base/lazy_instance.h"
#include "base/nix/xdg_util.h"
#include "base/threading/thread_restrictions.h"
#include "chrome/browser/ui/browser_dialogs.h"
#include "ozone/ui/webui/file_picker_web_dialog.h"

namespace ui {

base::FilePath* SelectFileDialogImplWebUI::last_saved_path_ = NULL;
base::FilePath* SelectFileDialogImplWebUI::last_opened_path_ = NULL;

// static
ui::SelectFileDialog* SelectFileDialogImplWebUI::Create(
    SelectFileDialog::Listener* listener,
    SelectFilePolicy* policy) {
    fprintf(stdout, "SelectFileDialogImplWebUI::%s\n", __func__);
  return new SelectFileDialogImplWebUI(listener, policy);
}

SelectFileDialogImplWebUI::SelectFileDialogImplWebUI(Listener* listener,
                                           ui::SelectFilePolicy* policy)
    : SelectFileDialog(listener, policy),
      file_type_index_(0),
      type_(SELECT_NONE) {
  fprintf(stdout, "SelectFileDialogImplWebUI::%s\n", __func__);
  if (!last_saved_path_) {
    last_saved_path_ = new base::FilePath();
    last_opened_path_ = new base::FilePath();
  }
}

SelectFileDialogImplWebUI::~SelectFileDialogImplWebUI() { }

bool SelectFileDialogImplWebUI::HasMultipleFileTypeChoicesImpl() {
  NOTIMPLEMENTED();
  return false;
}

bool SelectFileDialogImplWebUI::IsRunning(gfx::NativeWindow parent_window)
    const {
  NOTIMPLEMENTED();
  return false;
}
void SelectFileDialogImplWebUI::ListenerDestroyed() {
  listener_ = NULL;
}

void SelectFileDialogImplWebUI::SelectFileImpl(
    SelectFileDialog::Type type,
    const base::string16& title,
    const base::FilePath& default_path,
    const SelectFileDialog::FileTypeInfo* file_types,
    int file_type_index,
    const std::string& default_extension,
    gfx::NativeWindow owning_window,
    void* params) {
  // We need to create a WebUI
  fprintf(stdout, "SelectFileDialogImplWebUI::%s\n", __func__);
  // web_contents is not required for creating a web dialog.
  content::WebContents* web_contents =
      static_cast<content::WebContents*>(params);
  FilePickerWebDialog::ShowDialog(owning_window);
}

bool SelectFileDialogImplWebUI::CallDirectoryExistsOnUIThread(
    const base::FilePath& path) {
  base::ThreadRestrictions::ScopedAllowIO allow_io;
  return base::DirectoryExists(path);
}

}  // namespace ui
