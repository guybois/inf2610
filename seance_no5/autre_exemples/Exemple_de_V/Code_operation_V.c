
// Ce à quoi peut ressembler une opération  V 
// Inspiré de uC/OS-III
OS_SEM_CTR  OSSemPost (OS_SEM  *p_sem,
                       OS_OPT   opt,
                       OS_ERR  *p_err)
{
    OS_SEM_CTR     ctr;
    OS_PEND_LIST  *p_pend_list;
    OS_TCB        *p_tcb;
    OS_TCB        *p_tcb_next;
    CPU_TS         ts;
    CPU_SR_ALLOC();


    CPU_CRITICAL_ENTER();
    p_pend_list = &p_sem->PendList;
    if (p_pend_list->HeadPtr == (OS_TCB *)0) {                  /* Any task waiting on semaphore?                       */

        p_sem->Ctr++;                                           /* No                                                   */
        ctr       = p_sem->Ctr;
        CPU_CRITICAL_EXIT();
       *p_err     = OS_ERR_NONE;
        return (ctr);
    }

    p_tcb = p_pend_list->HeadPtr;
    while (p_tcb != (OS_TCB *)0) {
        p_tcb_next = p_tcb->PendNextPtr;
        OS_Post((OS_PEND_OBJ *)((void *)p_sem),
                p_tcb,
                (void *)0,
                0u,
                ts);
        if ((opt & OS_OPT_POST_ALL) == 0u) {                     /* Post to all tasks waiting?                           */
            break;                                              /* No                                                   */
        }
        p_tcb = p_tcb_next;
    }
    CPU_CRITICAL_EXIT();
    if ((opt & OS_OPT_POST_NO_SCHED) == 0u) {
        OSSched();                                              /* Run the scheduler                                    */
    }
   *p_err = OS_ERR_NONE;

    return (0u);
}