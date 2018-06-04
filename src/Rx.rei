type error;

module Subscription: {
  type t;
  let unsubscribe: t => unit;
  let closed: t => bool;

  let add: (t, t) => t;
  let remove: (t, t) => unit;
};

module Observable: {
  type t('a);

  /* create */

  let of1: 'a => t('a);
  let of2: ('a, 'a) => t('a);
  /* add scheduler */

  let fromArray: array('a) => t('a);

  /* subscribe */

  let subscribe:
    (
      t('a),
      ~next: 'a => unit=?,
      ~error: error => unit=?,
      ~complete: unit => unit=?,
      unit
    ) =>
    Subscription.t;

  /* operators */

  let tap:
    (
      t('a),
      ~next: 'a => unit=?,
      ~error: error => unit=?,
      ~complete: unit => unit=?,
      unit
    ) =>
    t('a);

  let map: (t('a), 'a => 'b) => t('b);
  let mapU: (t('a), (. 'a) => 'b) => t('b);
  let mapWithIndex: (t('a), (int, 'a) => 'b) => t('b);
  let mapWithIndexU: (t('a), (. int, 'a) => 'b) => t('b);

  let filter: (t('a), 'a => bool) => t('a);
  let filterU: (t('a), (. 'a) => bool) => t('a);
  let filterWithIndex: (t('a), (int, 'a) => bool) => t('a);
  let filterWithIndexU: (t('a), (. int, 'a) => bool) => t('a);
};