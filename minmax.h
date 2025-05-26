#ifndef MINIMAX_H
#define MINIMAX_H

typedef int (*EvaluateFunc)(void* state);
typedef int (*IsTerminalFunc)(void* state);
typedef int (*GetChildrenFunc)(void* state, void*** children);

int minimax(
    void* state,
    int depth,
    int maximizingPlayer,
    GetChildrenFunc get_children,
    EvaluateFunc evaluate,
    IsTerminalFunc is_terminal,
    void** best_child_out
);

#endif