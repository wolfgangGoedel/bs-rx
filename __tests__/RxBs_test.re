open Jest;
open Expect;

exception TestExn(string);

describe("observable", () => {
  test("create and subscribe with next", () => {
    let observed = [||];

    Rx.Observable.(
      of2("hello", "world")
      |. subscribe(~next=e => Js.Array.push(e, observed) |> ignore)
    )
    |> ignore;

    expect(observed) |> toEqual([|"hello", "world"|]);
  });

  test("tap and subscribe without params", () => {
    let observed = ref(None);
    let completed = ref(false);

    Rx.Observable.(
      of1("test")
      |. tap(
           ~next=e => observed := Some(e),
           ~complete=() => completed := true,
         )
      |. subscribe
    )
    |> ignore;

    expect((observed^, completed^)) |> toEqual((Some("test"), true));
  });

  testAsync("from resolved Promise", done_ => {
    let observed = ref(None);

    Rx.Observable.(
      fromPromise(Js.Promise.resolve("Hello"))
      |. subscribe(
           ~next=e => observed := Some(e),
           ~complete=
             () => expect(observed^) |> toEqual(Some("Hello")) |> done_,
         )
    )
    |> ignore;
  });

  testAsync("from rejected Promise", done_ =>
    Rx.Observable.(
      fromPromise(Js.Promise.reject(TestExn("boo")))
      |. subscribe(~error=e =>
           expect(e) |> toEqual(TestExn("boo")) |> done_
         )
    )
    |> ignore
  );
});