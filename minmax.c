#include "minimax.h"
#include <limits.h>

static int minimax_internal(
    void* state,
    int depth,
    int maximizingPlayer,
    int alpha,
    int beta,
    GetChildrenFunc get_children,
    EvaluateFunc evaluate,
    IsTerminalFunc is_terminal,
    void** best_child_out
) {
    if (depth == 0 || is_terminal(state)) {
        if (best_child_out) *best_child_out = NULL;
        return evaluate(state);
    }

    void** children = NULL;
    int child_count = get_children(state, &children);

    if (child_count == 0) {
        if (best_child_out) *best_child_out = NULL;
        return evaluate(state);
    }

    int best_score = maximizingPlayer ? INT_MIN : INT_MAX;
    void* best_child = NULL;

    for (int i = 0; i < child_count; i++) {
        void* child = children[i];
        void* dummy = NULL;
        int score = minimax_internal(
            child,
            depth - 1,
            !maximizingPlayer,
            alpha,
            beta,
            get_children,
            evaluate,
            is_terminal,
            &dummy
        );

        if (maximizingPlayer) {
            if (score > best_score) {
                best_score = score;
                best_child = child;
            }
            if (best_score > alpha) alpha = best_score;
        } else {
            if (score < best_score) {
                best_score = score;
                best_child = child;
            }
            if (best_score < beta) beta = best_score;
        }

        // α-β剪定: これ以降の兄弟ノードは探索不要
        if (beta <= alpha) break;
    }

    if (best_child_out) *best_child_out = best_child;
    return best_score;
}

int minimax(
    void* state,
    int depth,
    int maximizingPlayer,
    GetChildrenFunc get_children,
    EvaluateFunc evaluate,
    IsTerminalFunc is_terminal,
    void** best_child_out
) {
    return minimax_internal(
        state,
        depth,
        maximizingPlayer,
        INT_MIN,
        INT_MAX,
        get_children,
        evaluate,
        is_terminal,
        best_child_out
    );
}