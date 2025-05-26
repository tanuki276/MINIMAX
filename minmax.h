#ifndef MINIMAX_H
#define MINIMAX_H

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*EvaluateFunc)(void* state);
/* 盤面や状態の評価値を返す関数 */

typedef int (*IsTerminalFunc)(void* state);
/* 終端（ゲーム終了）判定を返す関数（trueなら終端） */

typedef int (*GetChildrenFunc)(void* state, void*** children);
/* 子ノード（次の手の状態）を配列で返す関数
   戻り値は子ノード数、childrenには子ノード配列のポインタを格納 */

/**
 * minimax関数（α-β剪定付き）
 * @param state 現在のゲーム状態
 * @param depth 探索深さ制限
 * @param maximizingPlayer 1なら最大化プレイヤー、0なら最小化プレイヤー
 * @param get_children 子ノード取得関数
 * @param evaluate 評価関数
 * @param is_terminal 終端判定関数
 * @param best_child_out 最善手の子ノードを受け取るポインタ（NULL可）
 * @return 最善手の評価値
 */
int minimax(
    void* state,
    int depth,
    int maximizingPlayer,
    GetChildrenFunc get_children,
    EvaluateFunc evaluate,
    IsTerminalFunc is_terminal,
    void** best_child_out
);

#ifdef __cplusplus
}
#endif

#endif /* MINIMAX_H */