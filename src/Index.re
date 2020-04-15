// Entry point

[@bs.val] external document: Js.t({..}) = "document";

let style = document##createElement("style");
document##head##appendChild(style);
style##innerHTML #= Styles.style;

let container = document##createElement("div");
document##body##appendChild(container);

ReactDOMRe.render(<Board />, container);
