# feature.mk
FEATURE_DIR = features
PROCESS_FEATURE_DIR = $(FEATURE_DIR)/process_features
LIBRARY_DIR = lib

#Override
LEADER_ENABLE = no

MOD_KEYS_ENABLE = yes
LEADER_HASH_ENABLE = yes
ALPHANUMERIC_HASH_ENABLE = no
RAW_ENABLE = yes
RAWHID_MOD_ENABLE = yes
COUNTER_KEYS_ENABLE = yes

SRC += $(FEATURE_DIR)/features.c

ifeq ($(LEADER_ENABLE), yes)
SRC += def/leader_end.c
endif

ifeq ($(MOD_KEYS_ENABLE),yes)
OPT_DEFS += -DMOD_KEYS_ENABLE
SRC += $(PROCESS_FEATURE_DIR)/process_mod_keys.c
SRC += def/mod_keys.c
endif

ifeq ($(LEADER_HASH_ENABLE),yes)
OPT_DEFS += -DLEADER_HASH_ENABLE
SRC += $(FEATURE_DIR)/leader_hash.c
SRC += $(PROCESS_FEATURE_DIR)/process_leader_hash.c
SRC += def/leader_hash_end.c
endif

ifeq ($(ALPHANUMERIC_HASH_ENABLE),yes)
OPT_DEFS += -DALPHANUMERIC_HASH_ENABLE
SRC += $(FEATURE_DIR)/alphanumeric_hash.c
SRC += $(PROCESS_FEATURE_DIR)/process_alphanumeric_hash.c
endif

ifeq ($(RAWHID_MOD_ENABLE),yes)
OPT_DEFS += -DRAWHID_MOD_ENABLE
SRC += $(FEATURE_DIR)/rawhid_mod.c
SRC += $(PROCESS_FEATURE_DIR)/process_rawhid_mod.c
endif

ifeq ($(COUNTER_KEYS_ENABLE),yes)
OPT_DEFS += -DCOUNTER_KEYS_ENABLE
SRC += $(FEATURE_DIR)/counter_keys.c
SRC += $(PROCESS_FEATURE_DIR)/process_counter_keys.c
SRC += $(LIBRARY_DIR)/keymap_ascii.c
endif
