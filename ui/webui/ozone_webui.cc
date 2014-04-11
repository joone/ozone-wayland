// Copyright (c) 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ozone/ui/webui/ozone_webui.h"

#include <set>

#include "base/command_line.h"
#include "base/debug/leak_annotations.h"
#include "base/environment.h"
#include "base/i18n/rtl.h"
#include "base/logging.h"
#include "base/nix/mime_util_xdg.h"
#include "base/stl_util.h"
#include "base/strings/stringprintf.h"
#include "ozone/ui/webui/select_file_dialog_impl_webui.h"

namespace views {

OzoneWebUI::OzoneWebUI() {
}

OzoneWebUI::~OzoneWebUI() {
}

void OzoneWebUI::Initialize() {
}

ui::SelectFileDialog* OzoneWebUI::CreateSelectFileDialog(
    ui::SelectFileDialog::Listener* listener,
    ui::SelectFilePolicy* policy) const {
  fprintf(stdout, "OzoneWebUI::%s\n", __func__);
  return ui::SelectFileDialogImplWebUI::Create(listener, policy);
}

}  // namespace views

views::LinuxUI* BuildWebUI() {
  return new views::OzoneWebUI;
}
