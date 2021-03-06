/*! \file rm_hash_main.c
 *
 * Resource Manager for Hash Table
 *
 * This file contains the resource manager for physical hash tables
 */
/*
 * Copyright: (c) 2018 Broadcom. All Rights Reserved. "Broadcom" refers to 
 * Broadcom Limited and/or its subsidiaries.
 * 
 * Broadcom Switch Software License
 * 
 * This license governs the use of the accompanying Broadcom software. Your 
 * use of the software indicates your acceptance of the terms and conditions 
 * of this license. If you do not agree to the terms and conditions of this 
 * license, do not use the software.
 * 1. Definitions
 *    "Licensor" means any person or entity that distributes its Work.
 *    "Software" means the original work of authorship made available under 
 *    this license.
 *    "Work" means the Software and any additions to or derivative works of 
 *    the Software that are made available under this license.
 *    The terms "reproduce," "reproduction," "derivative works," and 
 *    "distribution" have the meaning as provided under U.S. copyright law.
 *    Works, including the Software, are "made available" under this license 
 *    by including in or with the Work either (a) a copyright notice 
 *    referencing the applicability of this license to the Work, or (b) a copy 
 *    of this license.
 * 2. Grant of Copyright License
 *    Subject to the terms and conditions of this license, each Licensor 
 *    grants to you a perpetual, worldwide, non-exclusive, and royalty-free 
 *    copyright license to reproduce, prepare derivative works of, publicly 
 *    display, publicly perform, sublicense and distribute its Work and any 
 *    resulting derivative works in any form.
 * 3. Grant of Patent License
 *    Subject to the terms and conditions of this license, each Licensor 
 *    grants to you a perpetual, worldwide, non-exclusive, and royalty-free 
 *    patent license to make, have made, use, offer to sell, sell, import, and 
 *    otherwise transfer its Work, in whole or in part. This patent license 
 *    applies only to the patent claims licensable by Licensor that would be 
 *    infringed by Licensor's Work (or portion thereof) individually and 
 *    excluding any combinations with any other materials or technology.
 *    If you institute patent litigation against any Licensor (including a 
 *    cross-claim or counterclaim in a lawsuit) to enforce any patents that 
 *    you allege are infringed by any Work, then your patent license from such 
 *    Licensor to the Work shall terminate as of the date such litigation is 
 *    filed.
 * 4. Redistribution
 *    You may reproduce or distribute the Work only if (a) you do so under 
 *    this License, (b) you include a complete copy of this License with your 
 *    distribution, and (c) you retain without modification any copyright, 
 *    patent, trademark, or attribution notices that are present in the Work.
 * 5. Derivative Works
 *    You may specify that additional or different terms apply to the use, 
 *    reproduction, and distribution of your derivative works of the Work 
 *    ("Your Terms") only if (a) Your Terms provide that the limitations of 
 *    Section 7 apply to your derivative works, and (b) you identify the 
 *    specific derivative works that are subject to Your Terms. 
 *    Notwithstanding Your Terms, this license (including the redistribution 
 *    requirements in Section 4) will continue to apply to the Work itself.
 * 6. Trademarks
 *    This license does not grant any rights to use any Licensor's or its 
 *    affiliates' names, logos, or trademarks, except as necessary to 
 *    reproduce the notices described in this license.
 * 7. Limitations
 *    Platform. The Work and any derivative works thereof may only be used, or 
 *    intended for use, with a Broadcom switch integrated circuit.
 *    No Reverse Engineering. You will not use the Work to disassemble, 
 *    reverse engineer, decompile, or attempt to ascertain the underlying 
 *    technology of a Broadcom switch integrated circuit.
 * 8. Termination
 *    If you violate any term of this license, then your rights under this 
 *    license (including the license grants of Sections 2 and 3) will 
 *    terminate immediately.
 * 9. Disclaimer of Warranty
 *    THE WORK IS PROVIDED "AS IS" WITHOUT WARRANTIES OR CONDITIONS OF ANY 
 *    KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WARRANTIES OR CONDITIONS OF 
 *    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE OR 
 *    NON-INFRINGEMENT. YOU BEAR THE RISK OF UNDERTAKING ANY ACTIVITIES UNDER 
 *    THIS LICENSE. SOME STATES' CONSUMER LAWS DO NOT ALLOW EXCLUSION OF AN 
 *    IMPLIED WARRANTY, SO THIS DISCLAIMER MAY NOT APPLY TO YOU.
 * 10. Limitation of Liability
 *    EXCEPT AS PROHIBITED BY APPLICABLE LAW, IN NO EVENT AND UNDER NO LEGAL 
 *    THEORY, WHETHER IN TORT (INCLUDING NEGLIGENCE), CONTRACT, OR OTHERWISE 
 *    SHALL ANY LICENSOR BE LIABLE TO YOU FOR DAMAGES, INCLUDING ANY DIRECT, 
 *    INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT OF 
 *    OR RELATED TO THIS LICENSE, THE USE OR INABILITY TO USE THE WORK 
 *    (INCLUDING BUT NOT LIMITED TO LOSS OF GOODWILL, BUSINESS INTERRUPTION, 
 *    LOST PROFITS OR DATA, COMPUTER FAILURE OR MALFUNCTION, OR ANY OTHER 
 *    COMMERCIAL DAMAGES OR LOSSES), EVEN IF THE LICENSOR HAS BEEN ADVISED OF 
 *    THE POSSIBILITY OF SUCH DAMAGES.
 */

