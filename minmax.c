#include "minimax.h"
#include <limits.h>
#include <stdlib.h>

int minimax(
    void* state,
    int depth,
    int maximizingPlayer,
    GetChildrenFunc get_children,
    EvaluateFunc evaluate,
    IsTerminalFunc is_terminal,
    void** best_child_out
) {
    if (depth == 0 || is_terminal(state)) {
        *best_child_out = NULL;
        return evaluate(state);
    }

    void** children = NULL;
    int child_count = get_children(state, &children);

    if (child_count == 0) {
        *best_child_out = NULL;
        return evaluate(state);
    }

    int best_score = maximizingPlayer ? INT_MIN : INT_MAX;
    void* best_child = NULL;

    for (int i = 0; i < child_count; i++) {
        void* child = children[i];
        void* dummy;
        int score = minimax(child, depth - 1, !maximizingPlayer, get_children, evaluate, is_terminal, &dummy);

        if ((maximizingPlayer && score > best_score) || (!maximizingPlayer && score < best_score)) {
            best_score = score;
            best_child = child;
        }
    }

    *best_child_out = best_child;
    return best_score;
}