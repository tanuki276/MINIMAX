def minimax(state, depth, maximizing, get_children, evaluate, is_terminal):
    """
    汎用ミニマックス関数

    Args:
        state: 現在の盤面（どんな形式でもOK）
        depth: 探索深さ
        maximizing: True = プレイヤー, False = 敵
        get_children(state): 次の状態リストを返す関数
        evaluate(state): 状態の評価値を返す関数
        is_terminal(state): 終局状態かどうか判定する関数

    Returns:
        評価値, 最善の次状態
    """
    if depth == 0 or is_terminal(state):
        return evaluate(state), state

    best_state = None

    if maximizing:
        max_eval = float('-inf')
        for child in get_children(state):
            eval_score, _ = minimax(child, depth - 1, False, get_children, evaluate, is_terminal)
            if eval_score > max_eval:
                max_eval = eval_score
                best_state = child
        return max_eval, best_state
    else:
        min_eval = float('inf')
        for child in get_children(state):
            eval_score, _ = minimax(child, depth - 1, True, get_children, evaluate, is_terminal)
            if eval_score < min_eval:
                min_eval = eval_score
                best_state = child
        return min_eval, best_state