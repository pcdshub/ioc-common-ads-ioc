/* Backport of EPICS Base 7.0.10's afterIocRunning iocsh command (PR #558) for sites still on Base 7.0.3.x */
#ifndef INC_afterIocRunning_H
#define INC_afterIocRunning_H

void afterIocRunningRegister(void);

#endif /* INC_afterIocRunning_H */
