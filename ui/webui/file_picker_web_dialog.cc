// Copyright (c) 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ozone/ui/webui/file_picker_web_dialog.h"

#include "chrome/browser/profiles/profile_manager.h"
#include "chrome/browser/ui/browser_dialogs.h"
#include "chrome/common/url_constants.h"
#include "chrome/grit/browser_resources.h"
#include "chrome/grit/chromium_strings.h"
#include "chrome/grit/generated_resources.h"
#include "content/public/browser/web_ui.h"
#include "content/public/browser/web_ui_message_handler.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/gfx/size.h"

using content::WebContents;
using content::WebUIMessageHandler;

namespace {

// Default width/height of the dialog.
const int kDefaultWidth = 350;
const int kDefaultHeight = 225;
}

namespace ui {

// FilePickerMessageHandler --------------------------------------------
class FilePickerMessageHandler : public content::WebUIMessageHandler {
 public:
  FilePickerMessageHandler(
      const ui::FilePickerWebDialog* dialog);
  virtual ~FilePickerMessageHandler();
  virtual void RegisterMessages() OVERRIDE;

 private:
  // content::WebUIMessageHandler implementation.
  void OnCancelButtonClicked(const base::ListValue* args);
  void OnCreateProfileClicked(const base::ListValue* args);
  void OnContinueButtonClicked(const base::ListValue* args);

  // Weak ptr to parent dialog.
  const ui::FilePickerWebDialog* dialog_;

  // Dialog button handling.
  // ui::ProfileSigninConfirmationDelegate* delegate_;
};

FilePickerMessageHandler::FilePickerMessageHandler(
    const ui::FilePickerWebDialog* dialog)
  : dialog_(dialog) {
  fprintf(stdout, "FilePickerMessageHandle::%s\n", __func__);
}

FilePickerMessageHandler::~FilePickerMessageHandler() {
}

void FilePickerMessageHandler::RegisterMessages() {
  fprintf(stdout, "FilePickerMessageHandle::%s\n", __func__);
  web_ui()->RegisterMessageCallback(
      "cancel",
      base::Bind(&FilePickerMessageHandler::OnCancelButtonClicked,
                 base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "createNewProfile",
      base::Bind(&FilePickerMessageHandler::OnCreateProfileClicked,
                 base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "continue",
      base::Bind(&FilePickerMessageHandler::OnContinueButtonClicked,
                 base::Unretained(this)));
}

void FilePickerMessageHandler::OnCancelButtonClicked(
    const base::ListValue* args) {
  fprintf(stdout, "FilePickerMessageHandle::%s\n", __func__);
  dialog_->Close();
}

void FilePickerMessageHandler::OnCreateProfileClicked(
    const base::ListValue* args) {
  fprintf(stdout, "FilePickerMessageHandle::%s\n", __func__);
  dialog_->Close();
}

void FilePickerMessageHandler::OnContinueButtonClicked(
    const base::ListValue* args) {
  dialog_->Close();
}

}  // namespace ui

namespace ui {

// static
void FilePickerWebDialog::ShowDialog(gfx::NativeWindow owning_window) {
  chrome::ShowWebDialog(owning_window,
                        ProfileManager::GetActiveUserProfile(),
                        new FilePickerWebDialog);
}

void FilePickerWebDialog::Close() const {
  fprintf(stdout, "FilePickerWebDialog::%s\n", __func__);
}

FilePickerWebDialog::FilePickerWebDialog() {
}

ui::ModalType FilePickerWebDialog::GetDialogModalType() const {
  return ui::MODAL_TYPE_SYSTEM;
}

base::string16 FilePickerWebDialog::GetDialogTitle() const {
  return l10n_util::GetStringUTF16(IDS_FILE_PICKER_TITLE);
}

GURL FilePickerWebDialog::GetDialogContentURL() const {
  return GURL(chrome::kChromeUIFilePickerURL);
}

void FilePickerWebDialog::GetWebUIMessageHandlers(
    std::vector<content::WebUIMessageHandler*>* handlers) const {
  handlers->push_back(new FilePickerMessageHandler(this));
}

void FilePickerWebDialog::GetDialogSize(gfx::Size* size) const {
  size->SetSize(kDefaultWidth, kDefaultHeight);
}

std::string FilePickerWebDialog::GetDialogArgs() const {
  return "[]";
}

void FilePickerWebDialog::OnDialogClosed(const std::string& json_retval) {
  delete this;
  fprintf(stdout, "FilePickerWebDialog::%s\n", __func__);
}

void FilePickerWebDialog::OnCloseContents(WebContents* source,
                                                bool* out_close_dialog) {
  if (out_close_dialog)
    *out_close_dialog = true;
}

bool FilePickerWebDialog::ShouldShowDialogTitle() const {
  return true;
}

bool FilePickerWebDialog::HandleContextMenu(
    const content::ContextMenuParams& params) {
  // Disable context menu.
  return true;
}

}  // namespace ui
