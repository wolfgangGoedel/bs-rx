module Subscription: {
  type t;
  let unsubscribe: t => unit;
  let closed: t => bool;

  let add: (t, t) => t;
  let remove: (t, t) => unit;
};

/* module Observer: {
     type t('a);
     let next: 'a => unit;
     let error: error => unit;
     let complete: unit => unit;
   }; */

module Observable: {
  type t('a);

  /* create */

  let of1: 'a => t('a);
  let of2: ('a, 'a) => t('a);
  /* add scheduler */

  let fromArray: array('a) => t('a);
  let fromPromise: Js.Promise.t('a) => t('a);

  /* subscribe */

  let subscribe:
    (
      ~next: 'a => unit=?,
      ~error: 'e => unit=?,
      ~complete: unit => unit=?,
      t('a)
    ) =>
    Subscription.t;

  /* operators */

  let tap:
    (
      ~next: 'a => unit=?,
      ~error: 'e => unit=?,
      ~complete: unit => unit=?,
      t('a)
    ) =>
    t('a);

  let map: (t('a), 'a => 'b) => t('b);
  let mapWithIndex: (t('a), (int, 'a) => 'b) => t('b);

  let filter: (t('a), 'a => bool) => t('a);
  let filterWithIndex: (t('a), (int, 'a) => bool) => t('a);
};