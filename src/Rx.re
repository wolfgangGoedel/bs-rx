type error;

module Subscription = {
  type t;

  [@bs.send] external unsubscribe : t => unit = "";
  [@bs.get] external closed : t => bool = "";

  [@bs.send] external add : (t, t) => t = "";
  [@bs.send] external remove : (t, t) => unit = "";
};

module Observable = {
  type t('a);
  type operatorFunction('a, 'b) = (. t('a)) => t('b);

  /* create */

  [@bs.module "rxjs"] external fromArray : array('a) => t('a) = "from";

  [@bs.module "rxjs"] external of1 : 'a => t('a) = "of";
  [@bs.module "rxjs"] external of2 : ('a, 'a) => t('a) = "of";

  /* consume */

  [@bs.send]
  external _subscribe :
    (
      t('a),
      [@bs.uncurry] ('a => unit),
      [@bs.uncurry] (error => unit),
      [@bs.uncurry] (unit => unit)
    ) =>
    Subscription.t =
    "subscribe";

  let subscribe =
      (source, ~next=_ => (), ~error=_ => (), ~complete=() => (), ()) =>
    _subscribe(source, next, error, complete);

  /* operators */

  [@bs.module "rxjs/operators"]
  external _tap :
    (
      [@bs.uncurry] ('a => unit),
      [@bs.uncurry] (error => unit),
      [@bs.uncurry] (unit => unit)
    ) =>
    operatorFunction('a, 'a) =
    "tap";

  let tap = (source, ~next=_ => (), ~error=_ => (), ~complete=() => (), ()) =>
    (_tap(next, error, complete))(. source);

  [@bs.module "rxjs/operators"]
  external _mapWithIndex : ((. 'a, int) => 'b) => operatorFunction('a, 'b) =
    "map";

  let mapWithIndexU = (source, project) =>
    (_mapWithIndex((. e, i) => project(. i, e)))(. source);
  let mapWithIndex = (source, project) =>
    source |. mapWithIndexU((. i, e) => project(i, e));

  [@bs.module "rxjs/operators"]
  external _map : ((. 'a) => 'b) => operatorFunction('a, 'b) = "map";

  let mapU = (source, project) => (_map((. e) => project(. e)))(. source);
  let map = (source, project) => source |. mapU((. e) => project(e));

  [@bs.module "rxjs/operators"]
  external _filter : ((. 'a) => bool) => operatorFunction('a, 'a) = "filter";

  let filterU = (source, predicate) =>
    (_filter((. e) => predicate(. e)))(. source);
  let filter = (source, predicate) =>
    source |. filterU((. e) => predicate(e));

  [@bs.module "rxjs/operators"]
  external _filterWithIndex :
    ((. 'a, int) => bool) => operatorFunction('a, 'a) =
    "filter";

  let filterWithIndexU = (source, predicate) =>
    (_filterWithIndex((. e, i) => predicate(. i, e)))(. source);
  let filterWithIndex = (source, predicate) =>
    source |. filterWithIndexU((. i, e) => predicate(i, e));
};