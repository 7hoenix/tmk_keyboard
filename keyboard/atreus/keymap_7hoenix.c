#include "keymap_common.h"
#include "light_ws2812.h"

/* The default Atreus layout. First layer is normal keys, second
   (momentary fn layer) is numbers, most punctuation, and
   arrows. Third (modal, persistent) layer is function keys and other
   rarely-used keys. */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* 0: mostly letters */
  KEYMAP(KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, \
         KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, \
         KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, \
         KC_ESC, KC_TAB, KC_LALT, KC_LSFT, KC_BSPC, KC_LCTL, KC_LGUI,     \
         KC_SPC, KC_FN0, KC_MINS, KC_QUOT, KC_ENT),                     \
    // KC_LGUI

  /* 1: punctuation and numbers */
    KEYMAP(SHIFT(KC_1), SHIFT(KC_2), KC_UP, SHIFT(KC_LBRC), SHIFT(KC_RBRC), \
        KC_PGUP, KC_7, KC_8, KC_9, SHIFT(KC_8), \
        SHIFT(KC_3), KC_LEFT, KC_DOWN, KC_RIGHT, SHIFT(KC_4), \
        KC_PGDN, KC_4, KC_5, KC_6, SHIFT(KC_EQUAL), \
        KC_LBRC, KC_RBRC, SHIFT(KC_9), SHIFT(KC_0), SHIFT(KC_7), \
        KC_GRAVE, KC_1, KC_2, KC_3, KC_BSLS,    \
        KC_FN1, SHIFT(KC_INS), KC_LALT, KC_LSFT, KC_BSPC, KC_LCTL, \
        KC_LGUI, KC_SPC, KC_FN0, KC_DOT, KC_0, KC_EQUAL), \

  /* 2: arrows and function keys */
    KEYMAP(KC_INS, KC_HOME, KC_UP, KC_END, KC_PGUP,             KC_UP, KC_F7, KC_F8, KC_F9, KC_F10, \
        KC_DEL, KC_LEFT, KC_DOWN, KC_RIGHT, KC_PGDN,            KC_DOWN, KC_F4, KC_F5, KC_F6, KC_F11,          \
        KC_FN23, KC__VOLUP, KC_NO, KC_NO, KC_FN3,                KC_NO, KC_F1, KC_F2, KC_F3, KC_F12,            \
        KC_FN22, KC__VOLDOWN, KC_LALT, KC_LSFT, KC_BSPC, KC_LCTL, KC_LGUI, KC_SPC, KC_FN2, KC_PSCREEN, KC_SLCK, KC_PAUSE), \
        /* KC_FN4, KC__VOLUP, KC_NO, KC_NO, KC_FN3,                KC_NO, KC_F1, KC_F2, KC_F3, KC_F12,            \ */
        /* KC_NO, KC__VOLDOWN, KC_LALT, KC_LSFT, KC_BSPC, KC_LCTL, KC_LGUI, KC_SPC, KC_FN2, KC_PSCREEN, KC_SLCK, KC_PAUSE), \ */

  /* 3: mouse control, reached by fn+esc, then holding z*/
  KEYMAP(
         //       left    up/down  right                              mouse wheel: left up/down right
         KC_NO,   KC_NO,   KC_FN6,  KC_NO,   KC_NO,                   KC_NO,   KC_NO,   KC_FN10, KC_NO,   KC_NO,   \
         KC_NO,   KC_FN8,  KC_FN7,  KC_FN9,  KC_NO,                   KC_NO,   KC_FN12, KC_FN11, KC_FN13, KC_NO,   \
         //       acceleration settings                               buttons:    left   middle   right
         KC_NO,   KC_FN19, KC_FN20, KC_FN21, KC_NO,                   KC_FN17,   KC_FN14, KC_FN16, KC_FN15, KC_FN18, \
         KC_TRNS, KC_NO,   KC_TRNS, KC_TRNS, KC_NO, KC_TRNS, KC_TRNS, KC_NO,     KC_FN5,  KC_NO,   KC_NO,   KC_NO  \
          )
};

const uint16_t PROGMEM fn_actions[] = {
  [0] = ACTION_LAYER_MOMENTARY(1),  // to Fn overlay
  [1] = ACTION_LAYER_ON(2, 1),  // switch to layer 2
  [2] = ACTION_LAYER_OFF(2, 1),  // switch back to layer 0
  [3] = ACTION_FUNCTION(BOOTLOADER),
  [4] = ACTION_LAYER_ON(3, 1),  // switch to layer 3
  [5] = ACTION_LAYER_OFF(3, 1),  // switch back to layer 2

  [6] = ACTION_MOUSEKEY(KC_MS_U), // mouse movement
  [7] = ACTION_MOUSEKEY(KC_MS_D),
  [8] = ACTION_MOUSEKEY(KC_MS_L),
  [9] = ACTION_MOUSEKEY(KC_MS_R),
  [10] = ACTION_MOUSEKEY(KC_WH_U), // wheel
  [11] = ACTION_MOUSEKEY(KC_WH_D),
  [12] = ACTION_MOUSEKEY(KC_WH_L),
  [13] = ACTION_MOUSEKEY(KC_WH_R),
  [14] = ACTION_MOUSEKEY(KC_BTN1), // clicks
  [15] = ACTION_MOUSEKEY(KC_BTN2),
  [16] = ACTION_MOUSEKEY(KC_BTN3),
  [17] = ACTION_MOUSEKEY(KC_BTN4),
  [18] = ACTION_MOUSEKEY(KC_BTN5),
  [19] = ACTION_MOUSEKEY(KC_ACL0), // acceleration settings
  [20] = ACTION_MOUSEKEY(KC_ACL1),
  [21] = ACTION_MOUSEKEY(KC_ACL2),
  [22] = ACTION_FUNCTION(LED_WHITE), // led controls
  [23] = ACTION_FUNCTION(LED_OFF)
};

struct cRGB led[3];

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
      case BOOTLOADER:
          bootloader();
          break;

      case LED_OFF:
          led[0].r=00;led[0].g=00;led[0].b=00;   // LED 0 is red
          led[1].r=00;led[1].g=00;led[1].b=00;   // LED 1 is White
          led[2].r=00;led[2].g=00;led[2].b=00;   // LED 2 is White
          ws2812_setleds(led, 3);
          break;

      case LED_WHITE:
          led[0].r=16;led[0].g=16;led[0].b=16;   // LED 0 is red
          led[1].r=16;led[1].g=16;led[1].b=16;   // LED 1 is White
          led[2].r=16;led[2].g=16;led[2].b=16;   // LED 2 is White
          ws2812_setleds(led, 3);
          break;
  }
}
