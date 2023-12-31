KEYBOARD_NAME = ergodox_ez
KEYMAP_NAME = king_tut
KEYMAP_DIR = keyboards/$(KEYBOARD_NAME)/keymaps/$(KEYMAP_NAME)

LTO_ENABLE = yes

DEFERRED_EXEC_ENABLE = yes

SWAP_HANDS_ENABLE= yes   # Allow swapping hands of keyboard
OS_DETECTION_ENABLE = no
CONSOLE_ENABLE = yes
NKRO_ENABLE = yes

MOUSEKEY_ENABLE  = no  # Mouse keys
MOUSE_SHARED_EP = no
EXTRAKEY_ENABLE = no

DYNAMIC_MACRO_ENABLE = yes
COMBO_ENABLE = yes
SWAP_HANDS_ENABLE = yes
TAP_DANCE_ENABLE = no

#LIBRARY
LIBRARY_DIR = $(KEYMAP_DIR)/lib
SRC += $(LIBRARY_DIR)/log.c

#FEATURES
FEATURE_DIR = $(KEYMAP_DIR)/features
include $(FEATURE_DIR)/features.mk
