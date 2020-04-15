type cell =
  | Dead
  | Alive;

type t = array(array(cell));

Random.init(int_of_float(Js.Date.now()));

let getMatrix = (matrix, rowIndex, colIndex) => {
  switch (Belt.Array.get(matrix, rowIndex)) {
  | Some(row) => Belt.Array.get(row, colIndex)
  | None => None
  };
};

let getNeighbors = (board, rowIndex, colIndex) => {
  [|
    getMatrix(board, rowIndex - 1, colIndex - 1),
    getMatrix(board, rowIndex - 1, colIndex),
    getMatrix(board, rowIndex - 1, colIndex + 1),
    getMatrix(board, rowIndex, colIndex - 1),
    getMatrix(board, rowIndex, colIndex + 1),
    getMatrix(board, rowIndex + 1, colIndex - 1),
    getMatrix(board, rowIndex + 1, colIndex),
    getMatrix(board, rowIndex + 1, colIndex + 1),
  |]
  ->Belt.Array.keepMap(n => n);
};

let isAlive = x => {
  switch (x) {
  | Alive => true
  | Dead => false
  };
};

let getNewCell = (board, rowIndex, colIndex) => {
  let numOfLiveNeighbors =
    getNeighbors(board, rowIndex, colIndex)
    ->Belt.Array.keep(isAlive)
    ->Belt.Array.size;
  switch (board[rowIndex][colIndex]) {
  | Alive when numOfLiveNeighbors == 2 || numOfLiveNeighbors == 3 => Alive
  | Dead when numOfLiveNeighbors == 3 => Alive
  | _ => Dead
  };
};

let createRowData = (rowSize, _) => {
  Belt.Array.makeBy(rowSize, _ => {Random.int(10) > 7 ? Alive : Dead});
};

let newBoard = boardSize => {
  Belt.Array.makeBy(boardSize, createRowData(boardSize));
};

let nextBoard = board => {
  let boardSize = board->Belt.Array.size;
  Belt.Array.makeBy(boardSize, rowIndex => {
    Belt.Array.makeBy(boardSize, colIndex => {
      getNewCell(board, rowIndex, colIndex)
    })
  });
};
