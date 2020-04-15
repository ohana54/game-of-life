type state = {
  running: bool,
  board: BoardData.t,
};

type action =
  | Tick
  | Start
  | Stop
  | Reset;

let boardSize = 50;

let initialState = {running: false, board: BoardData.newBoard(boardSize)};

let reducer = (state, action) => {
  switch (action) {
  | Tick => {...state, board: BoardData.nextBoard(state.board)}
  | Start => {...state, running: true}
  | Stop => {...state, running: false}
  | Reset => {...state, board: BoardData.newBoard(boardSize)}
  };
};

let createCell = (index, cell) => {
  open BoardData;
  let bgColor =
    switch (cell) {
    | Dead => "white"
    | Alive => "black"
    };
  let style = ReactDOMRe.Style.make(~backgroundColor=bgColor, ());
  <td style key={string_of_int(index)} />;
};

let createRow = (index, row) => {
  <tr key={string_of_int(index)}>
    {Belt.Array.mapWithIndex(row, createCell)->React.array}
  </tr>;
};

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer(reducer, initialState);

  let delay = state.running ? Some(75) : None;

  Hooks.useInterval(() => dispatch(Tick), delay);

  <div
    style={ReactDOMRe.Style.make(
      ~display="flex",
      ~alignItems="center",
      ~justifyContent="space-between",
      ~flexDirection="column",
      (),
    )}>
    <table>
      <tbody>
        {Belt.Array.mapWithIndex(state.board, createRow)->React.array}
      </tbody>
    </table>
    <div>
      <button onClick={_ => dispatch(Start)}>
        {React.string("Start")}
      </button>
      <button onClick={_ => dispatch(Stop)}> {React.string("Stop")} </button>
      <button onClick={_ => dispatch(Tick)}> {React.string("Tick")} </button>
      <button onClick={_ => dispatch(Reset)}>
        {React.string("Reset")}
      </button>
    </div>
  </div>;
};
