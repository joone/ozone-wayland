// Copyright (c) 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_OZONE_WEB_UI_H_
#define CHROME_BROWSER_UI_OZONE_WEB_UI_H_

#include <map>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/observer_list.h"
#include "ui/base/ime/linux/linux_input_method_context.h"
#include "ui/events/linux/text_edit_key_bindings_delegate_auralinux.h"
#include "ui/gfx/color_utils.h"
#include "ui/gfx/geometry/insets.h"
#include "ui/gfx/image/image.h"
#include "ui/views/border.h"
#include "ui/views/linux_ui/linux_ui.h"
#include "ui/views/window/frame_buttons.h"


class SkBitmap;

namespace gfx {
class Image;
}
using ui::TextEditCommandAuraLinux;

namespace views {
class Border;
class LabelButton;
class View;
class NativeThemeChangeObserver;
class WindowButtonOrderObserver;
// Interface to Wayland desktop features.
//
class OzoneWebUI : public views::LinuxUI {
 public:
  OzoneWebUI();
  virtual ~OzoneWebUI();

  // ui::LinuxInputMethodContextFactory:
  virtual scoped_ptr<ui::LinuxInputMethodContext> CreateInputMethodContext(
      ui::LinuxInputMethodContextDelegate* delegate) const OVERRIDE
      {return scoped_ptr<ui::LinuxInputMethodContext>();}

  // gfx::LinuxFontDelegate:
  virtual bool UseAntialiasing() const OVERRIDE { return false;}
  virtual gfx::FontRenderParams::Hinting GetHintingStyle() const OVERRIDE {
      gfx::FontRenderParams::Hinting hinting =
        gfx::FontRenderParams::HINTING_SLIGHT;
      return hinting;}
  virtual gfx::FontRenderParams::SubpixelRendering
      GetSubpixelRenderingStyle() const OVERRIDE {
      gfx::FontRenderParams::SubpixelRendering subpixel_rendering =
            gfx::FontRenderParams::SUBPIXEL_RENDERING_NONE;
            return subpixel_rendering;
      }

  virtual std::string GetDefaultFontName() const OVERRIDE {
      std::string font_name = "sans 10";
      return font_name; }

  // ui::LinuxShellDialog:
  virtual ui::SelectFileDialog* CreateSelectFileDialog(
      ui::SelectFileDialog::Listener* listener,
      ui::SelectFilePolicy* policy) const OVERRIDE;

  // ui::LinuxUI:
  virtual void Initialize() OVERRIDE;

  // These methods are not needed
  virtual gfx::Image GetThemeImageNamed(int id) const { return gfx::Image();}
  virtual bool GetColor(int id, SkColor* color) const  { return false;}
  virtual bool HasCustomImage(int id) const  {return false;}

  virtual SkColor GetFocusRingColor() const { return SK_ColorBLACK;}
  virtual SkColor GetThumbActiveColor() const {return SK_ColorBLACK;}
  virtual SkColor GetThumbInactiveColor() const {return SK_ColorBLACK;}
  virtual SkColor GetTrackColor() const {return SK_ColorBLACK;}
  virtual SkColor GetActiveSelectionBgColor() const {return SK_ColorBLACK;}
  virtual SkColor GetActiveSelectionFgColor() const {return SK_ColorBLACK;}
  virtual SkColor GetInactiveSelectionBgColor() const {return SK_ColorBLACK;}
  virtual SkColor GetInactiveSelectionFgColor() const {return SK_ColorBLACK;}
  virtual double GetCursorBlinkInterval() const { return 1.0;}

  // Returns a NativeTheme that will provide system colors and draw system
  // style widgets.
  //virtual ui::NativeTheme* GetNativeTheme() const OVERRIDE { return 0;}
  virtual ui::NativeTheme* GetNativeTheme(aura::Window* window) const { return 0;}

  // Used to set an override NativeTheme.
  virtual void SetNativeThemeOverride(const NativeThemeGetter& callback) 
     { return; }

  // Returns whether we should be using the native theme provided by this
  // object by default.
  virtual bool GetDefaultUsesSystemTheme() const { return false;}

  // Sets visual properties in the desktop environment related to download
  // progress, if available.
  virtual void SetDownloadCount(int count) const {}
  virtual void SetProgressFraction(float percentage) const {}

  // Checks for platform support for status icons.
  virtual bool IsStatusIconSupported() const {return false;}

  // Create a native status icon.
  virtual scoped_ptr<StatusIconLinux> CreateLinuxStatusIcon(
      const gfx::ImageSkia& image,
      const base::string16& tool_tip) const {
        return scoped_ptr<views::StatusIconLinux>();}

  // Returns the icon for a given content type from the icon theme.
  // TODO(davidben): Add an observer for the theme changing, so we can drop the
  // caches.
  virtual gfx::Image GetIconForContentType(
      const std::string& content_type, int size) const { return gfx::Image();}

  // Builds a Border which paints the native button style.
  virtual scoped_ptr<Border> CreateNativeBorder(
      views::LabelButton* owning_button,
      scoped_ptr<views::Border> border) { return scoped_ptr<views::Border>(
        border.Pass());}

  // Notifies the observer about changes about how window buttons should be
  // laid out. If the order is anything other than the default min,max,close on
  // the right, will immediately send a button change event to the observer.
  virtual void AddWindowButtonOrderObserver(
      WindowButtonOrderObserver* observer) {}

  // Removes the observer from the LinuxUI's list.
  virtual void RemoveWindowButtonOrderObserver(
      WindowButtonOrderObserver* observer) {}

/*  // Notifies the observer when the native theme changes.
  virtual void AddNativeThemeChangeObserver(
      NativeThemeChangeObserver* observer) {}
  virtual void RemoveNativeThemeChangeObserver(
      NativeThemeChangeObserver* observer) {}
*/

  // Determines whether the user's window manager is Unity.
  virtual bool UnityIsRunning() { return 0;}

  // What action we should take when the user middle clicks on non-client
  // area. The default is lowering the window.
  virtual NonClientMiddleClickAction GetNonClientMiddleClickAction() { 
     return MIDDLE_CLICK_ACTION_NONE; }

  virtual void NotifyWindowManagerStartupComplete() {}

  virtual bool MatchEvent(const ui::Event& event,
                           std::vector<TextEditCommandAuraLinux>* commands) 
      { return false; }

 private:
  DISALLOW_COPY_AND_ASSIGN(OzoneWebUI);
};

}  // namespace views


// WebUI.
views::LinuxUI* BuildWebUI();

#endif  // CHROME_BROWSER_UI_OZONE_WEB_UI_H_
