// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ozone/ui/webui/file_picker_ui.h"

#include "base/values.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/common/url_constants.h"
#include "chrome/grit/browser_resources.h"
#include "chrome/grit/chromium_strings.h"
#include "chrome/grit/generated_resources.h"
#include "content/public/browser/web_contents.h"
#include "content/public/browser/web_ui.h"
#include "content/public/browser/web_ui_data_source.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/base/resource/resource_bundle.h"

namespace ui {
FilePickerUI::FilePickerUI(content::WebUI* web_ui)
  : ConstrainedWebDialogUI(web_ui) {
  content::WebUIDataSource* html_source = content::WebUIDataSource::Create(
      chrome::kChromeUIFilePickerHost);
  html_source->SetUseJsonJSFormatV2();

  html_source->AddLocalizedString(
       "filePickerFileNameLabel",
       IDS_FILE_PICKER_FILE_NAME);

  html_source->AddLocalizedString("saveFileButtonText", IDS_SAVE);
  html_source->AddLocalizedString(
       "cancelButtonText", IDS_CANCEL);

  html_source->SetJsonPath("strings.js");

  html_source->AddResourcePath("file_picker.js", IDR_FILE_PICKER_JS);
  html_source->AddResourcePath("file_picker.css", IDR_FILE_PICKER_CSS);
  html_source->SetDefaultResource(IDR_FILE_PICKER_HTML);

  Profile* profile = Profile::FromWebUI(web_ui);
  content::WebUIDataSource::Add(profile, html_source);
}

FilePickerUI::~FilePickerUI() {
}

}  // namespace ui
