#!/bin/bash
# Copyright (c) 2014 Intel Corporation. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.
#
# stolen from https://github.com/crosswalk-project/tizen-extensions-crosswalk

if [ ! `which cpplint.py` ]; then
   echo -en "\nPlease make sure cpplint.py is in your PATH. "
   echo -e "It is part of depot_tools inside Chromium repository."
   exit 1
fi

# Store current dir and change to repository root dir.
OLD_PWD=$PWD
SELF_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $SELF_DIR/..

# TODO(vignatti): maybe we should remove the OZONE_ prefix from all header
# guards and activate
FILTERS="+build,-build/header_guard,+whitespace,+readability,+legal,+runtime"

cpplint.py --filter="$FILTERS" $(find \
                               \( -name '*.h' -o -name '*.cc' \) | grep -v text-client-protocol.h  )

# Return to previous dir and return the code returned by cpplint.py
RET_VAL=$?
cd $OLD_PWD
exit $RET_VAL