/*******************************************************************************
 * Includes
 */
#include <bsl/bsl.h>
#include <sal/sal_types.h>
#include <sal/sal_libc.h>
#include <shr/shr_error.h>
#include <shr/shr_debug.h>
#include <bcmdrd/bcmdrd_field.h>
#include <bcmptm/bcmptm_rm_hash_internal.h>
#include "rm_hash_internal.h"
#include "rm_hash_device.h"

/*******************************************************************************
 * Defines
 */
#define BSL_LOG_MODULE BSL_LS_BCMPTM_RMHASH

/*******************************************************************************
 * Typedefs
 */


/*******************************************************************************
 * Private variables
 */


/*******************************************************************************
 * Public Functions
 */


/*
 * bcmptm_rm_hash_init
 *
 * Init resource manager for hash table
 */
int
bcmptm_rm_hash_init(int unit)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_EXIT(bcmptm_rm_hash_device_init(unit));
    SHR_IF_ERR_EXIT(bcmptm_rm_hash_ent_move_info_init(unit));

exit:
    SHR_FUNC_EXIT();
}

/*
 * bcmptm_rm_hash_cleanup
 *
 * Clean up resource manager for hash table
 */
int
bcmptm_rm_hash_cleanup(int unit)
{
    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_EXIT(bcmptm_rm_hash_lt_ctrl_cleanup(unit));
    SHR_IF_ERR_EXIT(bcmptm_rm_hash_ent_move_info_cleanup(unit));
    SHR_IF_ERR_EXIT(bcmptm_rm_hash_state_elems_cleanup(unit));
    SHR_IF_ERR_EXIT(bcmptm_rm_hash_pt_reg_info_cleanup(unit));
    SHR_IF_ERR_EXIT(bcmptm_rm_hash_device_cleanup(unit));

exit:
    SHR_FUNC_EXIT();
}

