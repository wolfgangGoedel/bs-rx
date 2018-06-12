open Jest;
open Expect;

test("make Subject", () => {
  let subject = Rx.Subject.make();
  let completed = ref(false);

  Rx.Subject.asObservable(subject)
  |. Rx.Observable.subscribe(~complete=() => completed := true)
  |. ignore;

  Rx.Subject.asObserver(subject) |. Rx.Observer.complete;

  expect(completed^) |> toBe(true);
});