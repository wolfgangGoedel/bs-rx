let noop = _ => ();
let flip = (f, a, b) => f(b, a);

module Subscription = {
  type t;

  [@bs.send] external unsubscribe : t => unit = "";
  [@bs.get] external closed : t => bool = "";

  [@bs.send] external add : (t, t) => t = "";
  [@bs.send] external remove : (t, t) => unit = "";
};

module Observer = {
  type t('a);

  [@bs.send] external next : (t('a), 'a) => unit = "";
  [@bs.send] external error : (t('a), 'e) => unit = "";
  [@bs.send] external complete : t('a) => unit = "";
};

module Observable = {
  type t('a);
  type operatorFunction('a, 'b) = (. t('a)) => t('b);

  /* create */

  [@bs.module "rxjs"] [@bs.new]
  external make : ((Observer.t('a), unit) => unit) => t('a) = "Observable";

  [@bs.module "rxjs"] external of1 : 'a => t('a) = "of";
  [@bs.module "rxjs"] external of2 : ('a, 'a) => t('a) = "of";

  [@bs.module "rxjs"] external fromArray : array('a) => t('a) = "from";
  [@bs.module "rxjs"]
  external fromPromise : Js.Promise.t('a) => t('a) = "from";

  [@bs.module "rxjs"] external defer : (unit => t('a)) => t('a) = "defer";
  [@bs.module "rxjs"]
  external deferPromise : (unit => Js.Promise.t('a)) => t('a) = "defer";

  /* consume */

  [@bs.send]
  external _subscribe :
    (
      t('a),
      [@bs.uncurry] ('a => unit),
      [@bs.uncurry] ('e => unit),
      [@bs.uncurry] (unit => unit)
    ) =>
    Subscription.t =
    "subscribe";

  let subscribe = (~next=noop, ~error=noop, ~complete=noop, source) =>
    _subscribe(source, next, error, complete);

  /* operators */

  [@bs.module "rxjs/operators"]
  external _tap :
    (
      [@bs.uncurry] ('a => unit),
      [@bs.uncurry] ('e => unit),
      [@bs.uncurry] (unit => unit)
    ) =>
    operatorFunction('a, 'a) =
    "tap";

  let tap = (~next=noop, ~error=noop, ~complete=noop, source) =>
    (_tap(next, error, complete))(. source);

  [@bs.module "rxjs/operators"]
  external _map : ([@bs.uncurry] ('a => 'b)) => operatorFunction('a, 'b) =
    "map";

  let map = (source, project) => (_map(project))(. source);

  [@bs.module "rxjs/operators"]
  external _mapWithIndex :
    ([@bs.uncurry] (('a, int) => 'b)) => operatorFunction('a, 'b) =
    "map";

  let mapWithIndex = (source, project) =>
    (_mapWithIndex(flip(project)))(. source);

  [@bs.module "rxjs/operators"]
  external _filter : ([@bs.uncurry] ('a => bool)) => operatorFunction('a, 'a) =
    "filter";

  let filter = (source, predicate) => (_filter(predicate))(. source);

  [@bs.module "rxjs/operators"]
  external _filterWithIndex :
    ([@bs.uncurry] (('a, int) => bool)) => operatorFunction('a, 'a) =
    "filter";

  let filterWithIndex = (source, predicate) =>
    (_filterWithIndex(flip(predicate)))(. source);

  [@bs.module "rxjs/operators"]
  external _mergeMap :
    ([@bs.uncurry] ('a => t('b)), ~concurrent: int=?) =>
    operatorFunction('a, 'b) =
    "flatMap";

  let mergeMap = (~concurrent=?, source, project) =>
    (_mergeMap(project, ~concurrent?))(. source);

  [@bs.module "rxjs/operators"]
  external _mergeMapWithIndex :
    ([@bs.uncurry] (('a, int) => t('b)), ~concurrent: int=?) =>
    operatorFunction('a, 'b) =
    "flatMap";

  let mergeMapWithIndex = (~concurrent=?, source, project) =>
    (_mergeMapWithIndex(flip(project), ~concurrent?))(. source);
};

module Subject = {
  type t('a);

  [@bs.module "rxjs"] [@bs.new] external make : unit => t('a) = "Subject";
  external asObservable : t('a) => Observable.t('a) = "%identity";
  external asObserver : t('a) => Observer.t('a) = "%identity";
};