int
bcmptm_rm_hash_trans_cmd(int unit,
                         uint32_t flags,
                         uint32_t cseq_id,
                         bcmptm_trans_cmd_t trans_cmd)
{
    rm_hash_trans_record_t *trans_rec = NULL;
    rm_hash_trans_undo_list_t *trans_ulist = NULL;

    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_EXIT
        (bcmptm_rm_hash_trans_record_get(unit, &trans_rec));
    if (!trans_rec) {
        LOG_WARN(BSL_LOG_MODULE,
                 (BSL_META_U(unit, "Hash rsrc_mgr got NULL trans_rec \n")));
        SHR_RETURN_VAL_EXIT(SHR_E_NONE); 
    }
    SHR_IF_ERR_EXIT
        (bcmptm_rm_hash_trans_undo_list_get(unit, &trans_ulist));
    switch (trans_cmd) {
        case BCMPTM_TRANS_CMD_COMMIT:
            LOG_VERBOSE(BSL_LOG_MODULE,
                        (BSL_META_U(unit, "Hash rsrc_mgr got Commit \n")));
            if (trans_rec->trans_state == BCMPTM_RM_HASH_STATE_IDLE) {
                /*
                 * If transaction state is in IDLE and rm receives commit command,
                 * it stays in IDLE state and ignores cseq_id.
                 */
                 SHR_RETURN_VAL_EXIT(SHR_E_NONE);
            } else if ((trans_rec->trans_state == BCMPTM_RM_HASH_STATE_UC_A) ||
                       (trans_rec->trans_state == BCMPTM_RM_HASH_STATE_INVALIDATING_U)) {
                /*
                 * If transaction state is in UC_A and it receives commit command,
                 * it checks if the cseq_id is expected or not. If yes, it commits
                 * the changes to sw_state and goes to IDLE.
                 */
                if (cseq_id == trans_rec->cseq_id) {
                    trans_rec->trans_state = BCMPTM_RM_HASH_STATE_INVALIDATING_U;
                    SHR_IF_ERR_EXIT
                        (bcmptm_rm_hash_trans_undo_list_invalidate(unit,
                                                                   trans_ulist));
                    trans_rec->trans_state = BCMPTM_RM_HASH_STATE_IDLE;
                } else {
                    /* If the cseq_id is not expected, then ignore the commit */
                    SHR_RETURN_VAL_EXIT(SHR_E_NONE);
                }
            } else {
                SHR_RETURN_VAL_EXIT(SHR_E_INTERNAL);
            }
            break;
        case BCMPTM_TRANS_CMD_ABORT:
            LOG_VERBOSE(BSL_LOG_MODULE,
                        (BSL_META_U(unit, "Hash rsrc_mgr got Abort \n")));
            if (trans_rec->trans_state == BCMPTM_RM_HASH_STATE_IDLE) {
                /*
                 * If transaction state is in IDLE and rm receives abort command,
                 * it stays in IDLE state and ignores cseq_id.
                 */
                 SHR_RETURN_VAL_EXIT(SHR_E_NONE);
            } else if ((trans_rec->trans_state == BCMPTM_RM_HASH_STATE_UC_A) ||
                       (trans_rec->trans_state == BCMPTM_RM_HASH_STATE_RESTORING_U)) {
                /*
                 * If transaction state is in UC_A and rm receives abort command,
                 * it checks if the cseq_id is expected or not. If not, declare
                 * SHR_E_FAIL. If yes, execute the operations in the undo list.
                 */
                if (cseq_id == trans_rec->cseq_id) {
                    trans_rec->trans_state = BCMPTM_RM_HASH_STATE_RESTORING_U;
                    SHR_IF_ERR_EXIT
                        (bcmptm_rm_hash_trans_undo_list_restore(unit,
                                                                trans_ulist));
                    trans_rec->trans_state = BCMPTM_RM_HASH_STATE_IDLE;
                } else {
                    SHR_RETURN_VAL_EXIT(SHR_E_FAIL);
                }
            }
            break;
        case BCMPTM_TRANS_CMD_IDLE_CHECK:
            LOG_VERBOSE(BSL_LOG_MODULE,
                        (BSL_META_U(unit, "Hash rsrc_mgr got Idle_Check \n")));
            if (trans_rec->trans_state == BCMPTM_RM_HASH_STATE_IDLE) {
                SHR_RETURN_VAL_EXIT(SHR_E_NONE);
            } else {
                SHR_RETURN_VAL_EXIT(SHR_E_FAIL);
            }
            break;
        default:
            LOG_ERROR(BSL_LOG_MODULE,
                     (BSL_META_U(unit, "Hash rsrc_mgr got Unknown trans_cmd \n")));
            SHR_RETURN_VAL_EXIT(SHR_E_INTERNAL);
            break;
    }

    /* Rsrc_mgr starts in IDLE state.
     * In IDLE state, ptrm_state_cseq_id is dont_care.
     * - if it gets commit()
     *          it stays in IDLE state. Ignores cseq_id.
     *
     * - if it gets abort()
     *          stays in IDLE state. Ignores cseq_id.
     *
     * - if it gets bcmptm_rm_hash_req()
     *          goes into CHANGED state and
     *          remembers cseq_id as ptrm_state_cseq_id
     *
     * - if it gets idle_check:
     *          stays in IDLE state and returns SHR_E_NONE.
     *          cseq_id should be ignored
     *
     * In CHANGED state:
     * - if it gets bcmptm_rm_hash_req()
     *          Must declare SHR_E_FAIL if cseq_id does not match ptrm_state_cseq_id
     *          Remain in CHANGED state.
     *
     * - if it gets commit()
     *          if cseq_id != ptrm_state_cseq_id, ignore commit.
     *          Else, it commits the changes to sw_state and goes to IDLE
     *
     * - if it gets abort()
     *          if cseq_id != ptrm_state_cseq_id, declare SHR_E_FAIL
     *          Else, it aborts the changes to sw_state and goes to IDLE
     *
     * - if it gets idle_check()
     *          it stays in CHANGED state and returns SHR_E_FAIL
     *          (cseq_id should be ignored)
     *
     * PTRM_state_cseq_id must be in HA space - just like rest of PTRM SW_state
 */

exit:
    SHR_FUNC_EXIT();
}

