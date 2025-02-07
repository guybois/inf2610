
// Ce à quoi peut ressembler une opération V pouvant être bloquant ou non bloquant (via opt) et pouvant même avoir un délai d'attente (via timeout)
// Inspiré de uC/OS-III
OS_SEM_CTR  OSSemPend (OS_SEM   *p_sem,
                       OS_TICK   timeout,
                       OS_OPT    opt,
                       CPU_TS   *p_ts,
                       OS_ERR   *p_err)
{
    OS_SEM_CTR  ctr;
    CPU_SR_ALLOC();


    CPU_CRITICAL_ENTER();
    if (p_sem->Ctr > 0u) {                                      /* Resource available?                                  */
        p_sem->Ctr--;                                           /* Yes, caller may proceed                              */
        ctr   = p_sem->Ctr;
        CPU_CRITICAL_EXIT();
       *p_err = OS_ERR_NONE;
        return (ctr);
    }

    if ((opt & OS_OPT_PEND_NON_BLOCKING) != 0u) {               /* Caller wants to block if not available?              */
        ctr   = p_sem->Ctr;                                     /* No                                                   */
        CPU_CRITICAL_EXIT();
       *p_err = OS_ERR_PEND_WOULD_BLOCK;
        return (ctr);
    } else {                                                    /* Yes                                                  */
        if (OSSchedLockNestingCtr > 0u) {                       /* Can't pend when the scheduler is locked              */
            CPU_CRITICAL_EXIT();
           *p_err = OS_ERR_SCHED_LOCKED;
            return (0u);
        }
    }
    OS_Pend((OS_PEND_OBJ *)((void *)p_sem),                     /* Block task pending on Semaphore                      */
            OSTCBCurPtr,
            OS_TASK_PEND_ON_SEM,
            timeout);
    CPU_CRITICAL_EXIT();
    OSSched(); 													/* Find the next HPT and call OSCtxSw					*/
	CPU_CRITICAL_ENTER();
    switch (OSTCBCurPtr->PendStatus) {
        case OS_STATUS_PEND_OK:                                 /* We got the semaphore                                 */
            *p_err = OS_ERR_NONE;
             break;

        case OS_STATUS_PEND_ABORT:                              /* Indicate that we aborted                             */
            *p_err = OS_ERR_PEND_ABORT;
             break;

        case OS_STATUS_PEND_TIMEOUT:                            /* Indicate that we didn't get semaphore within timeout */
            *p_err = OS_ERR_TIMEOUT;
             break;

        case OS_STATUS_PEND_DEL:                                /* Indicate that object pended on has been deleted      */
            *p_err = OS_ERR_OBJ_DEL;
             break;

        default:
            *p_err = OS_ERR_STATUS_INVALID;
             CPU_CRITICAL_EXIT();
             OS_TRACE_SEM_PEND_EXIT(*p_err);
             return (0u);
    }
    ctr = p_sem->Ctr;
    CPU_CRITICAL_EXIT();
    return (ctr);
}