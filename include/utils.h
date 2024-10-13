#ifndef UTILS_H
#define UTILS_H

void resetCursorPosition();
void clearTerminal();

#ifdef _W32
void activateVirtualTerminal();
#endif

#endif //utils.h