/*
 * Copyright 2020 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <stdint.h>
#include "stack/include/acl_api_types.h"
#include "stack/include/bt_types.h"
#include "types/raw_address.h"

#define BTM_MAX_SCN_ 31  // PORT_MAX_RFC_PORTS system/bt/stack/include/rfcdefs.h

/* Define the ACL Management control structure
 */
typedef struct {
  uint16_t hci_handle;
  uint16_t pkt_types_mask;
  uint16_t clock_offset;
  RawAddress remote_addr;
  DEV_CLASS remote_dc;
  BD_NAME remote_name;

  uint16_t manufacturer;
  uint16_t lmp_subversion;
  uint16_t link_super_tout;
  BD_FEATURES
  peer_lmp_feature_pages[HCI_EXT_FEATURES_PAGE_MAX + 1]; /* Peer LMP Extended
                                                            features mask table
                                                            for the device */
  uint8_t num_read_pages;
  uint8_t lmp_version;

  bool in_use;
  uint8_t link_role;
  bool link_up_issued; /* True if busy_level link up has been issued */

#define BTM_ACL_SWKEY_STATE_IDLE 0
#define BTM_ACL_SWKEY_STATE_MODE_CHANGE 1
#define BTM_ACL_SWKEY_STATE_ENCRYPTION_OFF 2
#define BTM_ACL_SWKEY_STATE_SWITCHING 3
#define BTM_ACL_SWKEY_STATE_ENCRYPTION_ON 4
#define BTM_ACL_SWKEY_STATE_IN_PROGRESS 5
  uint8_t switch_role_state;

#define BTM_MAX_SW_ROLE_FAILED_ATTEMPTS 3
  uint8_t switch_role_failed_attempts;

#define BTM_ACL_ENCRYPT_STATE_IDLE 0
#define BTM_ACL_ENCRYPT_STATE_ENCRYPT_OFF 1 /* encryption turning off */
#define BTM_ACL_ENCRYPT_STATE_TEMP_FUNC \
  2 /* temporarily off for change link key or role switch */
#define BTM_ACL_ENCRYPT_STATE_ENCRYPT_ON 3 /* encryption turning on */
  uint8_t encrypt_state;                   /* overall BTM encryption state */

  tBT_TRANSPORT transport;
  RawAddress conn_addr;   /* local device address used for this connection */
  uint8_t conn_addr_type; /* local device address type for this connection */
  RawAddress active_remote_addr;   /* remote address used on this connection */
  uint8_t active_remote_addr_type; /* local device address type for this
                                      connection */
  BD_FEATURES peer_le_features; /* Peer LE Used features mask for the device */

} tACL_CONN;

typedef struct {
  /****************************************************
   **      ACL Management
   ****************************************************/
  tACL_CONN acl_db[MAX_L2CAP_LINKS];
  uint8_t btm_scn[BTM_MAX_SCN_]; /* current SCNs: true if SCN is in use */
  uint16_t btm_def_link_policy;
  uint16_t btm_def_link_super_tout;

  tBTM_BL_EVENT_MASK bl_evt_mask;
  tBTM_BL_CHANGE_CB* p_bl_changed_cb; /* Callback for when Busy Level changed */

  uint8_t pm_pend_link; /* the index of acl_db, which has a pending PM cmd */

  /* Packet types supported by the local device */
  uint16_t btm_acl_pkt_types_supported;

  uint8_t acl_disc_reason;
} tACL_CB;  // NEW
