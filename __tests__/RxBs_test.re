open Jest;
open Expect;

describe("observable", () => {
  test("create and subscribe with next", () => {
    let observed = [||];

    Rx.Observable.(
      of2("hello", "world")
      |. subscribe(~next=e => Js.Array.push(e, observed) |. ignore, ())
      |. ignore
    );

    expect(observed) |> toEqual([|"hello", "world"|]);
  });

  test("subscribe without params", () => {
    let observed = ref(None);

    Rx.Observable.(
      of1("test")
      |. tap(~next=e => observed := Some(e), ())
      |. subscribe()
      |. ignore
    );

    expect(observed^) |> toEqual(Some("test"));
  });
});