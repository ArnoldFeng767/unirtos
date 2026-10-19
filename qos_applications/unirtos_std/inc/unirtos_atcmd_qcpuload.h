/*****************************************************************/ /**
 * @file   unirtos_atcmd_qcpuload.h
 * @brief  AT+QCPULOAD command declaration
 * @author Nike.Bu@quectel.com
 * @date   2026-07-28
 *
 * @copyright  Copyright (c) 2023 Quectel Wireless Solution, Co., Ltd.
 * All Rights Reserved. Quectel Wireless Solution Proprietary and Confidential.
 *
 * @par EDIT HISTORY FOR MODULE
 * <table>
 * <tr><th>Date       <th>Version    <th>Author          <th>Description
 * <tr><td>2026-07-28 <td>1.0        <td>Nike.Bu         <td> Init
 * </table>
 *
 * @par AT Command Specification
 *
 * Syntax:
 *   AT+QCPULOAD=<period>  Start monitoring; <period> in ms, range 200~60000
 *   AT+QCPULOAD=0         Stop monitoring
 *   AT+QCPULOAD?          Query current state: +QCPULOAD: <state>,<last_pct>
 *   AT+QCPULOAD=?         Test command
 *
 * Periodic URC (auto-reported when monitoring is active):
 *   +QCPULOAD: <period>,<usage_pct>
 *
 **********************************************************************/
#ifndef __UNIRTOS_ATCMD_QCPULOAD_H__
#define __UNIRTOS_ATCMD_QCPULOAD_H__

#include "qosa_at_cmd.h"

void qstd_exec_qcpuload_cmd(qosa_at_cmd_t *cmd);
void unir_cpuload_at_init(void);

#endif /* __UNIRTOS_ATCMD_QCPULOAD_H__ */
