document.addEventListener('DOMContentLoaded', () => {
    const gameBoard = document.getElementById('game-board');
    let board = [
        [0, 0, 0, 0],
        [0, 0, 0, 0],
        [0, 0, 0, 0],
        [0, 0, 0, 0]
    ];
    let touchStartX = 0;
    let touchStartY = 0;

    function createBoard() {
        gameBoard.innerHTML = '';
        for (let r = 0; r < 4; r++) {
            for (let c = 0; c < 4; c++) {
                const tile = document.createElement('div');
                tile.classList.add('tile');
                if (board[r][c] !== 0) {
                    tile.textContent = board[r][c];
                    tile.classList.add(`tile-${board[r][c]}`);
                }
                gameBoard.appendChild(tile);
            }
        }
    }

    function addRandomTile() {
        let emptyCells = [];
        for (let r = 0; r < 4; r++) {
            for (let c = 0; c < 4; c++) {
                if (board[r][c] === 0) {
                    emptyCells.push({ r, c });
                }
            }
        }
        if (emptyCells.length > 0) {
            let randomCell = emptyCells[Math.floor(Math.random() * emptyCells.length)];
            board[randomCell.r][randomCell.c] = (Math.random() < 0.9) ? 2 : 4;
        }
    }

    function slideRow(row) {
        let newRow = row.filter(val => val !== 0);
        let missing = 4 - newRow.length;
        let zeros = Array(missing).fill(0);
        newRow = newRow.concat(zeros);
        return newRow;
    }

    function combineRow(row) {
        for (let i = 0; i < 3; i++) {
            if (row[i] !== 0 && row[i] === row[i + 1]) {
                row[i] *= 2;
                row[i + 1] = 0;
            }
        }
        return row;
    }
    
    function rotateBoard() {
        let newBoard = [[0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0]];
        for (let r = 0; r < 4; r++) {
            for (let c = 0; c < 4; c++) {
                newBoard[r][c] = board[c][3 - r];
            }
        }
        board = newBoard;
    }

    function handleMove(direction) {
        let oldBoard = JSON.parse(JSON.stringify(board));

        if (direction === 'ArrowUp') {
            rotateBoard();
            rotateBoard();
            rotateBoard(); // 270度回転して上を左に
        } else if (direction === 'ArrowDown') {
            rotateBoard(); // 90度回転して下を左に
        } else if (direction === 'ArrowRight') {
            rotateBoard();
            rotateBoard(); // 180度回転して右を左に
        }

        // ここで左方向の処理を実行
        for (let r = 0; r < 4; r++) {
            let row = board[r];
            row = combineRow(slideRow(row));
            board[r] = slideRow(row);
        }

        if (direction === 'ArrowUp') {
            rotateBoard(); // 元に戻す
        } else if (direction === 'ArrowDown') {
            rotateBoard();
            rotateBoard();
            rotateBoard(); // 元に戻す
        } else if (direction === 'ArrowRight') {
            rotateBoard();
            rotateBoard(); // 元に戻す
        }
        
        let isChanged = JSON.stringify(oldBoard) !== JSON.stringify(board);
        if (isChanged) {
            addRandomTile();
            createBoard();
        }
    }

    // PCキーボード操作
    document.addEventListener('keydown', (e) => {
        if (['ArrowUp', 'ArrowDown', 'ArrowLeft', 'ArrowRight'].includes(e.key)) {
            handleMove(e.key);
        }
    });

    // スマホスワイプ操作
    gameBoard.addEventListener('touchstart', (e) => {
        touchStartX = e.changedTouches[0].screenX;
        touchStartY = e.changedTouches[0].screenY;
    });

    gameBoard.addEventListener('touchend', (e) => {
        let touchEndX = e.changedTouches[0].screenX;
        let touchEndY = e.changedTouches[0].screenY;
        let dx = touchEndX - touchStartX;
        let dy = touchEndY - touchStartY;

        if (Math.abs(dx) > Math.abs(dy) && Math.abs(dx) > 30) {
            if (dx > 0) handleMove('ArrowRight');
            else handleMove('ArrowLeft');
        } else if (Math.abs(dy) > Math.abs(dx) && Math.abs(dy) > 30) {
            if (dy > 0) handleMove('ArrowDown');
            else handleMove('ArrowUp');
        }
    });

    // 初期化
    addRandomTile();
    addRandomTile();
    createBoard();
});
