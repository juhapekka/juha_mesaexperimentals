#include "target-helpers/inline_debug_helper.h"
#include "state_tracker/drm_driver.h"
#include "intel/drm/intel_drm_public.h"
#include "ilo/ilo_public.h"

static struct pipe_screen *
create_screen(int fd)
{
   struct intel_winsys *iws;
   struct pipe_screen *screen;

   iws = intel_winsys_create_for_fd(fd);
   if (!iws)
      return NULL;

   screen = ilo_screen_create(iws);
   if (!screen)
      return NULL;

   screen = debug_screen_wrap(screen);

   return screen;
}

PUBLIC
DRM_DRIVER_DESCRIPTOR("i965", "i915", create_screen, NULL)
