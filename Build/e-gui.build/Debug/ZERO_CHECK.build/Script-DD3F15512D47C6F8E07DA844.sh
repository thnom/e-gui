#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/thnom/Projects/e-gui/e-gui/Build
  make -f /Users/thnom/Projects/e-gui/e-gui/Build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/thnom/Projects/e-gui/e-gui/Build
  make -f /Users/thnom/Projects/e-gui/e-gui/Build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/thnom/Projects/e-gui/e-gui/Build
  make -f /Users/thnom/Projects/e-gui/e-gui/Build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/thnom/Projects/e-gui/e-gui/Build
  make -f /Users/thnom/Projects/e-gui/e-gui/Build/CMakeScripts/ReRunCMake.make
fi

