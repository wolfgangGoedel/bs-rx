type t('a);
type operatorFunction('a, 'b) = (. t('a)) => t('b);

let noop = _ => ();
let flip = (f, a, b) => f(b, a);

/* create */

[@bs.module "rxjs"] [@bs.new]
external make : ((Rx_Observer.t('a), unit) => unit) => t('a) = "Observable";

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
  Rx_Subscription.t =
  "subscribe";

let subscribe = (~next=noop, ~error=noop, ~complete=noop, source) =>
  _subscribe(source, next, error, complete);