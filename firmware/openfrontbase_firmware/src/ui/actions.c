#include "actions.h"
#include "screens.h"

void action_to_all(lv_event_t *e) {
    LV_UNUSED(e);
    loadScreen(SCREEN_ID_ALL);
}