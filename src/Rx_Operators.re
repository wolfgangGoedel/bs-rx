open Rx_Observable;

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