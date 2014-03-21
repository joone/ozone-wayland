// Copyright 2013 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef OZONE_CONTENT_OZONE_CHANNEL_H_
#define OZONE_CONTENT_OZONE_CHANNEL_H_

#include "base/strings/string16.h"
#include "ipc/ipc_listener.h"
#include "ozone/ui/events/window_constants.h"

namespace content {
class RemoteEventDispatcher;
// OzoneChannel is responsible for listening to any messages sent by it's
// host counterpart in BrowserProcess. There will be always only one
// OzoneChannel per browser instance.

class OzoneChannel : public IPC::Listener {
 public:
  OzoneChannel();
  virtual ~OzoneChannel();

  // IPC::Listener implementation.
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;

  void Register();
  void OnWidgetStateChanged(unsigned handleid,
                            ui::WidgetState state,
                            unsigned width,
                            unsigned height);
  void OnWidgetTitleChanged(unsigned widget, base::string16 title);
  void OnWidgetAttributesChanged(unsigned widget,
                                 unsigned parent,
                                 unsigned x,
                                 unsigned y,
                                 ui::WidgetType type);
  void OnWidgetImeReset();
  void OnWidgetShowInputPanel();
  void OnWidgetHideInputPanel();

 private:
  RemoteEventDispatcher* event_converter_;
  DISALLOW_COPY_AND_ASSIGN(OzoneChannel);
};

}  // namespace content

#endif  // OZONE_CONTENT_OZONE_CHANNEL_H_
