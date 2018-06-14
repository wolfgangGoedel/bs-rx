# bs-rx

[BuckleScript](https://github.com/bucklescript/bucklescript) bindings for [RxJS](https://github.com/ReactiveX/rxjs)

`bs-rx` is a work in progress with the goal to provide bindings to the RxJS reactive programming library. It tries to stay close to the original TypeScript API of RxJS, but with some changes to be closer to `Belt` (`t` comes first - pipe with `|.`)

In its current state it's more a RFC to find the right API. Feel free to post issues !

## Example

```reason
Rx.Observable.(
  Belt.Array.range(1, 100)
  |. fromArray
  |. filter(x => x mod 3 == 0)
  |. subscribe(~next=Js.log)
);
```

## Todo

**Many things.**

- Only a few operators are bound yet - and RxJS has a lot of them
- Document all these operators
- subscribe expects next, error, complete callbacks - using a variant type would be more elegant (and would force to handle stream errors and avoid runtime exceptions)
- ultimately, there should be an RxBS library with interop with RxJS but implemented in Reason/OCaml and usable with native projects
