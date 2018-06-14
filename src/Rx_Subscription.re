type t;

[@bs.send] external unsubscribe : t => unit = "";
[@bs.get] external closed : t => bool = "";

[@bs.send] external add : (t, t) => t = "";
[@bs.send] external remove : (t, t) => unit = "";