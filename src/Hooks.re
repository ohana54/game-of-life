let useInterval = (callback, delay) => {
  React.useEffect1(
    () => {
      switch (delay) {
      | Some(d) =>
        let id = Js.Global.setInterval(callback, d);
        Some(() => Js.Global.clearInterval(id));
      | None => None
      }
    },
    [|delay|],
  );
};
