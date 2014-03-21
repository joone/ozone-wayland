// Copyright 2014 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ozone/ui/ime/input_method_context_impl_wayland.h"

#include "base/logging.h"
#include "ozone/ui/events/ime_state_change_handler.h"

namespace ui {

InputMethodContextImplWayland::InputMethodContextImplWayland(
    LinuxInputMethodContextDelegate* delegate)
    : delegate_(delegate) {
  CHECK(delegate_);
}

InputMethodContextImplWayland::~InputMethodContextImplWayland() {
}

////////////////////////////////////////////////////////////////////////////////
// InputMethodContextImplWayland, ui::LinuxInputMethodContext implementation:
bool InputMethodContextImplWayland::DispatchKeyEvent(
    const KeyEvent& key_event) {
  return false;
}

void InputMethodContextImplWayland::Reset() {
  IMEStateChangeHandler::GetInstance()->ResetIme();
}

void InputMethodContextImplWayland::OnTextInputTypeChanged(
    ui::TextInputType text_input_type) {

  // FIXME: We need to support more input types.
  if (text_input_type == ui::TEXT_INPUT_TYPE_NONE)
    IMEStateChangeHandler::GetInstance()->HideInputPanel();
  else
    IMEStateChangeHandler::GetInstance()->ShowInputPanel();
}

void InputMethodContextImplWayland::OnCaretBoundsChanged(
    const gfx::Rect& caret_bounds) {
  IMEStateChangeHandler::GetInstance()->ImeCaretBoundsChanged(caret_bounds);
}

}  // namespace ui
